#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/geometry.h"
#include "../src/renderer.h"
#include "../src/tgaimage.h"
#include "../src/model.h"

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
