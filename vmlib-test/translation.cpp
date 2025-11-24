#include <catch2/catch_amalgamated.hpp>

#include "../vmlib/mat44.hpp"
#include "../vmlib/vec4.hpp"

using Catch::Approx;

TEST_CASE( "Translation matrix", "[mat44][translation]" )
{
        static constexpr float kEps_ = 1e-6f;
        using Catch::Matchers::WithinAbs;

        Vec3f const offset{ 3.f, -2.f, 5.f };
        auto const t = make_translation( offset );

        SECTION( "Matrix layout" )
        {
                REQUIRE_THAT( (t[0,3]), WithinAbs( offset.x, kEps_ ) );
                REQUIRE_THAT( (t[1,3]), WithinAbs( offset.y, kEps_ ) );
                REQUIRE_THAT( (t[2,3]), WithinAbs( offset.z, kEps_ ) );

                REQUIRE( t[3,0] == Approx( 0.f ) );
                REQUIRE( t[3,1] == Approx( 0.f ) );
                REQUIRE( t[3,2] == Approx( 0.f ) );
                REQUIRE( t[3,3] == Approx( 1.f ) );
        }

        SECTION( "Transforms points" )
        {
                Vec4f const point{ 1.f, 2.f, 3.f, 1.f };
                auto const transformed = t * point;

                REQUIRE( transformed.x == Approx( point.x + offset.x ) );
                REQUIRE( transformed.y == Approx( point.y + offset.y ) );
                REQUIRE( transformed.z == Approx( point.z + offset.z ) );
                REQUIRE( transformed.w == Approx( 1.f ) );
        }
}

