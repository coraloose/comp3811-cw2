#include <catch2/catch_amalgamated.hpp>

#include <cmath>
#include "../vmlib/mat44.hpp"
#include "../vmlib/vec4.hpp"
using Catch::Approx;

TEST_CASE("Rotation around X by 90 degrees rotates Y into Z")
{
	const float pi = 3.14159265358979323846f;
	const float angle = 0.5f * pi;

	Mat44f R = make_rotation_x(angle);
	Vec4f v{ 0.f, 1.f, 0.f, 1.f };
	Vec4f r = R * v;

	REQUIRE(r[0] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[1] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[2] == Approx(1.f).margin(1e-5f));
	REQUIRE(r[3] == Approx(1.f));
}

TEST_CASE("Rotation around Y by 90 degrees rotates Z into X")
{
	const float pi = 3.14159265358979323846f;
	const float angle = 0.5f * pi;

	Mat44f R = make_rotation_y(angle);
	Vec4f v{ 0.f, 0.f, 1.f, 1.f };
	Vec4f r = R * v;

	REQUIRE(r[0] == Approx(1.f).margin(1e-5f));
	REQUIRE(r[1] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[2] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[3] == Approx(1.f));
}

TEST_CASE("Rotation around Z by 90 degrees rotates X into Y")
{
	const float pi = 3.14159265358979323846f;
	const float angle = 0.5f * pi;

	Mat44f R = make_rotation_z(angle);
	Vec4f v{ 1.f, 0.f, 0.f, 1.f };
	Vec4f r = R * v;

	REQUIRE(r[0] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[1] == Approx(1.f).margin(1e-5f));
	REQUIRE(r[2] == Approx(0.f).margin(1e-5f));
	REQUIRE(r[3] == Approx(1.f));
}
