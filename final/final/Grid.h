#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Vector3f.h"

using namespace std;

class Grid
{
public:
	Grid();
	Grid(float x, float y, float z);
	void assignNoise(float val);
	float getNoiseVal();
	Vector3f getXYZ();
private:
	Vector3f xyz;
	float noiseval;
};
#endif // !GRID_H