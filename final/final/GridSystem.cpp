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
	GridSystem(10, 10, PerlinNoise());
}

GridSystem::GridSystem(int w, int h, PerlinNoise p)
{
	this->w = w;
	this->h = h;
	float offset = 0.2f;
	this->p = p;
	float octave = 1.0f;
	float size = 0.4f;
	//initialize grids
	for (float i = 0.0f; i <= w; i += offset)
	{
		vector<Grid> gridRow;
		for (float j = 0.0f; j <= h; j += offset)
		{
			Grid g = Grid(i, 0.0f, j, size);
			if (i == 0.0f || (i + (2 * offset)) > w || j == offset || (j + (2 * offset)) > h)
			{
				//g.assignNoise(p.octaveNoise(Vector3f(i, 0.0f, j), octave));
				g.assignNoise(p.octaveNoise(i, 0.0f, j, 1.0f, 2.0f, 3));
				g.assignNormal(Vector3f(0, 1, 0));
				//cout << " " << g.getNoiseVal() << " ";
			}
			else
			{
				g.assignNoise(p.octaveNoise(i, 0.0f, j, 1.0f, 3.0f, 3)*2.3);
				g.assignNormal(Vector3f(0, 1, 0));
				//g.assignNoise(p.octaveNoise(Vector3f(i, 0.0f, j), octave) * 2);
				//cout << " " << g.getNoiseVal() << " ";
			}
			gridRow.push_back(g);
		}
		grids.push_back(gridRow);
	}
}

void GridSystem::drawMesh()
{
	/*for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (i > 0 && j > 0)
			{
				grids[i - 1][j - 1].getTexture().chooseTexture(0.5f);

				glVertex(grids[i - 1][j - 1].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j - 1].getXYZ());
				grids[i][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j].getXYZ());

				grids[i][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j].getXYZ());
				grids[i - 1][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j - 1].getXYZ());

				grids[i - 1][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j - 1].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j - 1].getXYZ());
				grids[i][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j].getXYZ());
			}
		}
	}*/
	glBegin(GL_QUADS);
	const float boundingBoxHeight = 2.0f;
	const float waterLevel = 1.0f;
	//draw bounding box
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, 0, 0));

	glVertex(Vector3f(0, 0, h));
	glVertex(Vector3f(0, boundingBoxHeight, h));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glVertex(Vector3f(w, 0, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, boundingBoxHeight, 0));
	glVertex(Vector3f(0, boundingBoxHeight, h));
	glVertex(Vector3f(0, 0, h));

	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, 0, h));
	glVertex(Vector3f(w, 0, h));
	glVertex(Vector3f(w, 0, 0));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//draw water
	glColor4f(0.0f, 0.0f, 1.0f, 0.2f);
	glVertex(Vector3f(0, waterLevel, 0));
	glVertex(Vector3f(0, waterLevel, h));
	glVertex(Vector3f(w, waterLevel, h));
	glVertex(Vector3f(w, waterLevel, 0));

	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(1, .2, 0, 0.5f);
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (i > 0 && j > 0)
			{
				grids[i - 1][j - 1].getTexture().chooseTexture(1.0f);
				glVertex(grids[i - 1][j - 1].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j - 1].getXYZ());
				grids[i][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j].getXYZ());

				grids[i][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j].getXYZ());
				grids[i - 1][j - 1].getTexture().chooseTexture(0.5f);
				glVertex(grids[i - 1][j - 1].getXYZ());
				/*glVertex(grids[i - 1][j - 1].getXYZ());
				glVertex(grids[i][j - 1].getXYZ());
				glVertex(grids[i][j].getXYZ());

				glVertex(grids[i][j].getXYZ());
				glVertex(grids[i - 1][j].getXYZ());
				glVertex(grids[i - 1][j - 1].getXYZ());*/
			}
		}
	}
	glEnd();

}















