#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Vector3f.h"
#include "Texture.h"
#include "Object3D.h"

using namespace std;

class Grid : public Object3D
{
public:
	Grid();
	Grid(float x, float y, float z);
	Grid(float x, float y, float z, Texture t);
	void print();
	void assignNoise(float val);
	void assignNormal(Vector3f n) { this->normal = n; }
	float getNoiseVal();
	Vector3f getXYZ();
	Texture getTexture();
	vector<Vector3f> neighbours;

	virtual bool Grid::intersect(const Ray& r, Hit& h, float tmin)
	{
		Vector3f R_o = r.getOrigin();
		Vector3f R_d = r.getDirection().normalized();
		float nDotR_d = Vector3f::dot(this->normal, R_d);

		if (nDotR_d == 0)
		{
			return false;
		}

		float nDotR_o = Vector3f::dot(this->normal, R_o);
		float t = -1.0*(-1.0*this->d + nDotR_o) / (nDotR_d);

		if (t > tmin && t < h.getT())
		{
			h.set(t, this->material, this->normal);
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	Vector3f xyz;
	float noiseval;
	Texture texture;
	Vector3f normal;
	float d;
};
#endif // !GRID_H