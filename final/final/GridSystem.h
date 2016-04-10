#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H


#include <vecmath.h>
#include <vector>
#include "Grid.h"

using namespace std;

class GridSystem
{
public:
	GridSystem();
	void addGrid(Grid g);
private:
	vector<Grid> list_grid;
};
#endif // !GRIDSYSTEM_H

