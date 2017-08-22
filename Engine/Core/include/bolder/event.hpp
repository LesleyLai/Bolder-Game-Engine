#pragma once

/**
  * @file event.hpp
  * @brief File for the event system.
  *
  * This file contains the event module that allows for event-response like
  * programming in C++.
  */

#include <algorithm>
#include <cassert>
#include <vector>
#include <functional>
#include <mutex>

#include "bolder/exception.hpp"

namespace bolder { namespace event {

/** @addtogroup event
 * @{
 */

/**
 * @brief Event channel broadcasts events into its corresponding handler
 */
class Channel {
public:
    /// Adds an Event_handler to the channel
    template <typename Event, typename Handler>
    void add_handler(Handler& handler);

    /// Removes an Event_handler to the channel
    template <typename Event, typename Handler>
    void remove_handler(Handler& handler);

    /// Broadcast an event
    template<class Event>
    void broadcast(const Event& event);
};

/**
 * @class Handler_raii
 * @brief A RAII wrapper of an event handler
 *
 * Handler_raii automatically adds an event handler into the Event channel
 * and remove the event handler when out of scope.
 */
template<class Handler>
class Handler_raii {
public:
    template<typename... Args>
    Handler_raii(Channel& channel, Args&&... args);

    ~Handler_raii();

private:
    Channel& channel_;
    Handler handler_;
};

/**
 * @class Handler_trait
 * @brief Provides event_type typedef that retrive the corresponding event type
 * of a handler.
 */
template<typename Event>
struct Handler_trait {
    using event_type = Event;
};

/** @}*/

/** @defgroup event Events
 * @brief This module provides an event system.
 * @par Usage
 * First, we need an event handler that conform to the event::Handler
 * concept. Event handlers have their corresponding event types, which can be
 * arbitrary structure with data that the event handlers is interested in. We
 * add the event handler to event::Channel by its .add() member function or by
 * event::Handler_raii wrapper. At last, we create and broadcast the event through
 * event::Channel's broadcast() member; the channel will automatically call
 * event handlers that interested in the event.
 * @par Example
 * @code{.cpp}
 * #include "bolder/event.hpp"
 *
 * #include <iostream>
 *
 * using namespace bolder;
 *
 * struct Test_event {
 *     int value;
 * };
 *
 * class Test_event_handler : public event::Handler_trait<Test_event> {
 * public:
 *     Test_event_handler(std::stringstream& sstream) : ss_{sstream} {}
 *
 *     void operator()(const event_type& evt) {
 *         std::cout << "Event received: " << evt.value << '\n';
 *     }
 * };
 *
 * int main() {
 *     event::Channel channel;
 *     event::Handler_raii<Test_event_handler> handler(channel);
 *     channel.broadcast(Test_event{123}); // Prints "Event received: 123"
 * }
 * @endcode
 */

/**
 * @interface bolder::event::Handler
 * @ingroup event
 * @brief Concept of event handler
 *
 * Handler is a [concept](https://en.wikipedia.org/wiki/Concepts_(C%2B%2B))
 * about how to write event handler classes. This concept Specifies that an
 * instance of the type can be treat as event handler.
 *
 * @{
 * @par Requirements
 * The type @c T satisfies Handler if
 *
 * Given @c handler expression of type T or const T
 *
 * The following expressions must be valid and have their specified effects
 * @code{.cpp}
 * handler(); // Calles the event handler
 * @endcode
 * Also, handler::event_type should returns the handler's corresponding type of
 * event.
 *
 * The simplest way to create an event handler is to create a class that
 * inherited from Handler_trait; then overload its operator() function.
 * @}
 */

namespace detail {

// A global channel per event type
template<class Event>
class Internal_static_channel {
public:
    static Internal_static_channel& instance();

    template <typename T>
    void add_handler(T& handler);

    template <typename T>
    void remove_handler(T& handler);

    // Broadcast an event
    void broadcast(const Event& event);

private:
    using Handler = std::function<void(const Event&)>;

    std::mutex handlers_mutex_; // Protects handlers
    std::vector<void*> original_ptrs_;
    std::vector<Handler> handlers_;

    Internal_static_channel() {}

    void validate() const {
        assert(original_ptrs_.size() == handlers_.size());
    }
};

template<class Event>
Internal_static_channel<Event>& Internal_static_channel<Event>::instance() {
    static Internal_static_channel result;
    return result; // return a reference to an internal static
}

template<class Event>
template <typename T>
void Internal_static_channel<Event>::add_handler(T& handler) {
    std::lock_guard<std::mutex> lock(handlers_mutex_);
    original_ptrs_.push_back(&handler);
    handlers_.push_back(
                [&handler] (const Event& event) {
        handler(event);
    }
    );

    validate();
}

template<class Event>
template <typename T>
void Internal_static_channel<Event>::remove_handler(T& handler) {
    std::lock_guard<std::mutex> lock(handlers_mutex_);
    const auto it = std::find(original_ptrs_.begin(), original_ptrs_.end(),
                              &handler);
    if (it == original_ptrs_.end()) {
        throw Runtime_error {
            "Tried to remove a handler that was not in the handler list"
        };
    }

    const auto index = it - original_ptrs_.begin();
    std::iter_swap(it, original_ptrs_.end() - 1);
    std::iter_swap(handlers_.begin() + index, handlers_.end() - 1);
    original_ptrs_.pop_back();
    handlers_.pop_back();

    validate();
}

template<class Event>
void Internal_static_channel<Event>::broadcast(const Event& event) {
    std::vector<Handler> local_queue(handlers_.size());
    {
        std::lock_guard<std::mutex> lock(handlers_mutex_);
        local_queue = handlers_;
    }

    for (auto& handler: local_queue)
        handler(event);
}

} // namespace detail

template<typename Event, typename Handler>
void Channel::add_handler(Handler& handler)
{
    detail::Internal_static_channel<Event>::instance().add_handler(handler);
}

template<typename Event, typename Handler>
void Channel::remove_handler(Handler& handler) {
    detail::Internal_static_channel<Event>::instance().remove_handler(handler);
}

template<class Event>
void Channel::broadcast(const Event& event) {
    detail::Internal_static_channel<Event>::instance().broadcast(event);
}

/**
 * @brief Handler_raii<Handler>::Handler_raii Constructor
 * @param channel Event channel for the event handler
 * @param args Arguments forward to the event handler constructor
 */
template<class Handler>
template<typename... Args>
Handler_raii<Handler>::Handler_raii(Channel& channel, Args&&... args)
    : channel_{channel},
      handler_{Handler{std::forward<Args>(args)...}} {
    channel_.add_handler<Handler::event_type>(handler_);
}

///@brief Handler_raii<Handler>::~Handler_raii Destructor
template<class Handler>
Handler_raii<Handler>::~Handler_raii() {
    channel_.remove_handler<Handler::event_type>(handler_);
}

}} // namespace bolder::event
