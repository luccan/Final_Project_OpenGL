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
	this->w = w;
	this->h = h;
	float offset = 0.1f;
	this->p = p;
	float persistance = 0.2f;
	float amplitude = 1.0f;
	float octave = 7.0f;

	//initialize grids
	for (float i = 0.0f; i < w + (offset/2); i += offset) //float correction that's why we add (offset/2)
	{
		vector<Grid> gridRow;
		for (float j = 0.0; j < h + (offset/2); j += offset)
		{
			Grid g = Grid(i, 0.0f, j);
			g.assignNoise(p.octave_noise(i, 0.0f, j, persistance, amplitude, octave) * 3);
			/*if (i == 0.0f || (i + (2 * offset))>w || j == offset || (j + (2 * offset))>h)
			{
				g.assignNoise(p.octave_noise(i, 0.0f, j, persistance, amplitude, octave));
			}
			else
			{
				g.assignNoise(p.octave_noise(i, 0.0f, j, persistance, amplitude, octave) * 3);
			}*/
			gridRow.push_back(g);
		}
		grids.push_back(gridRow);
	}

	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			Grid n_up = (i > 0) ? grids[i - 1][j] : grids[i][j];
			Grid n_down = (i < grids.size()-1) ? grids[i + 1][j] : grids[i][j];
			Grid n_right = (j < grids[0].size() - 1) ? grids[i][j + 1] : grids[i][j];
			Grid n_left = (j > 0) ? grids[i][j - 1] : grids[i][j];
			grids[i][j].setNeighboringGrid(n_up, n_right, n_down, n_left);
		}
	}

	/*for (int a = 0; a < grids.size()*grids[0].size()*5; a++){
		int i = rand() % grids.size();
		int j = rand() % grids[0].size();
		grids[i][j].naturalizeGrid();
	}*/
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
				grids[i - 1][j - 1].getTexture().chooseTexture();
				glVertex(grids[i - 1][j - 1].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture();
				glVertex(grids[i][j - 1].getXYZ());
				grids[i][j].getTexture().chooseTexture();
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture();
				glVertex(grids[i - 1][j].getXYZ());
			}
		}
	}

	const float boundingBoxHeight = 2.0f;
	const float waterLevel = 1.0f;
	//draw bounding box
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex(Vector3f(0,0,0));
	glVertex(Vector3f(0, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, 0, 0));

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex(Vector3f(0, 0, h));
	glVertex(Vector3f(0, boundingBoxHeight, h));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex(Vector3f(w, 0, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, boundingBoxHeight, 0));
	glVertex(Vector3f(0, boundingBoxHeight, h));
	glVertex(Vector3f(0, 0, h));

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, 0, h));
	glVertex(Vector3f(w, 0, h));
	glVertex(Vector3f(w, 0, 0));

	//draw water
	glColor3f(0.0f, 0.0f, 0.7f);
	glVertex(Vector3f(0, waterLevel, 0));
	glVertex(Vector3f(0, waterLevel, h));
	glVertex(Vector3f(w, waterLevel, h));
	glVertex(Vector3f(w, waterLevel, 0));

	glEnd();
}

void GridSystem::drawMeshSkeleton(){
	glBegin(GL_LINES);
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (i > 0){
				grids[i][j].getTexture().chooseTexture();
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture();
				glVertex(grids[i - 1][j].getXYZ());
			}
			if (j > 0){
				grids[i][j].getTexture().chooseTexture();
				glVertex(grids[i][j].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture();
				glVertex(grids[i][j - 1].getXYZ());
			}
		}
	}
	glEnd();
}















