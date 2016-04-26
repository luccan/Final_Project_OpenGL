#ifdef WIN32
#include <windows.h>
#endif

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>


#ifdef __APPLE__
#include "vecmath.h"
#include <GLUT/glut.h>
#else
#include <vecmath.h>
#include <GL/freeglut.h>
#endif

#include "extra.h"
#include "PerspectiveCamera.h"
#include "Terrain.h"
#include "PerlinNoise.h"

using namespace std;

// If you're really interested in what "namespace" means, see
// Stroustup.  But basically, the functionality of putting all the
// globals in an "unnamed namespace" is to ensure that everything in
// here is only accessible to code in this file.
namespace
{
	// Global variables here.

	// This is the camera

	PerspectiveCamera camera;

    //camera variables

    Vector3f pos;
    
    Vector3f cameraDir;
    Vector3f up = Vector3f::Vector3f (0.0f, -1.0f, 0.0f);
    Vector3f cameraRight;
    Vector3f cameraUp;
    Vector3f cameraFront;
    GLfloat cameraSpeed;
	// These are state variables for the UI
	bool gMousePressed = false;
	int  gPointMode = 1;


	// These are arrays for display lists for each drawing mode.  The
	// convention is that drawmode 0 is "blank", and other drawmodes
	// just call the appropriate display lists.
	GLuint gAxisList;
	//GLuint gPointList;

	Terrain terrain;
	char terrainMode = 0; //0 for mesh, 1 for wireframe
	char textureMode = 0; //0 for mesh, 1 for wireframe
	char viewMode = 0; //0 for edit, 1 for walkaround

	// Declarations of functions whose implementations occur later.
	void arcballRotation(int endX, int endY);
	void keyboardFunc(unsigned char key, int x, int y);
	void specialFunc(int key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	void motionFunc(int x, int y);
	void reshapeFunc(int w, int h);
	void initRendering();
	void makeDisplayLists();

	// This function is called whenever a "Normal" key press is
	// received.
	void keyboardFunc(unsigned char key, int x, int y)
	{
        cameraDir = (camera.GetCenter()-camera.getCameraLocation()).normalized();
        
        cameraRight = Vector3f::cross(up, cameraDir).normalized();
        cameraUp = Vector3f::cross(cameraDir, cameraRight).normalized();
        cameraSpeed = 0.05f;
        cameraFront = (camera.GetCenter()-camera.getCameraLocation()).normalized();
		switch (key)
		{
		case 27: // Escape key
			exit(0);
			break;
		case ' ':
		{
			viewMode = 0;
			Matrix4f eye = Matrix4f::identity().rotateX((M_PI / 4.0));
			camera.SetRotation(eye);
			camera.SetDistance(10);
			camera.SetCenter(Vector3f(5, 0, 5));
			break;
		}

		case 't':
		case 'T':
			terrainMode = (terrainMode + 1) % 3;
			break;
		case 'v':
		case 'V':
			if (viewMode == 0){
				viewMode = 1;
				camera.SetDistance(0.5);
				camera.SetCenter(terrain.getGridSystem()->getSelectedGrid()->getXYZ());
				camera.SetRotation(Matrix4f::identity());
			}
			break;

		case 'r':
		case 'R':
			textureMode = (textureMode + 1) % 4;
			break;

		case 'e':
		case 'E':
			switch (textureMode){
			case 1:
				terrain.getGridSystem()->getSelectedGrid()->setTexture(Texture(Texture::MUD));
				break;
			case 2:
				terrain.getGridSystem()->getSelectedGrid()->setTexture(Texture(Texture::GRASS));
				break;
			case 3:
				terrain.getGridSystem()->getSelectedGrid()->setTexture(Texture(Texture::MOUNTAIN));
				break;
			default: //case 0
				Grid* g = terrain.getGridSystem()->getSelectedGrid();
				g->setTexture(Texture(Texture::BLACK));
				//Grid* g2 = terrain.getGridSystem().getSelectedGrid();
				cout << "changed" << endl;
				break;
			}
			break;

// x is left
// y is down
// z is backward
        case 'w':
        {
			if (viewMode == 0){
				break;
			}
            camera.SetCenter(camera.GetCenter()+cameraFront*cameraSpeed);
            break;
        }
        case 's':
        {
			if (viewMode == 0){
				break;
			}
            camera.SetCenter(camera.GetCenter()-cameraFront*cameraSpeed);
            break;
        }
        case 'a':
            {
				if (viewMode == 0){
					break;
				}
                camera.SetCenter(camera.GetCenter() + Vector3f::cross(cameraFront, cameraUp).normalized() * cameraSpeed);
                break;
            }
        case 'd':
            {
				if (viewMode == 0){
					break;
				}
                camera.SetCenter(camera.GetCenter() - Vector3f::cross(cameraFront, cameraUp).normalized() * cameraSpeed);
                break;
            }

		default:
			cout << "Unhandled key press " << key << "." << endl;
		}

		glutPostRedisplay();
	}

	// This function is called whenever a "Special" key press is
	// received.  Right now, it does nothing.
	void specialFunc(int key, int x, int y)
	{
		/*
		switch ( key )
		{
		default:
		break;
		}
		*/

		//glutPostRedisplay();
	}

	//  Called when mouse button is pressed.
	void mouseFunc(int button, int state, int x, int y)
	{
		if (state == GLUT_DOWN)
		{
			gMousePressed = true;

			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				camera.MouseClick(Camera::LEFT, x, y);
				break;
			case GLUT_MIDDLE_BUTTON:
				if (viewMode == 0){
					camera.MouseClick(Camera::MIDDLE, x, y);
				}
				break;
			case GLUT_RIGHT_BUTTON:
				if (viewMode == 0){
					camera.MouseClick(Camera::RIGHT, x, y);
				}
			default:
				break;
			}
		}
		else
		{
			camera.MouseRelease(x, y);
			gMousePressed = false;
		}
		glutPostRedisplay();
	}

