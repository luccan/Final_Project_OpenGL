#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H

#ifdef __APPLE__
    #include "vecmath.h"
#else
    #include <vecmath.h>
#endif
#include <vector>
#include "Grid.h"
#include "Perlin.h"

using namespace std;

class GridSystem
{
public:
	GridSystem();
	GridSystem(int w, int h, Perlin p);
	void drawMesh();
private:
	vector<vector<Grid>> grids; //grids[x][y]
	Perlin p;
};
#endif // !GRIDSYSTEM_H

