#include "GridSystem.h"
#ifdef __APPLE__
#include "Vector3f.h"
#else
#include <Vector3f.h>
#endif
#include "extra.h"
#include <iostream>
#include "PerlinNoise.h"

GridSystem::GridSystem()
{
	GridSystem(10, 10, PerlinNoise(), 0.25f);
}

GridSystem::GridSystem(int w, int h, PerlinNoise p, float gridsize)
{
	this->selectedGrid = &Grid();
	this->selectedi = 0; this->selectedj = 0;
	this->w = w;
	this->h = h;
	this->offset = gridsize;
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
			float val = p.Noise(i, 0.0f, j, persistance, amplitude, octave) * 3;
			cout << val << endl;
			g.assignNoise(p.Noise(i, 0.0f, j, persistance, amplitude, octave) * 3);
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
	GLfloat Lt1diff[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Lt1pos[] = { 4.0, 4.0, 4.0, 1.0 };
	glLightfv(GL_LIGHT0 + 1, GL_DIFFUSE, Lt1diff);
	glLightfv(GL_LIGHT0 + 1, GL_POSITION, Lt1pos);
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (i > 0 && j > 0)
			{
				grids[i - 1][j - 1].getTexture().chooseTexture();
				//grids[i - 1][j - 1].getMaterial().bindMat();
				glVertex(grids[i - 1][j - 1].getXYZ());
				grids[i][j - 1].getTexture().chooseTexture();
				//grids[i][j - 1].getMaterial().bindMat();
				glVertex(grids[i][j - 1].getXYZ());
				grids[i][j].getTexture().chooseTexture();
				//grids[i][j].getMaterial().bindMat();
				glVertex(grids[i][j].getXYZ());
				grids[i - 1][j].getTexture().chooseTexture();
				//grids[i - 1][j].getMaterial().bindMat();
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

void GridSystem::drawMeshSkeleton(bool drawNormal = false){
	glBegin(GL_LINES);
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			//draw normal
			if (drawNormal){
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex(grids[i][j].getXYZ());
				glVertex(grids[i][j].getXYZ() + (0.2* grids[i][j].getNormal()));
			}
			//draw mesh lines
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

Grid* GridSystem::getLastClickedGrid(PerspectiveCamera pc){
	Grid* ret = new Grid();
	float min_dist = FLT_MAX;

	Vector3f ray = pc.getRay();
	float d = sqrt(pow(ray.x(), 2) + pow(ray.y(), 2) + pow(ray.z(), 2)); //dist from ray to projection pt
	Vector3f p = pc.getCameraLocation() + ray;
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			Grid* g = &grids[i][j];
			Vector3f pt = g->getXYZ();
			Vector3f newray = pt - pc.getCameraLocation(); //ray from camera to pt
			float dist = sqrt(pow(newray.x(), 2) + pow(newray.y(), 2) + pow(newray.z(), 2)); //dist from camera to pt
			Vector3f extNewray = newray.normalized() * d;
			Vector3f extPt = pc.getCameraLocation() + extNewray; //extended point in objective 3d space (0, 0, 592, 592)
			
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			float threshold = (d/180)*offset;
			if (abs(extPt.x() - p.x()) < threshold \
				&& abs(extPt.y() - p.y()) < threshold \
				&& abs(extPt.z() - p.z()) < threshold){ //DUMMY LOL
				if (min_dist > dist){
					min_dist = dist;
					ret = g;
					Vector3f point = pc.getCameraLocation() + newray / 3.0f;
					glVertex(point);
					glVertex(pt);
					cout << point.x() << " " << point.y() << " " << point.z() << " " << endl;
					cout << pt.x() << " " << pt.y() << " " << pt.z() << " " << endl;
				}
			}
			glVertex(Vector3f(0,0,0));
			glEnd();
		}
	}

	return ret;
}
void GridSystem::setSelectedGrid(Grid* g){
	selectedGrid = g;
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			if (grids[i][j].getXYZ().x() == selectedGrid->getXYZ().x() \
				&& grids[i][j].getXYZ().y() == selectedGrid->getXYZ().y() \
				&& grids[i][j].getXYZ().z() == selectedGrid->getXYZ().z()){
				this->selectedi = i;
				this->selectedj = j;
				glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				if (selectedi>0 && selectedj > 0){
					glVertex(grids[selectedi][selectedj].getXYZ());
					glVertex(grids[selectedi][selectedj - 1].getXYZ());
					glVertex(grids[selectedi - 1][selectedj - 1].getXYZ());
					glVertex(grids[selectedi - 1][selectedj].getXYZ());
				}
				glEnd();
			}
		}
	}
}
void GridSystem::showSelectedGrid(){
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	if (selectedi>0 && selectedj > 0){
		glVertex(grids[selectedi][selectedj].getXYZ());
		glVertex(grids[selectedi][selectedj-1].getXYZ());
		glVertex(grids[selectedi-1][selectedj-1].getXYZ());
		glVertex(grids[selectedi-1][selectedj].getXYZ());
	}
	glEnd();
	/*if (this->selectedGrid->getNoiseVal() > 0){
		this->selectedGrid->show();
	}*/
}













