#ifndef VERTEXCOLOR_H
#define VERTEXCOLOR_H

#include <vector>
#include "Vector3f.h"

using namespace std;

class VertexColor
{
public:
	enum TYPE {GRASS, MUD, MOUNTAIN, BLACK};
	VertexColor();
	VertexColor(TYPE type);
	void chooseTexture();
	TYPE getTexture();
private:
	Vector3f rgb;
	TYPE type;
};

#endif // !GRID_H