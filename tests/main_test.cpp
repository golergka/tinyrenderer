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

SCENARIO("matrices can be created correctly", "[Matrix]")
{
	GIVEN("an identity matrix of dimension 2")
	{
		Matrix m = Matrix::identity(2);
		WHEN("the user checks size of the matrix")
		{
			THEN("it has 2 rows")
			{
				REQUIRE(2 == m.nrows());
			}
			THEN("it has 2 columns")
			{
				REQUIRE(2 == m.ncols());
			}
		}
		WHEN("the user checks values of the matrix")
		{
			for (int x = 0; x < m.nrows(); x++)
			{
				for (int y = 0; y < m.ncols(); y++)
				{
					float v = m[x][y];
					if (x == y)
					{
						THEN("it is 1 on main diagonal")
						{
							REQUIRE(v == 1.);
						}
					}
					else
					{
						THEN("it is 0 outside the main diagonal")
						{
							REQUIRE(v == 0.);
						}
					}
				}
			}
		}
		WHEN("the user edits the matrix")
		{
			float n = 3.;
			m[0][1] = n;
			THEN("it saves the new value")
			{
				REQUIRE(m[0][1] == n);
			}
		}
		WHEN("it is multiplied by another matrix of size 2x2")
		{
			Matrix n = Matrix(2, 2);
			n[0][0] = 3;
			n[0][1] = 5;
			n[1][0] = -10;
			n[1][1] = 0;
			Matrix p = n * m;
			THEN("result is equal to that matrix")
			{
				for(int x = 0; x < m.nrows(); x++)
				{
					for(int y = 0; y < m.ncols(); y++)
					{
						REQUIRE(n[x][y] == p[x][y]);
					}
				}
			}
		}
		WHEN("it is multiplied by another matrix of the size 3x3")
		{
			Matrix n = Matrix(3, 3);
			THEN("invalid_argument exception is thrown")
			{
				REQUIRE_THROWS_AS(m * n, std::invalid_argument);
			}
		}
	}
	GIVEN("a trivial matrix of size 3x2")
	{
		Matrix m = Matrix(3, 2);
		m[0][0] = 5.;
		m[0][1] = 0.;
		m[1][0] = 3.;
		m[1][1] = 9.;
		m[2][0] = -2.;
		m[2][1] = 1.;
		WHEN("it is multiplied by another simple matrix of size 2x1")
		{
			Matrix n = Matrix(2, 1);
			n[0][0] = 3.;
			n[1][0] = -1.;
			Matrix p = m * n;
			CAPTURE(p);
			THEN("the result has size 3x1")
			{
				CHECK(3 == p.nrows());
				CHECK(1 == p.ncols());
			}
			THEN("the result is correct")
			{
				CHECK(p[0][0] == 15.);
				CHECK(p[1][0] == 0.);
				CHECK(p[2][0] == -7.);
			}
		}
	}
}
