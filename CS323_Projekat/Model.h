#pragma once
#pragma warning(disable:4996)
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <fstream>
#include <vector>
#include <string>

#include "Vec3.h"
#include "Vec2.h"

class Model
{
private:
	class Face
	{
	public:
		int edge;
		int* vertices;
		int* texcoords;
		int normal;

		Face(int edge, int* vertices, int* texcoords, int normal = -1)
			:
			edge(edge),
			vertices(vertices),
			texcoords(texcoords),
			normal(normal)
		{
		}
	};
	std::vector<float*> vertices;
	std::vector<float*> texcoords;
	std::vector<float*> normals;
	std::vector<Face> faces;
	GLuint list;
public:
	void LoadModel(const std::string filename)
	{
		std::string line;
		std::vector<std::string> lines;

		std::ifstream in(filename);

		if (!in.is_open())
		{
			std::printf("Cannot load model: %s\n", filename);
			return;
		}

		while (!in.eof())
		{
			std::getline(in, line);
			lines.push_back(line);
		}
		in.close();

		float a, b, c;
		for (std::string &str : lines)
		{
			if (str[0] == 'v')
			{
				if (str[1] == ' ')
				{
					sscanf(str.c_str(), "v %f %f %f", &a, &b, &c);
					vertices.push_back(new float[3]{ a, b, c });
				}
				if (str[1] == 't')
				{
					sscanf(str.c_str(), "vt %f %f", &a, &b);
					texcoords.push_back(new float[2]{ a, b});
				}
				if (str[1] == 'n')
				{
					sscanf(str.c_str(), "vn %f %f %f", &a, &b, &c);
					normals.push_back(new float[3]{ a, b, c });
				}
			}
			if (str[0] == 'f')
			{
				int v0, v1, v2, t0, t1, t2, n;
				sscanf(str.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
				int* vert = new int[3] {v0 - 1, v1 - 1, v2 - 1};
				faces.push_back(Face(3, vert, NULL, n - 1));	
			}
		}
		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		for (Face &face : faces)
		{
			if (face.normal != -1)
			{
				glNormal3fv(normals[face.normal]);
			}
			else
			{
				glDisable(GL_LIGHTING);
			}

			glBegin(GL_POLYGON);
				for (int i = 0; i < face.edge; i++)
				{
					glVertex3fv(vertices[face.vertices[i]]); 
				}
			glEnd();
			if (face.normal == -1)
			{
				glEnable(GL_LIGHTING);
			}
		}
		glEndList();

		printf("Model is printed: %s", filename.c_str());

		for (float* f : vertices)
		{
			delete f;
		}
		vertices.clear();
		for (float* f : texcoords)
		{
			delete f;
		}
		texcoords.clear();
		for (float* f : normals)
		{
			delete f;
		}
		normals.clear();
	}

	void DrawModel()
	{
		glCallList(list);
	}

};