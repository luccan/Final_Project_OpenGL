// Arcball camera by Eugene Hsu
// Based on 6.839 sample code for rotation code.
// Extended to handle translation (MIDDLE) and scale (RIGHT)

// -*-c++-*-
#ifndef CAMERA_H
#define CAMERA_H
#ifdef __APPLE__
#include "vecmath.h"
#else
#include <vecmath.h>
#include "Ray.h"
#endif

class Camera
{
public:

    Camera();
    
    typedef enum { NONE, LEFT, MIDDLE, RIGHT } Button;

    // You must call all of the Set*() functions before you use this!
    // I didn't put it into the constructor because it's inconvenient
    // to initialize stuff in my opengl application.
    
    void SetDimensions(int w, int h);
    void SetViewport(int x, int y, int w, int h);
    void SetPerspective(float fovy);

    // Call from whatever UI toolkit
    void MouseClick(Button button, int x, int y);
    void MouseDrag(int x, int y);
    void MouseRelease(int x, int y);

    // Apply viewport, perspective, and modeling
    // use these instead of 
    void ApplyViewport() const;
    void ApplyPerspective() const;
    void ApplyModelview() const;

    // Set for relevant vars
    void SetCenter(const Vector3f& center);
    void SetRotation(const Matrix4f& rotation);
    void SetDistance(const float distance);

    // Get for relevant vars
    Vector3f GetCenter() const { return mCurrentCenter; }
    Matrix4f GetRotation() const { return mCurrentRot; }
    float GetDistance() const { return mCurrentDistance; }
	Ray generateRay(const Vector2f& p);
private:

    // States 
    int     mDimensions[2];
    int     mStartClick[2];
    Button  mButtonState;

    // For rotation
    Matrix4f mStartRot;
    Matrix4f mCurrentRot;

    // For translation
    float   mPerspective[2];
    int     mViewport[4];
    Vector3f mStartCenter;
    Vector3f mCurrentCenter;

    // For zoom
    float   mStartDistance;
    float   mCurrentDistance;

    void ArcBallRotation(int x, int y);
    void PlaneTranslation(int x, int y);
    void DistanceZoom(int x, int y);
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& up, float angle);
	Vector3f getCameraLocation();
	virtual Ray generateRay(const Vector2f& point);
	void setDirection(Vector3f dir);
	Vector3f getDirection() { return this->direction; }
	virtual float getTMin() const
	{
		return 0.0f;
	}

private:
	Vector3f center;
	Vector3f direction;
	Vector3f w;
	Vector3f u;
	Vector3f v;
	float angle;

};
#endif
