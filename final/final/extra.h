#ifndef EXTRA_H
#define EXTRA_H

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "vecmath.h"
#else
#include <GL/gl.h>
#include <vecmath.h>
#endif

#ifndef M_PI
#define M_PI  3.14159265358979
#endif

// Inline functions to help with drawing
inline void glVertex( const Vector3f& a )
{
    glVertex3fv(a);
}

inline void glNormal( const Vector3f& a ) 
{
    glNormal3fv(a);
}

inline void glLoadMatrix( const Matrix4f& m )
{
//    glLoadMatrixf( m );
}

inline void glMultMatrix( const Matrix4f& m )
{
//    glMultMatrixf( m );
}

#endif
