#include "Terrain.h"
#include "Perlin.h"

Terrain::Terrain(Perlin& p, int w, int h)
{
	this->p = p;
	this->w = w;
	this->h = h;
	this->gs = GridSystem();
}

Perlin Terrain::getPerlin()
{
	return this->p;
}

Terrain::Terrain()
{
}

//GridSystem Terrain::getGridSystem()
//{
//	return this->gs;
//}
//void Terrain::setGridSystem(GridSystem &gs)
//{
//	this->gs = gs;
//}
