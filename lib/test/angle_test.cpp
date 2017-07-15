#include "doctest.h"

constexpr float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

constexpr float degree_to_rad = pi / 180;
constexpr float rad_to_degree = 180 / pi;

class Degree;

class Radian
{
public:
    /// Default constructor
    Radian();

    Radian(Degree degree);

    /// Construct radian from a number
    explicit Radian(float value);

    float value() const;

    Radian& operator+=(Radian rhs);
    Radian& operator-=(Radian rhs);
    Radian& operator*=(float rhs);
    float& operator/=(Radian rhs);

private:
    float value_;
};

class Degree
{
public:
    Degree();

    Degree(Radian radian);

    /// Construct degree from a number
    explicit Degree(float value);

    float value() const;

private:
    float value_;
};

TEST_CASE("Radian arithmetics") {
    Radian pi_o_4 {pi/4};
    Radian pi_o_2 {pi/2};

    SUBCASE("Radian unary addition operator") {
        auto pp = pi_o_4;
        pp += pi_o_4;
        REQUIRE(pp.value() == doctest::Approx(pi_o_2.value()));
    }

    SUBCASE("Radian unary subtraction operator") {
        auto pp = pi_o_2;
        pp -= pi_o_4;
        REQUIRE(pp.value() == doctest::Approx(pi_o_4.value()));
    }

    SUBCASE("Radian unary multiplication operator") {
        auto pp = pi_o_4;
        pp *= 2;
        REQUIRE(pp.value() == doctest::Approx(pi_o_2.value()));
    }

    SUBCASE("Radian unary division operator") {
        auto pp = pi_o_2;
        pp /= pi_o_4;
        REQUIRE(pp.value() == doctest::Approx(2));
    }

    //REQUIRE((pi_o_4 + pi_o_2).value() == doctest::Approx(pi / 4 * 3));
}

TEST_CASE("Convert degree and radian") {

    SUBCASE("Degree to radian") {
        Degree d{45};
        Radian r = d;
        REQUIRE(r.value() == doctest::Approx(pi / 4));
    }

    SUBCASE("Radian to degree") {
        Radian r{pi / 2};
        Degree d = r;
        REQUIRE(d.value() == doctest::Approx(90));
    }
}

Radian::Radian() : value_{0} {}

Radian::Radian(Degree degree) :value_{degree.value() * degree_to_rad}
{
}

Radian::Radian(float value) : value_{value}
{

}

float Radian::value() const
{
    return value_;
}

Radian &Radian::operator+=(Radian rhs)
{
    value_ += rhs.value();
    return *this;
}

Radian &Radian::operator-=(Radian rhs)
{
    value_ -= rhs.value();
    return *this;
}

Radian &Radian::operator*=(float rhs)
{
    value_ *= rhs;
    return *this;
}

float &Radian::operator/=(Radian rhs)
{
    value_ /= rhs.value();
    return value_;
}

Degree::Degree() : value_{0} {}

Degree::Degree(Radian radian) :value_{radian.value() * rad_to_degree}
{

}

Degree::Degree(float value) :value_{value}
{

}

float Degree::value() const
{
    return value_;
}
