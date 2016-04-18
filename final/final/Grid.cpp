#include "Grid.h"
#include "Terrain.h"
#include <iostream>

Grid::Grid()
{
}

Grid::Grid(float x, float y, float z, float size)
{
	this->xyz = Vector3f(x, 0.0f, z);
	this->corners.push_back(Vector3f(x, 0.0f, z));
	this->corners.push_back(Vector3f(x + size, 0.0f, z));
	this->corners.push_back(Vector3f(x, 0.0f, z + size));
	this->corners.push_back(Vector3f(x + size, 0.0f, z + size));
}

Grid::Grid(float x, float y, float z, float size, Texture t)
{

	this->xyz = Vector3f(x, 0.0f, z);
	this->corners.push_back(Vector3f(x, 0.0f, z));
	this->corners.push_back(Vector3f(x + size, 0.0f, z));
	this->corners.push_back(Vector3f(x, 0.0f, z + size));
	this->corners.push_back(Vector3f(x + size, 0.0f, z + size));
	this->texture = t;
}

void Grid::assignNoise(float val)
{
	this->noiseval = val;
	this->xyz.y() = val;
	if (val > 2.0f){
		this->texture = Texture(Texture::MOUNTAIN);
	}
	else {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (r > 0.5){
			this->texture = Texture(Texture::MUD);
		}
		else {
			this->texture = Texture(Texture::GRASS);
		}
	}
	this->normal = Vector3f::dot(this->corners[0], this->corners[1]);
}
float Grid::getNoiseVal()
{
	return this->noiseval;
}
Vector3f Grid::getXYZ()
{
	return this->xyz;
}
Texture Grid::getTexture()
{
	return this->texture;
}	

void Grid::print()
{
	this->xyz.print();
}