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
	GridSystem(int w, int h, PerlinNoise p, float gridsize);
	void drawMesh();
	void getLastClickedGrid(PerspectiveCamera pc, int &reti, int &retj); //returns 2 int values
	void setSelectedGrid(int i, int j);
	void showSelectedGrid();
	Grid* getSelectedGrid();
	void drawMeshSkeleton(bool drawNormal);
private:
	vector<vector<Grid*>> grids; //grids[x][y]
	Perlin p;
	int w;
	int h;
	int selectedi;
	int selectedj;
	float offset;
};
#endif // !GRIDSYSTEM_H

