// Test of the event system

#include "bolder/event.hpp"

#include <sstream>
#include "doctest.h"

using namespace bolder;

struct Test_event {
  int value;
};

class Test_event_handler : public Event_handler_trait<Test_event> {
public:
    Test_event_handler(std::stringstream& sstream) : ss_{sstream} {}

    void operator()(const event_type& evt) {
        ss_ << "Event received: " << evt.value;
    }

private:
    std::stringstream& ss_;
};

TEST_CASE("Event system") {
    std::stringstream ss;
    Event_handler_raii<Test_event_handler> handler(ss);

    SUBCASE("Broadcasts scoped object") {
        Test_event abc{123};
        Event_channel::broadcast(abc); // transmit object
        REQUIRE_EQ(ss.str(), "Event received: 123");
    }

    SUBCASE("Broadcasts anonymous object") {
        Event_channel::broadcast(Test_event{456}); // transmit object
        REQUIRE_EQ(ss.str(), "Event received: 456");
    }
}
