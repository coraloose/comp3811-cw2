#include <catch2/catch_amalgamated.hpp>

#include <numbers>

#include "../vmlib/mat44.hpp"
#include "../vmlib/vec4.hpp"

TEST_CASE( "Rotation matrices", "[mat44][rotation]" )
{
        using Catch::Matchers::WithinAbs;
        static constexpr float kEps_ = 1e-6f;
        static constexpr float kPiOver2_ = std::numbers::pi_v<float> / 2.f;

        SECTION( "Rotate around X" )
        {
                auto const m = make_rotation_x( kPiOver2_ );
                Vec4f const v{ 0.f, 1.f, 0.f, 1.f };
                auto const result = m * v;

                REQUIRE_THAT( (result.x), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.y), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.z), WithinAbs( 1.f, kEps_ ) );
                REQUIRE_THAT( (result.w), WithinAbs( 1.f, kEps_ ) );
        }

        SECTION( "Rotate around Y" )
        {
                auto const m = make_rotation_y( kPiOver2_ );
                Vec4f const v{ 1.f, 0.f, 0.f, 1.f };
                auto const result = m * v;

                REQUIRE_THAT( (result.x), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.y), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.z), WithinAbs( -1.f, kEps_ ) );
                REQUIRE_THAT( (result.w), WithinAbs( 1.f, kEps_ ) );
        }

        SECTION( "Rotate around Z" )
        {
                auto const m = make_rotation_z( kPiOver2_ );
                Vec4f const v{ 0.f, 1.f, 0.f, 1.f };
                auto const result = m * v;

                REQUIRE_THAT( (result.x), WithinAbs( -1.f, kEps_ ) );
                REQUIRE_THAT( (result.y), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.z), WithinAbs( 0.f, kEps_ ) );
                REQUIRE_THAT( (result.w), WithinAbs( 1.f, kEps_ ) );
        }
}

