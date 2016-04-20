#include "Terrain.h"
#include "GridSystem.h"

Terrain::Terrain()
{
}

Terrain::Terrain(PerlinNoise& p, int w, int h, float gridsize)
{
	this->w = w;
	this->h = h;
	this->gs = GridSystem(w,h,p, gridsize);
}

GridSystem* Terrain::getGridSystem()
{
	return &gs;
}
void Terrain::SetGridSystem(GridSystem &gs)
{
	this->gs = gs;
}
