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
#include "PerspectiveCamera.h"

using namespace std;

class GridSystem
{
public:
	GridSystem();
	GridSystem(int w, int h, PerlinNoise p);
	void drawMesh();
	Grid* getLastClickedGrid(PerspectiveCamera pc);
	void setSelectedGrid(Grid* g);
	void showSelectedGrid();
	void drawMeshSkeleton(bool drawNormal);
private:
	vector<vector<Grid>> grids; //grids[x][y]
	Perlin p;
	int w;
	int h;
	Grid* selectedGrid;
	int selectedi;
	int selectedj;
	float offset;
};
#endif // !GRIDSYSTEM_H

