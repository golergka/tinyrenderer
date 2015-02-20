#include <math.h>
#include <iostream>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "renderer.h"

int main(int argc, char** argv)
{
	// Loading the model
	Renderer renderer = Renderer();
	renderer.models.push_back(2 == argc ?
			Model(argv[1]) :
			Model("obj/head.obj")
		);

	// Setting up the light direction
	renderer.lights.push_back(Vec3f(0., 0., 1.));

	// Rendering
	TGAImage image = renderer.render();

	// Outputing the image to file
	image.write_tga_file("output.tga");
	return 0;
}
