#include "Texture.h"
#include "extra.h"
#include <iostream>

Texture::Texture()
{
	
}

Texture::Texture(TYPE type)
{
	switch (type){
	case GRASS:
		this->rgb = Vector3f(0.1f, 0.2f, 0.1f); //green
		break;
	case MUD:
		this->rgb = Vector3f(0.4f, 0.2f, 0.1f); //brown
		break;
	case MOUNTAIN:
		this->rgb = Vector3f(0.5f, 0.5f, 0.5f); //gray
		break;
	case BLACK:
	default:
		this->rgb = Vector3f(0.0f, 0.0f, 0.0f);
		break;
	}
}

void Texture::chooseTexture()
{
	glColor3f(rgb.x(), rgb.y(), rgb.z());
}