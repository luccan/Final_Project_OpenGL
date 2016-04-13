#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Vector3f.h"
#include "Texture.h"

using namespace std;

class Grid
{
public:
	Grid();
	Grid(float x, float y, float z);
	Grid(float x, float y, float z, Texture t);
	void assignNoise(float val);
	float getNoiseVal();
	Vector3f getXYZ();
	Texture getTexture();
private:
	Vector3f xyz;
	float noiseval;
	Texture texture;
};
#endif // !GRID_H