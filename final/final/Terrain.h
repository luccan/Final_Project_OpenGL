#ifndef TERRAIN_H
#define TERRAIN_H

#include "Perlin.h"
#include "GridSystem.h"

class Terrain
{
public:
	Terrain();
	Terrain(Perlin &p, int w, int h);
	GridSystem getGridSystem();
	void SetGridSystem(GridSystem &gs);
private:
	int w, h;
	GridSystem gs;
};

#endif // !TERRAIN_H
