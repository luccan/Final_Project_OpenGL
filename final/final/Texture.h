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
	void chooseTexture(float alpha);
private:
	Vector3f rgb;
};
#endif // !GRID_H