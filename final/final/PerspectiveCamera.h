#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H
#ifdef __APPLE__
#include "vecmath.h"
#else
#include <vecmath.h>
#endif

#include "camera.h"

class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera();
	Vector3f getCameraLocation();
	void drawRay();

};

#endif
