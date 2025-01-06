#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <map>

#include "Vec3.h"
#include "Vec2.h"

namespace Components{

	struct Transform
	{
		Vef3 position;
		Vef3 scale;
		Vef3 rotation;
	};

	struct Mesh
	{
		struct Material
		{
			float* ambient;
			float* diffuse;
			float* specular;
			GLuint texture;
		};

		struct Face
		{
			int edge;
			int* vertices;
			int* texcoords;
			int normal;
		};

		std::string prefix;
		std::vector<Material> materials;
		std::map<std::string, int> map_material;

		std::vector<float*> vertices;
		std::vector<float*> texcoords;
		std::vector<float*> normals;
		std::vector<Face> faces;
		GLuint list;
	};

	struct Collider
	{

	};

	struct Velocity
	{
		Vef3 velocity;
	};
}