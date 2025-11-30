#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
// SOLUTION_TAGS: gl-(ex-[^12]|cw-2|resit)

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

/** Mat44f: 4x4 matrix with floats
 *
 * See vec2f.hpp for discussion. Similar to the implementation, the Mat44f is
 * intentionally kept simple and somewhat bare bones.
 *
 * The matrix is stored in row-major order (careful when passing it to OpenGL).
 *
 * The overloaded operator [] allows access to individual elements. Example:
 *    Mat44f m = ...;
 *    float m12 = m[1,2];
 *    m[0,3] = 3.f;
 *
 * (Multi-dimensionsal subscripts in operator[] is a C++23 feature!)
 *
 * The matrix is arranged as:
 *
 *   ⎛ 0,0  0,1  0,2  0,3 ⎞
 *   ⎜ 1,0  1,1  1,2  1,3 ⎟
 *   ⎜ 2,0  2,1  2,2  2,3 ⎟
 *   ⎝ 3,0  3,1  3,2  3,3 ⎠
 */
struct Mat44f
{
	float v[16];

	constexpr
	float& operator[] (std::size_t aI, std::size_t aJ) noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
	constexpr
	float const& operator[] (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
};

// Identity matrix
constexpr Mat44f kIdentity44f = { {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
} };

// Common operators for Mat44f.
// Note that you will need to implement these yourself.

constexpr
Mat44f operator*( Mat44f const& aLeft, Mat44f const& aRight ) noexcept
{
	Mat44f ret{};

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			float sum = 0.f;
			for (std::size_t k = 0; k < 4; ++k)
			{
				sum += aLeft[i, k] * aRight[k, j];
			}
			ret[i, j] = sum;
		}
	}

	return ret;
}

constexpr
Vec4f operator*( Mat44f const& aLeft, Vec4f const& aRight ) noexcept
{
	Vec4f ret{ 0.f, 0.f, 0.f, 0.f };

	for (std::size_t i = 0; i < 4; ++i)
	{
		float sum = 0.f;
		for (std::size_t k = 0; k < 4; ++k)
		{
			sum += aLeft[i, k] * aRight[k];
		}
		ret[i] = sum;
	}

	return ret;
}

// Functions:

Mat44f invert( Mat44f const& aM ) noexcept;

inline
Mat44f transpose( Mat44f const& aM ) noexcept
{
	Mat44f ret;
	for( std::size_t i = 0; i < 4; ++i )
	{
		for( std::size_t j = 0; j < 4; ++j )
			ret[j,i] = aM[i,j];
	}
	return ret;
}

inline
Mat44f make_rotation_x( float aAngle ) noexcept
{
	Mat44f ret = kIdentity44f;

	const float c = std::cos(aAngle);
	const float s = std::sin(aAngle);

	// Rows 1 and 2 form the Y–Z rotation block
	ret[1, 1] = c;
	ret[1, 2] = -s;
	ret[2, 1] = s;
	ret[2, 2] = c;

	return ret;
}


inline
Mat44f make_rotation_y( float aAngle ) noexcept
{
	Mat44f ret = kIdentity44f;

	const float c = std::cos(aAngle);
	const float s = std::sin(aAngle);

	// Rows 0 and 2 form the X–Z rotation block
	ret[0, 0] = c;
	ret[0, 2] = s;
	ret[2, 0] = -s;
	ret[2, 2] = c;

	return ret;
}

inline
Mat44f make_rotation_z( float aAngle ) noexcept
{
	Mat44f ret = kIdentity44f;

	const float c = std::cos(aAngle);
	const float s = std::sin(aAngle);

	// Rows 0 and 1 form the X–Y rotation block
	ret[0, 0] = c;
	ret[0, 1] = -s;
	ret[1, 0] = s;
	ret[1, 1] = c;

	return ret;
}

inline
Mat44f make_translation( Vec3f aTranslation ) noexcept
{
	Mat44f ret = kIdentity44f;

	ret[0, 3] = aTranslation[0]; // tx
	ret[1, 3] = aTranslation[1]; // ty
	ret[2, 3] = aTranslation[2]; // tz

	return ret;
}
inline
Mat44f make_scaling( float aSX, float aSY, float aSZ ) noexcept
{
	Mat44f ret = kIdentity44f;

	ret[0, 0] = aSX;
	ret[1, 1] = aSY;
	ret[2, 2] = aSZ;

	return ret;
}

inline
Mat44f make_perspective_projection( float aFovInRadians, float aAspect, float aNear, float aFar ) noexcept
{
	Mat44f ret{}; // zero-initialised

	const float halfFov = 0.5f * aFovInRadians;
	const float t = std::tan(halfFov);
	const float n = aNear;
	const float f = aFar;

	assert(aAspect != 0.f);
	assert(f != n);

	// Row 0
	ret[0, 0] = 1.0f / (aAspect * t);
	ret[0, 1] = 0.0f;
	ret[0, 2] = 0.0f;
	ret[0, 3] = 0.0f;

	// Row 1
	ret[1, 0] = 0.0f;
	ret[1, 1] = 1.0f / t;
	ret[1, 2] = 0.0f;
	ret[1, 3] = 0.0f;

	// Row 2
	ret[2, 0] = 0.0f;
	ret[2, 1] = 0.0f;
	ret[2, 2] = -(f + n) / (f - n);
	ret[2, 3] = -(2.0f * f * n) / (f - n);

	// Row 3
	ret[3, 0] = 0.0f;
	ret[3, 1] = 0.0f;
	ret[3, 2] = -1.0f;
	ret[3, 3] = 0.0f;

	return ret;
}

#endif // MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
