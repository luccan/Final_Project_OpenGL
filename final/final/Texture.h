#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include "Vector3f.h"

using namespace std;

class Texture
{
public:
	enum TYPE {GRASS, MUD, MOUNTAIN, BLACK};
	Texture();
	Texture(TYPE type);
	void chooseTexture();
	TYPE getTexture();
private:
	Vector3f rgb;
	TYPE type;
};
#endif // !GRID_H