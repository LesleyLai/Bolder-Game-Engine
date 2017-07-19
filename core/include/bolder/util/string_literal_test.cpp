#include "doctest.h"
#include "util/string_literal.hpp"

using namespace bolder::utility;

TEST_CASE("String literal") {
    String_literal a {"Hello world!/n"};
}
