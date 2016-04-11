#include "GridSystem.h"
#ifdef __APPLE__
#include "Vector3f.h"
#else
#include <Vector3f.h>
#endif
#include "extra.h"
#include <iostream>

GridSystem::GridSystem()
{
	GridSystem(10, 10, Perlin());
}

GridSystem::GridSystem(int w, int h, Perlin p)
{
	this->p = p;
	//initialize grids
	for (float i = 0.5f; i < w; i+=1.1f){
		vector<Grid> gridRow;
		for (float j = 0.5f; j < h; j+=1.1f){
			Grid g = Grid(i,0.0f, j);
			g.assignNoise(p.octave_noise(i, 0.0f, j, 1, 1, 3));
			gridRow.push_back(g);
		}
		grids.push_back(gridRow);
	}
}

void GridSystem::drawMesh()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < grids.size(); i++){
		for (int j = 0; j < grids[0].size(); j++){
			if (i>0 && j>0){
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				glColor3f(r, r2, r3);
				glVertex(grids[i-1][j-1].getXYZ());
				glVertex(grids[i][j-1].getXYZ());
				glVertex(grids[i][j].getXYZ());
				glVertex(grids[i-1][j].getXYZ());
			}
		}
	}
	glEnd();
}















