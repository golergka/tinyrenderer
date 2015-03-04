#include <cmath>
#include "renderer.h"

Renderer::Renderer() : width(800), height(800), models(), lights() { }

TGAImage Renderer::render()
{
	// Creating the _image
	_image = TGAImage(width, height, TGAImage::RGB);

	// Creating _zbuffer
	_zbuffer = new int[width*height];
	for(int i = 0; i < width*height; i++)
	{
		// Minimum value by default
		_zbuffer[i] = std::numeric_limits<int>::min();
	}

	// Prepare projection matrix
	_projection_matrix = identity<4>();
	_projection_matrix = _projection_matrix * move_by(Vec3f(1,0,1));
	EulerAngles cameraRotation = EulerAngles(
			- M_PI / 4.f,
			- M_PI / 2.f,
			0
		);
	_projection_matrix = _projection_matrix * cameraRotation.get_rotation();
	Matrix<4,4> perspective = identity<4>();
	perspective[3][2] = -0.5f;
	_projection_matrix = _projection_matrix * perspective;

	// Rendering the models
	for (int i = 0; i < models.size(); i++)
	{
		render_model(models[i]);
	}

	delete _zbuffer;
	_image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	return _image;
}

float Renderer::light_intensity(Vec3f normal)
{
	float result = 0.;
	for(int i = 0; i < lights.size(); i++)
	{
		result += normal * lights[i];
	}
	return result;
}

Vec3i Renderer::world_to_screen_space(Vec3f v)
{
	Matrix<4,1> m = v2m(v);
	Vec3f r = m2v(_projection_matrix * m);
	return Vec3i(
			(r.x + 1.) * (width / 2.),
			(r.y + 1.) * (height / 2.),
			r.z
		);
}

void Renderer::render_model(Model& model)
{
	for(int i = 0; i < model.nfaces(); i++)
	{
		std::vector<Vec3i> face = model.face(i);
		Vec3f v0 = model.vert(face[0][0]);
		Vec3f v1 = model.vert(face[1][0]);
		Vec3f v2 = model.vert(face[2][0]);
		Vec3f normal = ((v1 - v0)^(v2 - v0)).normalize();
		float intensity = light_intensity(normal);
		if (intensity > 0)
		{
			draw_triangle(
					model.vert(face[0][0]),
					model.vert(face[1][0]),
					model.vert(face[2][0]),
					model.uv(i, 0),
					model.uv(i, 1),
					model.uv(i, 2),
					model,
					intensity
				);
		}
	}
}

void Renderer::draw_triangle(
		Vec3f p0,
		Vec3f p1,
		Vec3f p2,
		Vec2i u0,
		Vec2i u1,
		Vec2i u2,
		const Model& model,
		float intensity
	)
{
	Vec3i t0 = world_to_screen_space(p0);
	Vec3i t1 = world_to_screen_space(p1);
	Vec3i t2 = world_to_screen_space(p2);
	if (t0.y > t1.y)
	{
		std::swap(t0, t1);
		std::swap(u0, u1);
	}
	if (t0.y > t2.y)
	{
		std::swap(t0, t2);
		std::swap(u0, u2);
	}
	if (t1.y > t2.y)
	{
		std::swap(t1, t2);
		std::swap(u1, u2);
	}

	int total_height = t2.y - t0.y;
	for (int y = 0; y < total_height; y++)
	{
		bool second_half = y > t1.y - t0.y || t1.y == t0.y;
		int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		float alpha = (float) y / total_height;
		float beta  = (float) (y - (second_half ? t1.y - t0.y : 0)) / segment_height;
		Vec3i A	  = t0 + (t2 - t0) * alpha;
		Vec2i uvA = u0 + (u2 - u0) * alpha;
		Vec3i B	  = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
		Vec2i uvB = second_half ? u1 + (u2 - u1) * beta : u0 + (u1 - u0) * beta;
		if (A.x > B.x)
		{
			std::swap(A, B);
			std::swap(uvA, uvB);
		}
		for (int x = A.x; x < B.x; x++)
		{
			float phi = B.x == A.x ? 1. : (float) (x - A.x) / (float) (B.x - A.x);
			Vec3i P = Vec3i(
					x, 
					y + t0.y, 
					A.z + (B.z - A.z) * phi
				);
			if (in_bounds(P.x,P.y))
			{
				Vec2i uvP = uvA + (uvB - uvA) * phi;
				int idx = P.x + P.y * width;
				if (_zbuffer[idx] < P.z)
				{
					_zbuffer[idx] = P.z;
					TGAColor color = model.diffuse(uvP);
					_image.set(
							P.x, 
							P.y, 
							TGAColor(
								color.r * intensity,
								color.g * intensity,
								color.b * intensity,
								color.a
							)
						);
				}
			}
		}
	}
}

bool Renderer::in_bounds(const int w, const int h) const
{
	return w >= 0 && w < width && h >= 0 && h < height;
}
