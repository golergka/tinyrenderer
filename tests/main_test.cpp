#define CATCH_CONFIG_MAIN
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
	GIVEN("An identity matrix of dimension 2")
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
	}
}
