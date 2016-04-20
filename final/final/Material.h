#ifndef MATERIAL_H
#define MATERIAL_H

#include <extra.h>
#include <GL\GL.h>

class Material
{
public:
	enum TYPE { WATER, GRASS, MUD, MOUNTAIN, BLACK };
	Material(){

	}

	Material(TYPE type_m)
	{
		GLfloat water[4] = { 0.0f, 0.8f, 0.2f, 0.6f };
		GLfloat grass[4] = { 0.3f, 0.4f, 0.4f, 1.0f };
		GLfloat mud[4] = { 0.4f, 0.2f, 0.1f, 1.0f };
		GLfloat mountain[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat black[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		this->type = type_m;
		switch (this->type)
		{
		case GRASS:
			this->rgba_v = grass;
			this->rgba = Vector4f(grass[0], grass[1], grass[2], grass[3]);
			break;

		case MOUNTAIN:
			this->rgba_v = mountain;
			this->rgba = Vector4f(mountain[0], mountain[1], mountain[2], mountain[3]);
			break;

		case MUD:
			this->rgba_v = mud;
			this->rgba = Vector4f(mud[0], mud[1], mud[2], mud[3]);
			break;

		case BLACK:
			this->rgba_v = black;
			this->rgba = Vector4f(black[0], black[1], black[2], black[3]);
			break;
		case WATER:
			this->rgba_v = water;
			this->rgba = Vector4f(water[0], water[1], water[2], water[3]);
			break;
		default:
			break;
		}
	}

	void bindMat()
	{
		glEnable(GL_BLEND);
		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		//glColor3fv(rgba_v);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->rgba_v);
	}


	virtual ~Material()
	{
	}

	Material getMaterial()
	{
		//if (this->type == GRASS);
		return Material();
	}
private:
	TYPE type;
	Vector4f rgba;
	GLfloat* rgba_v;
};



#endif // MATERIAL_H
