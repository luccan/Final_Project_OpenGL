#include "GridSystem.h"
#ifdef __APPLE__
#include "Vector3f.h"
#include <float.h>
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
	this->selectedi = -1; this->selectedj = -1;
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
		vector<Grid*> gridRow;
		for (float j = 0.0; j < h + (offset/2); j += offset)
		{
			Grid* g = new Grid(i, 0.0f, j);
			float val = p.Noise(i, 0.0f, j, persistance, amplitude, octave) * 3;
			g->assignNoise(val);
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
			Grid* n_up = (i > 0) ? grids[i - 1][j] : grids[i][j];
			Grid* n_down = (i < grids.size()-1) ? grids[i + 1][j] : grids[i][j];
			Grid* n_right = (j < grids[0].size() - 1) ? grids[i][j + 1] : grids[i][j];
			Grid* n_left = (j > 0) ? grids[i][j - 1] : grids[i][j];
			grids[i][j]->setNeighboringGrid(n_up, n_right, n_down, n_left);
		}
	}

	/*for (int a = 0; a < grids.size()*grids[0].size()*5; a++){
		int i = rand() % grids.size();
		int j = rand() % grids[0].size();
		grids[i][j].naturalizeGrid();
	}*/
}

void GridSystem::drawMesh(bool walkaround)
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
				grids[i - 1][j - 1]->getTexture().chooseTexture();
				//grids[i - 1][j - 1].getMaterial().bindMat();
				glVertex(grids[i - 1][j - 1]->getXYZ());
				grids[i][j - 1]->getTexture().chooseTexture();
				//grids[i][j - 1].getMaterial().bindMat();
				glVertex(grids[i][j - 1]->getXYZ());
				grids[i][j]->getTexture().chooseTexture();
				//grids[i][j]->getMaterial()->bindMat();
				glVertex(grids[i][j]->getXYZ());
				grids[i - 1][j]->getTexture().chooseTexture();
				//grids[i - 1][j]->getMaterial()->bindMat();
				glVertex(grids[i - 1][j]->getXYZ());

			}
		}
	}

	glEnd();

	if (walkaround){
		drawBoundingBox(8.0);
	}
	else {
		drawBoundingBox(2.0);
	}
}

void GridSystem::drawBoundingBox(int boundingBoxHeight){
	glBegin(GL_QUADS);
	//const float boundingBoxHeight = 2.0f;
	const float waterLevel = 1.0f;
	//draw bounding box (sky)
	glColor3f(0.8f, 0.8f, 1.0f);
	glVertex(Vector3f(0, 0, 0));
	glVertex(Vector3f(0, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, 0, 0));

	glColor3f(0.8f, 0.8f, 1.0f);
	glVertex(Vector3f(0, 0, h));
	glVertex(Vector3f(0, boundingBoxHeight, h));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glColor3f(0.8f, 0.8f, 1.0f);
	glVertex(Vector3f(w, 0, 0));
	glVertex(Vector3f(w, boundingBoxHeight, 0));
	glVertex(Vector3f(w, boundingBoxHeight, h));
	glVertex(Vector3f(w, 0, h));

	glColor3f(0.8f, 0.8f, 1.0f);
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
				glVertex(grids[i][j]->getXYZ());
				glVertex(grids[i][j]->getXYZ() + (0.2* grids[i][j]->getNormal()));
			}
			//draw mesh lines
			if (i > 0){
				grids[i][j]->getTexture().chooseTexture();
				glVertex(grids[i][j]->getXYZ());
				grids[i - 1][j]->getTexture().chooseTexture();
				glVertex(grids[i - 1][j]->getXYZ());
			}
			if (j > 0){
				grids[i][j]->getTexture().chooseTexture();
				glVertex(grids[i][j]->getXYZ());
				grids[i][j - 1]->getTexture().chooseTexture();
				glVertex(grids[i][j - 1]->getXYZ());
			}
		}
	}
	glEnd();
}

void GridSystem::getLastClickedGrid(PerspectiveCamera pc, int &reti, int &retj){
	int retij[2] = { -1, -1 };
	float min_dist = FLT_MAX;

	Vector3f ray = pc.getRay();
	float d = sqrt(pow(ray.x(), 2) + pow(ray.y(), 2) + pow(ray.z(), 2)); //dist from ray to projection pt
	Vector3f p = pc.getCameraLocation() + ray;
	for (int i = 0; i < grids.size(); i++)
	{
		for (int j = 0; j < grids[0].size(); j++)
		{
			Grid* g = grids[i][j];
			Vector3f pt = g->getXYZ();
			Vector3f newray = pt - pc.getCameraLocation(); //ray from camera to pt
			float dist = sqrt(pow(newray.x(), 2) + pow(newray.y(), 2) + pow(newray.z(), 2)); //dist from camera to pt
			Vector3f extNewray = newray.normalized() * d;
			Vector3f extPt = pc.getCameraLocation() + extNewray; //extended point in objective 3d space (0, 0, 592, 592)
			
			float threshold = (exp(4-(dist/15.0f))/d)*1500.0f*offset; //exp(3) = 20. (quite efficient for dist 4-30)
			if (abs(extPt.x() - p.x()) < threshold \
				&& abs(extPt.y() - p.y()) < threshold \
				&& abs(extPt.z() - p.z()) < threshold){ //NO LONGER DUMMY LOL //IT WORKS
				if (min_dist > dist){
					min_dist = dist;
					retij[0] = i; retij[1] = j;
					//g->show();
					//cout << "min_dist: " << min_dist << endl;
				}
			}

		}
	}
	//cout << "-------------" << endl;

	reti = retij[0];
	retj = retij[1];
}
void GridSystem::setSelectedGrid(int i, int j){
	selectedi = i;
	selectedj = j;
}
void GridSystem::showSelectedGrid(){
	if (selectedi >= 0 && selectedj >= 0){
		grids[selectedi][selectedj]->show();
	}
}
Grid* GridSystem::getSelectedGrid(){
	if (selectedi < 0 && selectedj < 0){
		Grid* dummy = new Grid();
		return dummy;
	}
	return grids[selectedi][selectedj];
}

