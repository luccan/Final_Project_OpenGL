#ifndef _PERLIN_H_
#define _PERLIN_H_

#include <vector>
using namespace std;


class Perlin
{
public:
	Perlin();
	float Noise(float x, float y, float z, float persistence, float amplitude, float octave);
	float Noise(float x, float y, float z);
private:
	int inc(int num);
	float grad(int hash, float x, float y, float z);
	float fade(float t);
	float lerp(float a, float b, float z);
	vector<int> p;
};

#endif
