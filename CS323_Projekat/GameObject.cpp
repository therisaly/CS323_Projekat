#include "GameObject.h"

void GameObject::LoadModel(char* p_filename)
{
	ResourceLoader::Load3DS(model, p_filename);
}

void GameObject::RenderObject()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	
	int l_index;

	glColor3f(1.0, 1.0, 0.);

	glBegin(GL_TRIANGLES); 
	for (l_index = 0; l_index < model->polygons_num; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Coordinates of the first vertex
		glVertex3f(model->vertex[model->polygon[l_index].a].x,
			model->vertex[model->polygon[l_index].a].y,
			model->vertex[model->polygon[l_index].a].z); 

		//----------------- SECOND VERTEX -----------------
		// Coordinates of the second vertex
		//float x= model.vertex[ model.polygon[l_index].b ].x;

		glVertex3f(model->vertex[model->polygon[l_index].b].x,
			model->vertex[model->polygon[l_index].b].y,
			model->vertex[model->polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Coordinates of the Third vertex
		glVertex3f(model->vertex[model->polygon[l_index].c].x,
			model->vertex[model->polygon[l_index].c].y,
			model->vertex[model->polygon[l_index].c].z);
	}
	glEnd();

	glPopMatrix();
}

void GameObject::SetPosition(const Vef3& pos)
{
	position = pos;
}
