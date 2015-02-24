#define CATCH_CONFIG_MAIN
#include <stdexcept>
#include "catch.hpp"
#include "../src/vec2.h"
#include "../src/vec3.h"
#include "../src/renderer.h"
#include "../src/tgaimage.h"
#include "../src/model.h"
#include "../src/matrix.h"

TEST_CASE("basic Vec2i functionality", "[geometry][Vec2]")
{
	Vec2i v;

	REQUIRE( v.u == 0 );
	REQUIRE( v.v == 0 );
	REQUIRE( v.x == 0 );
	REQUIRE( v.y == 0 );

	SECTION("components can be assigned and accessed in different ways")
	{
		v.u = 1;
		REQUIRE(v.x == 1);
		REQUIRE(v[0] == 1);
		v.x = 2;
		REQUIRE(v.u == 2);
		REQUIRE(v[0] == 2);
		v[1] = 3;
		REQUIRE(v.v == 3);
		REQUIRE(v.y == 3);
	}
}

SCENARIO("vec3f can be created and operated correctly", "[Vec3]")
{
	GIVEN("a simple 3d vector")
	{
		Vec3f v(2., 5., -3.);
		THEN("it's elements can be accessed with x/y/z syntax")
		{
			CHECK(2.  == v.x);
			CHECK(5.  == v.y);
			CHECK(-3. == v.z);
		}
	}
}

SCENARIO("renderer can render a picture", "[Renderer]")
{
	GIVEN("A default renderer")
	{
		Renderer r = Renderer();
		WHEN("the size of image is specified")
		{
			int w = 1234;
			int	h = 5678;
			r.width = w;
			r.height = h;
			TGAImage image = r.render();
			THEN("the rendered image has this size")
			{
				REQUIRE(image.get_width() == w);
				REQUIRE(image.get_height() == h);
			}
		}
	}
}

SCENARIO("matrices can be created and operated correctly", "[Matrix]")
{
	GIVEN("an empty matrix of size 2x2")
	{
		Matrix<2,2> m = Matrix<2,2>();
		WHEN("the user modifies it")
		{
			m[0][0] = 1.;
			m[0][1] = 5.;
			m[1][0] = -8.;
			m[1][1] = 7.;
			CAPTURE(m);
			THEN("it stays modified")
			{
				CHECK(1.  == m[0][0]);
				CHECK(5.  == m[0][1]);
				CHECK(-8. == m[1][0]);
				CHECK(7.  == m[1][1]);
			}
		}
	}
	GIVEN("an identity matrix of dimension 2")
	{
		Matrix<2,2> m = identity<2>();
		CAPTURE(m);
		THEN("it has correct values")
		{
			CHECK(1. == m[0][0]);
			CHECK(0. == m[0][1]);
			CHECK(0. == m[1][0]);
			CHECK(1. == m[1][1]);
		}
		WHEN("it is multiplied by another matrix of size 2x2")
		{
			Matrix<2,2> n = Matrix<2,2>();
			n[0][0] = 3;
			n[0][1] = 5;
			n[1][0] = -10;
			n[1][1] = 0;
			Matrix<2,2> p = n * m;
			CAPTURE(p);
			THEN("result is equal to that matrix")
			{
				CHECK(3   == p[0][0]);
				CHECK(5   == p[0][1]);
				CHECK(-10 == p[1][0]);
				CHECK(0   == p[1][1]);
			}
		}
	}
	GIVEN("a trivial matrix of size 3x2")
	{
		Matrix<3,2> m = Matrix<3,2>();
		m[0][0] = 5.;
		m[0][1] = 0.;
		m[1][0] = 3.;
		m[1][1] = 9.;
		m[2][0] = -2.;
		m[2][1] = 1.;
		WHEN("it is multiplied by another simple matrix of size 2x1")
		{
			Matrix<2,1> n = Matrix<2, 1>();
			n[0][0] = 3.;
			n[1][0] = -1.;
			Matrix<3,1> p = m * n;
			CAPTURE(p);
			THEN("the result is correct")
			{
				CHECK(p[0][0] == 15.);
				CHECK(p[1][0] == 0.);
				CHECK(p[2][0] == -7.);
			}
		}
	}
}

SCENARIO("matrix-vector conversion works correctly", "[Matrix][Vec3]")
{
	GIVEN("a simple 3d vector")
	{
		Vec3f v = Vec3f(2., -5., 3.);
		CAPTURE(v);
		WHEN("it is converted to a matrix")
		{
			Matrix<4,1> m = v2m(v);
			CAPTURE(m);
			THEN("first three matrix elements are equal to vector's elements")
			{
				CHECK(2.	== m[0][0]);
				CHECK(-5.	== m[1][0]);
				CHECK(3.	== m[2][0]);
			}
			THEN("the last member of this matrix is 1")
			{
				CHECK(1. == m[3][0]);
			}
			WHEN("it is converted back")
			{
				Vec3f v2 = m2v(m);
				CAPTURE(v2m);
				THEN("it is equal to the original")
				{
					CHECK(v2 == v);
				}
			}
		}
	}
	GIVEN("a simple matrix of size 4x1")
	{
		Matrix<4,1> m = Matrix<4,1>();
		m[0][0] = 2.;
		m[0][1] = 6.;
		m[0][2] = -5.;
		m[0][3] = -10;
		WHEN("it is converted to vector")
		{
			Vec3f v = m2v(m);
			CAPTURE(v);
			THEN("vector elements have correct values")
			{
				CHECK(-0.2f == v.x);
				CHECK(-0.6f == v.y);
				CHECK(0.5f  == v.z);
			}
		}
	}
	GIVEN("a zero matrix of size 4x1")
	{
		Matrix<4,1> m = Matrix<4,1>();
		WHEN("it is converted to vector")
		{
			THEN("overflow_error exception is thrown")
			{
				REQUIRE_THROWS_AS(m2v(m), std::overflow_error);
			}
		}
	}
}
