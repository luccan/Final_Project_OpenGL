#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Vector3f.h"
#include "Texture.h"
#include "Material.h"

using namespace std;

class Grid
{
public:
	Grid();
	Grid(float x, float y, float z);
	Grid(float x, float y, float z, Texture t);
	void assignNoise(float val);
	void setNeighboringGrid(Grid* n_up, Grid* n_right, Grid* n_down, Grid* n_left);
	void naturalizeGrid(); //influences the texture of a grid based on its surrounding grids
	float getNoiseVal();
	Vector3f getXYZ();
	Vector3f getNormal();
	Texture getTexture();
	void setTexture(Texture t);

	Material getMaterial();
	void setMaterial(Material m);
	void show();
private:
	Vector3f xyz;
	float noiseval;
	Texture texture;
	Grid* neighbors[4]; //0 is up, 1 right, 2 btm, 3 left : if no neighbor, this will contain itself.
	Vector3f normal;
	Material mat;
	bool valid;
};
#endif // !GRID_H