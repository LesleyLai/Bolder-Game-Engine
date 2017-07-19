#include <sstream>

#include "math/angle.hpp"
#include "doctest.h"

using namespace bolder::math;

TEST_CASE("[angle] Radian arithmetics") {
    Radian pi_o_4 {pi/4};
    Radian pi_o_2 {pi/2};

    SUBCASE("Radian unary addition operator") {
        auto pp = pi_o_4;
        pp += pi_o_4;
        REQUIRE_EQ(pp.value(), doctest::Approx(pi_o_2.value()));
    }

    SUBCASE("Radian unary subtraction operator") {
        auto pp = pi_o_2;
        pp -= pi_o_4;
        REQUIRE_EQ(pp.value(), doctest::Approx(pi_o_4.value()));
    }

    SUBCASE("Radian unary multiplication operator") {
        auto pp = pi_o_4;
        pp *= 2;
        REQUIRE_EQ(pp.value(), doctest::Approx(pi_o_2.value()));
    }

    SUBCASE("Radian unary division operator") {
        auto pp = pi_o_2;
        pp /= 2;
        REQUIRE_EQ(pp.value(), doctest::Approx(pi_o_4.value()));
    }

    SUBCASE("Negation of radian") {
        REQUIRE_EQ((-pi_o_2).value(), doctest::Approx(-pi_o_2.value()));
    }

    SUBCASE("Radian binary addition operator") {
        REQUIRE_EQ((pi_o_4 + pi_o_2).value(), doctest::Approx(pi / 4 * 3));
    }

    SUBCASE("Radian binary minus operator") {
        REQUIRE_EQ((pi_o_2 - pi_o_4).value(), doctest::Approx(pi / 4));
    }

    SUBCASE("Radian binary multiply operator") {
        REQUIRE_EQ((pi_o_2 * 2).value(), doctest::Approx(pi));
        REQUIRE_EQ((2 * pi_o_2).value(), doctest::Approx(pi));
    }

    SUBCASE("Radian binary divide operator") {
        REQUIRE_EQ((pi_o_2 / 2).value(), doctest::Approx(pi / 4));
        REQUIRE_EQ(pi_o_2 / pi_o_2, doctest::Approx(1));
    }

}

TEST_CASE("[angle] degree arithmetics") {
    Radian degree_30 {30};
    Radian degree_60 {60};

    SUBCASE("Degree unary addition operator") {
        auto pp = degree_30;
        pp += degree_30;
        REQUIRE_EQ(pp.value(), doctest::Approx(degree_60.value()));
    }

    SUBCASE("Degree unary subtraction operator") {
        auto pp = degree_60;
        pp -= degree_30;
        REQUIRE_EQ(pp.value(), doctest::Approx(degree_30.value()));
    }

    SUBCASE("Degree unary multiplication operator") {
        auto pp = degree_30;
        pp *= 2;
        REQUIRE_EQ(pp.value(), doctest::Approx(degree_60.value()));
    }

    SUBCASE("Negation of degree") {
        REQUIRE_EQ((-degree_30).value(), doctest::Approx(-degree_30.value()));
    }

    SUBCASE("Degree binary addition operator") {
        REQUIRE_EQ((degree_30 + degree_60).value(), doctest::Approx(90));
    }

    SUBCASE("Degree binary minus operator") {
        REQUIRE_EQ((degree_60 - degree_30).value(), doctest::Approx(30));
    }

    SUBCASE("Degree binary multiply operator") {
        REQUIRE_EQ((degree_60 * 2).value(), doctest::Approx(120));
        REQUIRE_EQ((2 * degree_60).value(), doctest::Approx(120));
    }

    SUBCASE("Degree binary divide operator") {
        REQUIRE_EQ((degree_60 / 2).value(), doctest::Approx(30));
        REQUIRE_EQ(degree_60 / degree_30, doctest::Approx(2));
    }
}

TEST_CASE("[angle] Convert between degree and radian") {
    SUBCASE("Degree to radian") {
        Degree d{45};
        Radian r = d;
        REQUIRE_EQ(r.value(), doctest::Approx(pi / 4));
    }

    SUBCASE("Radian to degree") {
        Radian r{pi / 2};
        Degree d = r;
        REQUIRE_EQ(d.value(), doctest::Approx(90));
    }
}

TEST_CASE("[angle] Comparison of degree and radian") {
    SUBCASE("equal") {
        REQUIRE_EQ(Radian{1}, Radian{1});
        REQUIRE_EQ(Degree{1}, Degree{1});
    }

    SUBCASE("not equal") {
        REQUIRE_NE(Radian{2}, Radian{1});
        REQUIRE_NE(Degree{2}, Degree{1});
    }

    SUBCASE("greater than") {
        REQUIRE_GT(Radian{2}, Radian{1});
        REQUIRE_GT(Degree{2}, Degree{1});
    }

    SUBCASE("greater or equal") {
        REQUIRE_GE(Radian{2}, Radian{1});
        REQUIRE_GE(Degree{2}, Degree{2});
    }

    SUBCASE("less than") {
        REQUIRE_LT(Radian{1}, Radian{2});
        REQUIRE_LT(Degree{1}, Degree{2});
    }

    SUBCASE("less or equal") {
        REQUIRE_LE(Radian{1}, Radian{1});
        REQUIRE_LE(Degree{1}, Degree{2});
    }
}

TEST_CASE("[angle] String conversions") {
    std::stringstream ss;

    SUBCASE("Radian string conversion") {
        ss << Radian{pi};
        REQUIRE_EQ(ss.str(), "1_radians");
    }

    SUBCASE("Degree string conversion") {
        ss << Degree{45};
        REQUIRE_EQ(ss.str(), "45_degrees");
    }

}