Matrix4f GridSystem::RotationMatrixOnAxis(float angle, float u, float v, float w)
{
	float rotationMatrix[4][4];
	float L = (u*u + v * v + w * w);
	angle = angle * M_PI / 180.0; //converting to radian value
	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w;

	rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
	rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
	rotationMatrix[0][3] = 0.0;

	rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
	rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
	rotationMatrix[1][3] = 0.0;

	rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
	rotationMatrix[2][3] = 0.0;

	rotationMatrix[3][0] = 0.0;
	rotationMatrix[3][1] = 0.0;
	rotationMatrix[3][2] = 0.0;
	rotationMatrix[3][3] = 1.0;

	return Matrix4f(rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2], rotationMatrix[0][3], 
		rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2], rotationMatrix[1][3], 
		rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2], rotationMatrix[2][3], 
		rotationMatrix[3][0], rotationMatrix[3][1], rotationMatrix[3][2], rotationMatrix[3][3]);
}

void GridSystem::forceGroundedView(PerspectiveCamera &pc) {
	float lookAt_distance = offset/2;
	float old_distance = pc.GetDistance(); //need?

	Vector3f _p = pc.getCameraLocation(); Vector3f p = _p - Vector3f(0, _p.y(), 0); //xz only
	Vector3f _vec = pc.GetCenter() - p; Vector3f vec = _vec - Vector3f(0, _vec.y(), 0);
	Vector3f lookAt = p + ((offset*2) * vec.normalized()); //from camera to lookAt direction (xz only)

	Vector3f p_ground = Vector3f(p.x(), getYLevel(p.x(), p.z()) + 0.5f, p.z());
	Vector3f lookAt_ground = Vector3f(lookAt.x(), getYLevel(lookAt.x(), lookAt.z()) + 0.5f, lookAt.z());
	Vector3f nvec = (lookAt_ground - p_ground); //new camera location to new camera center
	Vector3f lookAt_final = p_ground + (lookAt_distance * nvec.normalized());

	//force distance to be at ground
	pc.SetCenter(lookAt_final); //apply new camera center
	//pc.SetCenter(lookAt_ground); //apply new camera center
	/*if (pc.GetCenter().y() < lookAt_ground.y() - 0.2){
		pc.SetCenter(lookAt_ground - Vector3f(0, 0.2, 0)); //apply new camera center
	}
	else if (pc.GetCenter().y() > lookAt_ground.y() + 0.2) {
		pc.SetCenter(lookAt_ground + Vector3f(0, 0.2, 0));
	}*/

	//float lookAt_distance = sqrt(pow(nvec.x(), 2) + pow(nvec.y(), 2) + pow(nvec.z(), 2));
	pc.SetDistance(lookAt_distance);

	Vector3f rotaxis = Vector3f::cross(nvec, Vector3f::UP);
	float angle_cur = atan((lookAt.y() - p_ground.y())/old_distance);
	float angle_new = atan((lookAt_ground.y() - p_ground.y())/lookAt_distance);
	float angle = angle_new - angle_cur;

	pc.SetViewRotation(RotationMatrixOnAxis(angle, rotaxis.x(), rotaxis.y(), rotaxis.z()));

	////set view to correct Z axis
	//pc.SetCenter(lookAt_ground); //apply new camera center
	//Vector3f nvec = (lookAt_ground - p_ground); //new camera location to new camera center (alrd applied)
	////float lookAt_distance = sqrt(pow(nvec.x(), 2) + pow(nvec.y(), 2) + pow(nvec.z(), 2));
	//float lookAt_distance = lookAtDistance;
	//pc.SetDistance(lookAt_distance);

	cout << "p:" << p_ground.x() << " " << p_ground.y() << " " << p_ground.z() << endl;
	cout << "lookAt:" << lookAt_ground.x() << " " << lookAt_ground.y() << " " << lookAt_ground.z() << endl;
	//cout << "test:" << test.x() << " " << test.y() << " " << test.z() << endl;
	//cout << p.x() << " " << p.z() << " " << getYLevel(0.758, 0.875) << endl;
}

float GridSystem::getYLevel(float x, float z){
	if (x < 0+2*offset || x > w-offset || z < 0+2*offset || z > h-offset){
		return -1;
	}
	float up = grids[(int)floor(x / offset)][(int)floor(z / offset)]->getXYZ().y();
	float right = grids[(int)ceil(x / offset)][(int)floor(z / offset)]->getXYZ().y();
	float down = grids[(int)ceil(x / offset)][(int)ceil(z / offset)]->getXYZ().y();
	float left = grids[(int)floor(x / offset)][(int)ceil(z / offset)]->getXYZ().y();
	//localPt([0-1],[0-1])
	Vector2f localPt = Vector2f(fmod(x, offset)/offset, fmod(z, offset)/offset);
	float uprighty = up + (0.5* (right-up) * localPt[0]); //y at (localPt[0],0)
	float leftdowny = left + (0.5 * (down-left) * localPt[0]); //y at (localPt[0],1)
	float y = uprighty + (0.5 * (leftdowny - uprighty) * localPt[1]);
	return y;
}








