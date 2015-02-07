#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : _verts(), _faces()
{
	std::ifstream in;
	in.open (filename, std::ifstream::in);
	if (in.fail())
	{
		return;
	}
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		// reading vertice lines
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vec3f v;
			for (int i = 0; i < 3; i++)
			{
				iss >> v.raw[i];
			}
			_verts.push_back(v);
		}
		// reading vertex normals
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash;
			Vec3f n;
			for (int i = 0; i < 3; i++)
			{
				iss >> n.raw[i];
			}
			_norms.push_back(n);
		}
		// reading face lines
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<int> f;
			int itrash, idx;
			iss >> trash;
			while (iss >> idx >> trash >> itrash  >> trash >> itrash)
			{
				idx--;
				f.push_back(idx);
			}
			_faces.push_back(f);
		}
	}
	std::cerr
		<< "# v# " << _verts.size()
		<< " f# " << _faces.size()
		<< " vn# " << _norms.size()
		<< std::endl;
}

int Model::nverts()
{
	return (int)_verts.size();
}

int Model::nfaces()
{
	return (int)_faces.size();
}

std::vector<int> Model::face(int idx)
{
	return _faces[idx];
}

Vec3f Model::vert(int i)
{
	return _verts[i];
}

Vec3f Model::norm(int i)
{
	return _norms[i];
}
