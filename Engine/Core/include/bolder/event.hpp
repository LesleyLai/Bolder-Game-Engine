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

namespace bolder {

/** @addtogroup event
 * @{
 */

/**
 * @brief A static class of global event channel
 */
class Event_channel {
public:
    /// Adds an Event_handler to the channel
    template <typename Event, typename Handler>
    static void add_handler(Handler& handler);

    /// Removes an Event_handler to the channel
    template <typename Event, typename Handler>
    static void remove_handler(Handler& handler);

    /// Broadcast an event
    template<class Event>
    static void broadcast(const Event& event);
};

/**
 * @class Event_handler_raii
 * @brief A RAII wrapper of an event handler
 *
 * Event_handler_raii automatically adds an event handler into the Event channel
 * and remove the event handler when out of scope.
 */
template<class Handler>
class Event_handler_raii {
public:
    template<typename... Args>
    Event_handler_raii(Args&&... args);

    ~Event_handler_raii();

private:
    Handler handler_;
};

/**
 * @class Event_handler_trait
 * @brief Provides event_type typedef that retrive the corresponding event type
 * of a handler.
 */
template<typename Event>
struct Event_handler_trait {
    using event_type = Event;
};

/** @}*/


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
void Event_channel::add_handler(Handler& handler)
{
    detail::Internal_static_channel<Event>::instance().add_handler(handler);
}

template<typename Event, typename Handler>
void Event_channel::remove_handler(Handler& handler) {
    detail::Internal_static_channel<Event>::instance().remove_handler(handler);
}

template<class Event>
void Event_channel::broadcast(const Event& event) {
    detail::Internal_static_channel<Event>::instance().broadcast(event);
}

template<class Handler>
template<typename... Args>
Event_handler_raii<Handler>::Event_handler_raii(Args&&... args)
    : handler_{Handler{std::forward<Args>(args)...}} {
    Event_channel::add_handler<Handler::event_type>(handler_);
}

template<class Handler>
Event_handler_raii<Handler>::~Event_handler_raii() {
    Event_channel::remove_handler<Handler::event_type>(handler_);
}

} // namespace bolder
