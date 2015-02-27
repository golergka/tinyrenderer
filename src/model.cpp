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
				iss >> v[i];
			}
			_verts.push_back(v);
		}
		// reading vertex normals
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Vec3f n;
			for (int i = 0; i < 3; i++)
			{
				iss >> n[i];
			}
			_norms.push_back(n);
		}
		// reading UV coordinates
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			Vec2f uv;
			for (int i = 0; i < 2; i++)
			{
				iss >> uv[i];
			}
			_uv.push_back(uv);
		}
		// reading face lines
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<Vec3i> f;
			Vec3i tmp;
			iss >> trash;
			while (iss   >> tmp[0]
				>> trash >> tmp[1]
				>> trash >> tmp[2])
			{
				for(int i = 0; i < 3; i++)
				{
					tmp[i]--;
				}
				f.push_back(tmp);
			}
			_faces.push_back(f);
		}
	}
	std::cerr
		<< "# v# " << _verts.size()
		<< " f# " << _faces.size()
		<< " vt# " << _uv.size()
		<< " vn# " << _norms.size()
		<< std::endl;
	load_texture(filename, "_diffuse.tga", _diffuse);
}

Model::~Model() { }

void Model::load_texture(
		std::string filename,
		const char* suffix,
		TGAImage&	img
	)
{
	std::string texfile(filename);
	size_t dot = texfile.find_last_of(".");
	if (dot != std::string::npos)
	{
		texfile = texfile.substr(0, dot) + std::string(suffix);
		std::cerr 
			<< "texture file " << texfile << " loading " 
			<< (img.read_tga_file(texfile.c_str()) ? "ok" : "failed")
			<< std::endl;
		img.flip_vertically();
	}
}

int Model::nverts()
{
	return (int)_verts.size();
}

int Model::nfaces()
{
	return (int)_faces.size();
}

std::vector<Vec3i> Model::face(int idx)
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

Vec2i Model::uv(int iface, int nvert)
{
	int idx = _faces[iface][nvert][1];
	return Vec2i(
			_uv[idx].x * _diffuse.get_width(),
			_uv[idx].y * _diffuse.get_height()
		);
}

TGAColor Model::diffuse(Vec2i uv) const
{
	return _diffuse.get(uv.x, uv.y);
}
