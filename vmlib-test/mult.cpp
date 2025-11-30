#define CATCH_CONFIG_MAIN
#include <catch2/catch_amalgamated.hpp>

#include <cmath>
#include "../vmlib/mat44.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/vec4.hpp"
using Catch::Approx;

static Mat44f make_sequential_matrix()
{
	Mat44f m{};
	float x = 1.f;
	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			m[i, j] = x;
			x += 1.f;
		}
	}
	return m;
}

TEST_CASE("Mat44f multiplied by identity leaves matrix unchanged")
{
	Mat44f A = make_sequential_matrix();
	Mat44f I = kIdentity44f;

	Mat44f R1 = A * I;
	Mat44f R2 = I * A;

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			REQUIRE(R1[i, j] == Approx(A[i, j]));
			REQUIRE(R2[i, j] == Approx(A[i, j]));
		}
	}
}
TEST_CASE("Mat44f multiply simple known matrices")
{
	Mat44f A{};
	Mat44f B{};

	// A = [ 1 2 ; 3 4 ]
	A[0, 0] = 1.f; A[0, 1] = 2.f;
	A[1, 0] = 3.f; A[1, 1] = 4.f;

	// B = [ 5 6 ; 7 8 ]
	B[0, 0] = 5.f; B[0, 1] = 6.f;
	B[1, 0] = 7.f; B[1, 1] = 8.f;

	Mat44f R = A * B;



	REQUIRE(R[0, 0] == Catch::Approx(19.f));
	REQUIRE(R[0, 1] == Catch::Approx(22.f));
	REQUIRE(R[1, 0] == Catch::Approx(43.f));
	REQUIRE(R[1, 1] == Catch::Approx(50.f));
}


TEST_CASE("Mat44f * Vec4f with identity leaves vector unchanged")
{
	Mat44f I = kIdentity44f;
	Vec4f v{ 1.f, -2.f, 3.f, 1.f };

	Vec4f r = I * v;

	REQUIRE(r[0] == Approx(1.f));
	REQUIRE(r[1] == Approx(-2.f));
	REQUIRE(r[2] == Approx(3.f));
	REQUIRE(r[3] == Approx(1.f));
}

TEST_CASE("Mat44f * Vec4f applies translation")
{
	Vec3f t{ 5.f, -1.f, 2.f };
	Mat44f T = make_translation(t);

	Vec4f p{ 1.f, 2.f, 3.f, 1.f };
	Vec4f r = T * p;

	REQUIRE(r[0] == Approx(1.f + t[0]));
	REQUIRE(r[1] == Approx(2.f + t[1]));
	REQUIRE(r[2] == Approx(3.f + t[2]));
	REQUIRE(r[3] == Approx(1.f));
}
