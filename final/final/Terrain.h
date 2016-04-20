#ifndef TERRAIN_H
#define TERRAIN_H

#include "PerlinNoise.h"
#include "GridSystem.h"

class Terrain
{
public:
	Terrain();
	Terrain(PerlinNoise &p, int w, int h);
	GridSystem* getGridSystem();
	void SetGridSystem(GridSystem &gs);
private:
	int w, h;
	GridSystem gs;
};

#endif // !TERRAIN_H
