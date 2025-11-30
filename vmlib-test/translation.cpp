#include <catch2/catch_amalgamated.hpp>

#include <cmath>
#include "../vmlib/mat44.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/vec4.hpp"

using Catch::Approx;

TEST_CASE("Translation matrix stores offsets in last column")
{
    Vec3f t{ 2.f, 3.f, 4.f };
    Mat44f T = make_translation(t);

    REQUIRE(T[0, 3] == Approx(2.f));
    REQUIRE(T[1, 3] == Approx(3.f));
    REQUIRE(T[2, 3] == Approx(4.f));
    REQUIRE(T[3, 3] == Approx(1.f));
}

TEST_CASE("Translation transforms homogeneous position vector")
{
    Vec3f t{ -1.f, 5.f, 0.5f };
    Mat44f T = make_translation(t);

    Vec4f p{ 10.f, 0.f, 2.f, 1.f };
    Vec4f r = T * p;

    REQUIRE(r[0] == Approx(10.f + t[0]));
    REQUIRE(r[1] == Approx(0.f + t[1]));
    REQUIRE(r[2] == Approx(2.f + t[2]));
    REQUIRE(r[3] == Approx(1.f));
}

TEST_CASE("Scaling matrix has correct diagonal entries")
{
    Mat44f S = make_scaling(2.f, 3.f, 4.f);

    REQUIRE(S[0, 0] == Approx(2.f));
    REQUIRE(S[1, 1] == Approx(3.f));
    REQUIRE(S[2, 2] == Approx(4.f));
    REQUIRE(S[3, 3] == Approx(1.f));
}

TEST_CASE("Scaling transforms vector components")
{
    Mat44f S = make_scaling(2.f, 3.f, 4.f);
    Vec4f v{ 1.f, -1.f, 0.5f, 1.f };
    Vec4f r = S * v;

    REQUIRE(r[0] == Approx(2.f));    // 1 * 2
    REQUIRE(r[1] == Approx(-3.f));   // -1 * 3
    REQUIRE(r[2] == Approx(2.f));    // 0.5 * 4
    REQUIRE(r[3] == Approx(1.f));
}
