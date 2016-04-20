#include "Grid.h"
#include "Terrain.h"
#include <iostream>
#include "extra.h"

Grid::Grid() //dummy initialization
{
	this->valid = false;
}

Grid::Grid(float x, float y, float z)
{
	this->xyz = Vector3f(x, 0.0f, z);
	this->valid = true;
}

Grid::Grid(float x, float y, float z, Texture t)
{
	this->xyz = Vector3f(x, 0.0f, z);
	this->texture = t;
	this->valid = true;
}

void Grid::assignNoise(float val)
{
	this->noiseval = val;
	this->xyz.y() = val;
	if (val > 1.5f)
	{
		this->texture = Texture(Texture::MOUNTAIN);
		this->mat = Material(Material::MOUNTAIN);
	}
	else if (val >= 1.5f && val <= 2.0f)
	{
		this->texture = Texture(Texture::MUD);
		this->mat = Material(Material::MUD);
	}
	else if (val >= 0.5f && val <= 1.5f)
	{
		//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			/*this->texture = Texture(Texture::MUD);
			this->mat = Material(Material::MUD);*/


		this->texture = Texture(Texture::GRASS);
		this->mat = Material(Material::GRASS);
		float h = 10.0f;
	}

}


void Grid::setNeighboringGrid(Grid* n_up, Grid* n_right, Grid* n_down, Grid* n_left){
	this->neighbors[0] = n_up;
	this->neighbors[1] = n_right;
	this->neighbors[2] = n_down;
	this->neighbors[3] = n_left;
	this->normal = Vector3f::cross(this->neighbors[0]->getXYZ(), this->neighbors[1]->getXYZ()) \
		+ Vector3f::cross(this->neighbors[1]->getXYZ(), this->neighbors[2]->getXYZ()) \
		+ Vector3f::cross(this->neighbors[2]->getXYZ(), this->neighbors[3]->getXYZ()) \
		+ Vector3f::cross(this->neighbors[3]->getXYZ(), this->neighbors[0]->getXYZ());
	this->normal.normalize();
}

void Grid::naturalizeGrid(){ // USE POINTER!
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < 0.2)
	{
		this->texture = Texture(this->neighbors[0]->getTexture().getTexture());
	}
	else if (r < 0.4)
	{
		this->texture = Texture(this->neighbors[1]->getTexture().getTexture());
	}
	else if (r < 0.6)
	{
		this->texture = Texture(this->neighbors[2]->getTexture().getTexture());
	}
	else if (r < 0.8)
	{
		this->texture = Texture(this->neighbors[3]->getTexture().getTexture());
	}
}

float Grid::getNoiseVal()
{
	return this->noiseval;
}
Vector3f Grid::getXYZ()
{
	return this->xyz;
}
Vector3f Grid::getNormal()
{
	return this->normal;
}
Texture Grid::getTexture()
{
	return texture;
}
void Grid::setTexture(Texture t)
{
	if (this->valid){
		this->texture = t;
	}
}
Material Grid::getMaterial()
{
	return this->mat;
}
void Grid::setMaterial(Material m)
{
	this->mat = m;
	m.bindMat();
}
void Grid::show(){
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	//elevate z just a bit to ensure red is visible
	glVertex(this->getXYZ()+Vector3f(0,0,0.001)); glVertex(this->neighbors[0]->getXYZ()); glVertex(this->neighbors[1]->getXYZ());
	glVertex(this->getXYZ()+Vector3f(0,0,0.001)); glVertex(this->neighbors[1]->getXYZ()); glVertex(this->neighbors[2]->getXYZ());
	glVertex(this->getXYZ()+Vector3f(0,0,0.001)); glVertex(this->neighbors[2]->getXYZ()); glVertex(this->neighbors[3]->getXYZ());
	glVertex(this->getXYZ()+Vector3f(0,0,0.001)); glVertex(this->neighbors[3]->getXYZ()); glVertex(this->neighbors[0]->getXYZ());
	//cout << this->neighbors[0]->getXYZ().x() << " " << this->neighbors[0]->getXYZ().y() << " " << this->neighbors[0]->getXYZ().z() << " " << endl;
	glEnd();
}