	// Called when mouse is moved while button pressed.
	void motionFunc(int x, int y)
	{
		camera.MouseDrag(x, y, viewMode == 0 ? true : false);

		glutPostRedisplay();
	}

	// Called when the window is resized
	// w, h - width and height of the window in pixels.
	void reshapeFunc(int w, int h)
	{
		camera.SetDimensions(w, h);

		camera.SetViewport(0, 0, w, h);
		camera.ApplyViewport();

		// Set up a perspective view, with square aspect ratio
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		camera.SetPerspective(50);
		camera.ApplyPerspective();
	}


	// Initialize OpenGL's rendering modes
	void initRendering()
	{
		glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
		//glEnable(GL_LIGHTING);     // Enable lighting calculations
		//glEnable(GL_LIGHT0);       // Turn on light #0.

		// Setup polygon drawing
		glShadeModel(GL_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Clear to black
		glClearColor(0, 0, 0, 1);

		// Base material colors (they don't change)
		GLfloat diffColor[] = { 0.4, 0.4, 0.4, 1 };
		GLfloat specColor[] = { 0.9, 0.9, 0.9, 1 };
		GLfloat shininess[] = { 50.0 };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}

	void makeDisplayLists()
	{
		gAxisList = glGenLists(1);

		glNewList(gAxisList, GL_COMPILE);
		{
			// Save current state of OpenGL
			glPushAttrib(GL_ALL_ATTRIB_BITS);

			// This is to draw the axes when the mouse button is down
			glDisable(GL_LIGHTING);
			glLineWidth(3);
			glPushMatrix();
			glScaled(5.0, 5.0, 5.0);
			glBegin(GL_LINES);
			glColor4f(1, 0.5, 0.5, 1); glVertex3d(0, 0, 0); glVertex3d(1, 0, 0); //x is red
			glColor4f(0.5, 1, 0.5, 1); glVertex3d(0, 0, 0); glVertex3d(0, 1, 0); //y is green
			glColor4f(0.5, 0.5, 1, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 1); //z is blue

			glColor4f(0.5, 0.5, 0.5, 1);
			glVertex3d(0, 0, 0); glVertex3d(-1, 0, 0);
			glVertex3d(0, 0, 0); glVertex3d(0, -1, 0);
			glVertex3d(0, 0, 0); glVertex3d(0, 0, -1);

			glEnd();
			glPopMatrix();

			glPopAttrib();
		}
		glEndList();
	}

	void displayTerrain(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
		glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND);

		glLoadIdentity();                 // Reset the model-view matrix

		camera.ApplyModelview();

		if (terrainMode == 0){
			if (viewMode == 1){
				terrain.getGridSystem()->drawMesh(true);
			}
			else {
				terrain.getGridSystem()->drawMesh(false);
			}
		}
		else if (terrainMode == 1){
			camera.drawRay();
			terrain.getGridSystem()->drawMeshSkeleton(false);
		}
		else {
			camera.drawRay();
			terrain.getGridSystem()->drawMeshSkeleton(true);
		}
		int ij[2];
		terrain.getGridSystem()->getLastClickedGrid(camera, ij[0], ij[1]); //populate ij
		terrain.getGridSystem()->setSelectedGrid(ij[0], ij[1]);
		terrain.getGridSystem()->showSelectedGrid();

		if (viewMode == 1){ //roaming
			terrain.getGridSystem()->forceGroundedView(camera);
		}

		// This draws the coordinate axes when you're rotating, to
		// keep yourself oriented.
		// Use only to debug
		/*if (gMousePressed)
		{
			glPushMatrix();
			glTranslated(camera.GetCenter()[0], camera.GetCenter()[1], camera.GetCenter()[2]);
			glCallList(gAxisList);
			glPopMatrix();
		}*/

		glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
	}

}
// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char* argv[])
{
	/* initialize random seed: */
	srand(time(NULL));

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Initial parameters for window position and size
	glutInitWindowPosition(60, 60);
	glutInitWindowSize(600, 600);

	camera.SetDimensions(600, 600);

	Matrix4f eye = Matrix4f::identity().rotateX((M_PI / 4.0));
	camera.SetRotation(eye);
	camera.SetDistance(10);
	camera.SetCenter(Vector3f(5, 0, 5));

	glutCreateWindow("Graphics and Visualization Final");

	// Initialize OpenGL parameters.
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
	glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

	// Set up callback functions for mouse
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);

	// Set up the callback function for resizing windows
	glutReshapeFunc(reshapeFunc);

	float gridsize = 0.25f;

	PerlinNoise perlin = PerlinNoise();
	terrain = Terrain(perlin, 10, 10, gridsize);

	glutDisplayFunc(displayTerrain);

	makeDisplayLists();

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();

	return 0;	// This line is never reached.
}
