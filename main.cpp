#include <math.h>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue	 = TGAColor(0,   0,   255, 255);

Model *model = NULL;
const int width		= 800;
const int height	= 800;

void line(
		Vec2i		t0, 
		Vec2i		t1, 
		TGAImage&	image, 
		TGAColor	color
	)
{
	bool steep = false;
	if (std::abs(t0.x - t1.x) < std::abs(t0.y - t1.y))
	{
		std::swap(t0.x, t0.y);
		std::swap(t1.x, t1.y);
		steep = true;
	}
	if (t0.x > t1.x)
	{
		std::swap(t0, t1);
	}
	int dx = t1.x - t0.x;
	int dy = t1.y - t0.y;
	int derror2 = std::abs(dy)*2;
	int error2 = 0;
	int y = t0.y;
	for(int x = t0.x; x <= t1.x; x++)
	{
		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += (t1.y > t0.y ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void triangle(
		Vec2i		t0,
		Vec2i		t1,
		Vec2i		t2,
		TGAImage&	image,
		TGAColor	color
	)
{
	if (t0.y > t1.y)
	{
		std::swap(t0, t1);
	}
	if (t0.y > t2.y)
	{
		std::swap(t0, t2);
	}
	if (t1.y > t2.y)
	{
		std::swap(t1, t2);
	}

	int total_height = t2.y - t0.y;
	int segment_height = t1.y - t0.y + 1;

	for(int y = t0.y; y <= t1.y; y++)
	{
		float alpha = (float) (y - t0.y) / total_height;
		float beta  = (float) (y - t0.y) / segment_height;
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = t0 + (t1 - t0) * beta;
		line(A, B, image, color);
	}

	segment_height = t2.y - t1.y + 1;
	for(int y = t1.y; y <= t2.y; y++)
	{
		float alpha = (float) (y - t0.y) / total_height;
		float beta  = (float) (y - t1.y) / segment_height;
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = t1 + (t2 - t1) * beta;
		line (A, B, image, color);
	}
	/*
	line(t0, t1, image, color);
	line(t1, t2, image, color);
	line(t0, t2, image, color);
	*/
}

Vec2i to_screen_space(Vec3f v)
{
	return Vec2i(
			(v.x + 1.) * (width / 2.),
			(v.y + 1.) * (height / 2.)
		);
}

int main(int argc, char** argv)
{
	if (2 == argc)
	{
		model = new Model(argv[1]);
	}
	else
	{
		model = new Model("obj/head.obj");
	}
	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec3f v0 = model->vert(face[0]);
		Vec3f v1 = model->vert(face[1]);
		Vec3f v2 = model->vert(face[2]);
		triangle(
				to_screen_space(v0),
				to_screen_space(v1),
				to_screen_space(v2),
				image,
				TGAColor(rand()%255, rand()%255, rand()%255, 255)
			);
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
