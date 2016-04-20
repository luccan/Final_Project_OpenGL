#include "Terrain.h"
#include "GridSystem.h"

Terrain::Terrain()
{
}

Terrain::Terrain(PerlinNoise& p, int w, int h)
{
	this->w = w;
	this->h = h;
	this->gs = GridSystem(w,h,p);
}

GridSystem Terrain::getGridSystem()
{
	return gs;
}
void Terrain::SetGridSystem(GridSystem &gs)
{
	this->gs = gs;
}
