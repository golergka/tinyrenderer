#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model
{
private:
	std::vector<Vec3f>				_verts;
	std::vector<std::vector<int> >	_faces;
	std::vector<Vec3f>				_norms;
	std::vector<Vec2f>				_uv;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	Vec3f norm(int i);
	std::vector<int> face(int idx);
};

#endif // __MODEL_H__
