#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "model.h"
#include "tgaimage.h"
#include "matrix.h"

class Renderer
{
private:
	int*		_zbuffer;
	TGAImage	_image; 

	void		render_model(Model& model);
	float		light_intensity(Vec3f normal);
	Vec3i		world_to_screen_space(Vec3f v);
	void		draw_triangle(
		Vec3f p0,
		Vec3f p1,
		Vec3f p2,
		Vec2i u0,
		Vec2i u1,
		Vec2i u2,
		const Model& model,
		float intensity
	);

public:
	int					width;
	int					height;
	std::vector<Model>	models;
	std::vector<Vec3f>	lights;

	Renderer();

	TGAImage	render();
	bool		in_bounds(const int w, const int h) const;
};

#endif // __RENDERER_H__
