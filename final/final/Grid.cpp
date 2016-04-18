#include "Grid.h"
#include "Terrain.h"
#include <iostream>

Grid::Grid()
{
}

Grid::Grid(float x, float y, float z)
{
	this->xyz = Vector3f(x, 0.0f, z);
}

Grid::Grid(float x, float y, float z, Texture t)
{
	this->xyz = Vector3f(x, 0.0f, z);
	this->texture = t;
}

void Grid::assignNoise(float val)
{
	this->noiseval = val;
	this->xyz.y() = val;
	if (val > 1.9f){
		this->texture = Texture(Texture::MOUNTAIN);
	}
	else if (val < 1.0f){
		this->texture = Texture(Texture::MUD);
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
}

void Grid::setNeighboringGrid(Grid &n_up, Grid &n_right, Grid &n_down, Grid &n_left){
	this->neighbors[0] = &n_up;
	this->neighbors[1] = &n_right;
	this->neighbors[2] = &n_down;
	this->neighbors[3] = &n_left;
}

void Grid::naturalizeGrid(){
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < 0.2){
		this->texture = Texture(this->neighbors[0]->getTexture().getTexture());
	} else if (r < 0.4){
		this->texture = Texture(this->neighbors[1]->getTexture().getTexture());
	} else if (r < 0.6){
		this->texture = Texture(this->neighbors[2]->getTexture().getTexture());
	} else if (r < 0.8){
		this->texture = Texture(this->neighbors[3]->getTexture().getTexture());
	}
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