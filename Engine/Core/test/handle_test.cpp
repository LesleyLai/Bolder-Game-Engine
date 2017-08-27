#include "bolder/handle.hpp"
#include "bolder/handle_manager.hpp"

#include "doctest.h"

using namespace bolder;
using Test_handle = resource::Handle<12>;

TEST_CASE("One entry handle manager") {
    resource::Handle_manager<Test_handle, int, 1> handles;
    auto handle = handles.add(100);

    REQUIRE_EQ(handles.size(), 1);

    SUBCASE("Get corrent value from entry") {
        REQUIRE_EQ(*handles[handle], 100);
    }

    SUBCASE("Remove the last elements") {
        handles.remove(handle);

        SUBCASE("size goes down when remove") {
            REQUIRE_EQ(handles.size(), 0);
        }

        SUBCASE("null if entry removed") {
            REQUIRE_EQ(handles[handle], nullptr);
        }

        SUBCASE("Throw exception when remove none exist entries") {
            REQUIRE_THROWS_AS(handles.remove(handle),
                              const resource::Resource_error&);
        }

        auto handle2 = handles.add(1);

        SUBCASE("Handles returned for same spot are different") {
            REQUIRE_NE(handle.generation, handle2.generation);
        }

        SUBCASE("Throw exception when remove entry with invalid handle") {
            REQUIRE_THROWS_AS(handles.remove(handle),
                              const resource::Resource_error&);
        }

        SUBCASE("Handle returns current value instead of stale value") {
            REQUIRE_EQ(*handles[handle2], 1);
        }
    }
}

TEST_CASE("Multiple entry Handle_manager") {
    resource::Handle_manager<Test_handle, int, 3> handles;
    auto handle0 = handles.add(1);
    auto handle1 = handles.add(2);
    auto handle2 = handles.add(3);
    REQUIRE_EQ(handles.size(), 3);

    SUBCASE("Gets correct values from multiple entries") {
        REQUIRE_EQ(*handles[handle0], 1);
        REQUIRE_EQ(*handles[handle1], 2);
        REQUIRE_EQ(*handles[handle2], 3);
    }

    SUBCASE("Throw exception when add too many entries") {
        REQUIRE_THROWS_AS(handles.add(103),
                          const resource::Resource_error&);
    }


}
