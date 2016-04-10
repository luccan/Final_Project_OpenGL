#ifndef GRID_H
#define GRID_H

#include <vector>

using namespace std;

class Grid
{
public:
	Grid();
	Grid(float x, float y, float z);
	void assignNoise(float val);
	float getNoiseVal();
private:
	float x;
	float y;
	float z;
	float noiseval;
};
#endif // !GRID_H