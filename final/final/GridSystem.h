#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H

#ifdef __APPLE__
    #include "vecmath.h"
#else
    #include <vecmath.h>
#endif
#include <vector>
#include "Grid.h"
#include "PerlinNoise.h"

using namespace std;

class GridSystem
{
public:
	GridSystem();
	GridSystem(int w, int h, PerlinNoise p);
	void drawMesh();
	vector<vector<Grid>> getGrids() { return grids; }
private:
	vector<vector<Grid>> grids; //grids[x][y]
	PerlinNoise p;
	int w;
	int h;
};
#endif // !GRIDSYSTEM_H

