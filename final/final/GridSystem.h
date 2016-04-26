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
	void drawMesh(bool walkaround);
	void getLastClickedGrid(PerspectiveCamera pc, int &reti, int &retj); //returns 2 int values
	void setSelectedGrid(int i, int j);
	void showSelectedGrid();
	Grid* getSelectedGrid();
	void drawBoundingBox(int boundingBoxHeight);
	void drawMeshSkeleton(bool drawNormal);
	Matrix4f GridSystem::RotationMatrixOnAxis(float angle, float u, float v, float w);
	void forceGroundedView(PerspectiveCamera &pc);
	float getYLevel(float x, float y);
private:
	vector<vector<Grid*>> grids; //grids[x][y]
	PerlinNoise p;
	int w;
	int h;
	int selectedi;
	int selectedj;
	float offset;
};
#endif // !GRIDSYSTEM_H

