#include "PerspectiveCamera.h"
#ifdef __APPLE__
#include "vecmath.h"
#else
#include <vecmath.h>
#endif
#include "extra.h"

PerspectiveCamera::PerspectiveCamera(){
	Camera();
}

Vector3f PerspectiveCamera::getCameraLocation(){
	Vector4f relative_position = GetRotation().inverse() * Vector4f(0, 0, GetDistance(), 0);
	return relative_position.xyz() + GetCenter();
}

void PerspectiveCamera::drawRay(){ //only for debugging
	glBegin(GL_LINES);

	Vector3f vec = GetCenter() - getCameraLocation(); //vector from camera location to center

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex(getCameraLocation()+(vec/3.0f)); //shorten vector to make ray visible
	
	Vector3f random3dPoint = getRay();

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex(GetCenter()+random3dPoint);

	glEnd();
}

Vector3f PerspectiveCamera::getRay(){
	//random point in 3d space based on mouse click
	// start
	int sx = mStartClick[0] - mViewport[0];
	int sy = mStartClick[1] - mViewport[1];

	// compute "distance" of image plane (wrt projection matrix)
	float d = float(mViewport[3]) / 2.0f / tan(mPerspective[0] * M_PI / 180.0f / 2.0f);

	// compute up and right plane intersect of clickpoint (wrt fovy)
	float su = -sy + mViewport[3] / 2.0f;
	float sr = (sx - mViewport[2] / 2.0f);

	//compute vector from camera to (sr, su)
	Vector4f sClickPt = Vector4f(sr, su, -d, 1.0f);

	return (GetRotation().inverse() * sClickPt).xyz();
}