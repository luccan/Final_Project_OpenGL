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
	float offset = 0.5f;
	this->p = p;
	float persistance = 0.2f;
	float amplitude = 1.0f;
	float octave = 7.0f;
	//initialize grids
	for (float i = offset; i < w; i += offset)
	{
		vector<Grid> gridRow;
		for (float j = offset; j < h; j += offset)
		{
			Grid g = Grid(i, 0.0f, j);
			if (i == offset || (i + (2 * offset))>w || j == offset || (j + (2 * offset))>h)
			{
				g.assignNoise(p.octave_noise(i, 0.0f, j, persistance, amplitude, octave));
			}
			else
			{
				g.assignNoise(p.octave_noise(i, 0.0f, j, persistance, amplitude, octave) * 3);
			}
			gridRow.push_back(g);
		}
		grids.push_back(gridRow);
	}
}

void GridSystem::drawMesh()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (i > 0 && j > 0)
			{
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				glColor3f(0.372549 + r, 0.619608 + r2, 0.627451 + r3);
				glVertex(grids[i - 1][j - 1].getXYZ());
				glVertex(grids[i][j - 1].getXYZ());
				glVertex(grids[i][j].getXYZ());
				glVertex(grids[i - 1][j].getXYZ());
			}
		}
	}
	glEnd();
}















