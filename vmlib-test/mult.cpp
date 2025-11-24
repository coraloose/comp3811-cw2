#include <catch2/catch_amalgamated.hpp>

#include "../vmlib/mat44.hpp"
#include "../vmlib/vec4.hpp"

TEST_CASE( "Matrix multiplication", "[mat44][mult]" )
{
        Mat44f const a{ {
                1.f, 2.f, 3.f, 4.f,
                5.f, 6.f, 7.f, 8.f,
                9.f, 8.f, 7.f, 6.f,
                5.f, 4.f, 3.f, 2.f
        } };

        Mat44f const b{ {
                2.f, 0.f, 1.f, 0.f,
                1.f, 2.f, 0.f, 1.f,
                0.f, 1.f, 2.f, 0.f,
                1.f, 0.f, 0.f, 2.f
        } };

        Mat44f const expected{ {
                 8.f,  7.f,  7.f, 10.f,
                24.f, 19.f, 19.f, 22.f,
                32.f, 23.f, 23.f, 20.f,
                16.f, 11.f, 11.f,  8.f
        } };

        auto const result = a * b;

        for( std::size_t i = 0; i < 4; ++i )
        {
                for( std::size_t j = 0; j < 4; ++j )
                        REQUIRE( result[i,j] == Approx( expected[i,j] ) );
        }
}

TEST_CASE( "Matrix vector multiplication", "[mat44][mult]" )
{
        Mat44f const m{ {
                1.f, 2.f, 3.f, 4.f,
                5.f, 6.f, 7.f, 8.f,
                9.f, 8.f, 7.f, 6.f,
                5.f, 4.f, 3.f, 2.f
        } };

        Vec4f const v{ 1.f, 2.f, 3.f, 1.f };
        Vec4f const expected{ 18.f, 46.f, 52.f, 24.f };

        auto const result = m * v;

        REQUIRE( result.x == Approx( expected.x ) );
        REQUIRE( result.y == Approx( expected.y ) );
        REQUIRE( result.z == Approx( expected.z ) );
        REQUIRE( result.w == Approx( expected.w ) );
}

