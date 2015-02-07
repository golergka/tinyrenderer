#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "tgaimage.h"

class Model
{
private:
	std::vector<Vec3f>					_verts;
	std::vector<std::vector<Vec3i> >	_faces;
	std::vector<Vec3f>					_norms;
	std::vector<Vec2f>					_uv;
	TGAImage							_diffuse;

	void								load_texture(
			std::string filename, 
			const char *suffix, 
			TGAImage &img
		);
public:
	Model(const char *filename);
	~Model();
	int					nverts();
	int					nfaces();
	Vec3f				vert(int i);
	Vec2f				uv(int iface, int nvert);
	Vec3f				norm(int i);
	std::vector<Vec3i>	face(int idx);
};

#endif // __MODEL_H__
