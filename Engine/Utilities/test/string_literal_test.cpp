#include "doctest.h"
#include "bolder/string_literal.hpp"

using namespace bolder;

TEST_CASE("String literal") {
    String_literal a {"Hello world!/n"};
}
