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

void PerspectiveCamera::drawRay(){
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	Vector3f vec = GetCenter() - getCameraLocation();
	glVertex(getCameraLocation()+(vec/3.0f));
	glVertex(GetCenter()+Vector3f(1,0,0));
	glEnd();
}