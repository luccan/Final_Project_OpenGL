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

void Grid::assignNoise(float val)
{
	this->noiseval = val;
	this->xyz.y() = val;
}
float Grid::getNoiseVal()
{
	return this->noiseval;
}
Vector3f Grid::getXYZ()
{
	return this->xyz;
}