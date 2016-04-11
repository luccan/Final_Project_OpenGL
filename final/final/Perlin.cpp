#include "Perlin.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include "stdafx.h"

Perlin::Perlin()
{
}

float Perlin::octave_noise(float x, float y, float z, float persistence, float amplitude, float octave)
{
	float total = 0;
	float frequency = 1;
	float maxValue = 0;			// Used for normalizing result to 0.0 - 1.0
	for (int i = 0; i < octave; i++)
	{
		total += noise(x * frequency, y * frequency, z * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

float Perlin::noise(float x, float y, float z)
{
	int xi = (int)x & 255;
	int yi = (int)y & 255;
	int zi = (int)z & 255;

	float xf = x - (int)x;
	float yf = y - (int)y;
	float zf = z - (int)z;

	float u = fade(xf);
	float v = fade(yf);
	float w = fade(zf);


	int aaa, aba, aab, abb, baa, bba, bab, bbb;

	aaa = p[p[p[xi] + yi] + zi];
	aba = p[p[p[xi] + inc(yi)] + zi];
	aab = p[p[p[xi] + yi] + inc(zi)];
	abb = p[p[p[xi] + inc(yi)] + inc(zi)];
	baa = p[p[p[inc(xi)] + yi] + zi];
	bba = p[p[p[inc(xi)] + inc(yi)] + zi];
	bab = p[p[p[inc(xi)] + yi] + inc(zi)];
	bbb = p[p[p[inc(xi)] + inc(yi)] + inc(zi)];

	double x1, x2, y1, y2;

	x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);
	x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
	y1 = lerp(x1, x2, v);

	x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
	x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
	y2 = lerp(x1, x2, v);

	return (lerp(y1, y2, w) + 1) / 2.0f;
}

int Perlin::inc(int num)
{
	num++;
	return num;
}

float Perlin::grad(int hash, float x, float y, float z)
{
	int h = hash & 15;
	float u = h < 8 ? x : y;
	float v = 0;

	if (h < 4)
	{
		v = y;
	}
	else if (h == 12 || h == 14)
	{
		v = x;
	}
	else
	{
		v = z;
	}

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float Perlin::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}


float Perlin::lerp(float a, float b, float z)
{
	return a + z * (b - a);
}

