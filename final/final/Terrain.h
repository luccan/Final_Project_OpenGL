#ifndef TERRAIN_H
#define TERRAIN_H

#include "Perlin.h"
#include "GridSystem.h"

class Terrain
{
public:
	Terrain();
	Terrain(Perlin &p, int w, int h);
	Perlin getPerlin();
private:
	Perlin p;
	int w, h;
	GridSystem gs;
};

#endif // !TERRAIN_H
