#include "Grid.h"
#include "Terrain.h"
#include <iostream>

Grid::Grid()
{
}

Grid::Grid(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	cout << this->x << " " << this->y << " " << this->z << " ";
}

void Grid::assignNoise(float val)
{
	this->noiseval = val;
}
float Grid::getNoiseVal()
{
	return this->noiseval;
}