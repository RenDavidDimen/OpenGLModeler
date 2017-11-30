/* Snowman sample 
 * by R. Teather
 * Edited by Noel Brett
 */

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Vertices
float verts[8][3] = { {0,0,1}, {0,1,1}, {1,1,1}, {1,0,1}, {0,0,0}, {0,1,0}, {1,1,0}, {1,0,0} };

//	Colours
// [0] Black
// [1] White
// [2] Red
// [3] Orange
// [4] Yellow
// [5] Green
// [6] Blue
// [7] Purple
float cols[9][3] = {{0,0,0}, {1,1,1}, {1,0,0}, {1,0.64,0}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1}};
float baseColours[3][3] = {{1,0.85,0.73}, {1, 0.89, 0.71}, {1, 0.94, 0.84}};

float pos[] = {50,0,50};
float rot[] = {0,0,0};
float headRot[] = {0, 0, 0};

float eye[] = {150,100,150};

class sceneObject
{
	private:
		// Postion by array {x, y, z}
		float objPosition[3];
		
		// Angle of rotation about an axis given by {x, y, z}
		float objRotation[3];
		
		// Scale of object
		float objScale;
		
		// 
		int objMaterial;
		
		// 1: Cube 	2: Sphere  3: Teapot
		int objShape;

	public:
		// 	***************************
		//			Constructor
		// 	***************************
		sceneObject()
		{
			objPosition[0] = 0;
			objPosition[1] = 0;
			objPosition[2] = 0;

			objRotation[0] = 0;
			objRotation[1] = 0;
			objRotation[2] = 0;

			objScale = 1;
			objMaterial = 1;
			objShape = 1;
		}

		// 	********************************
		//			Setter Functions
		// 	********************************

		// Update Position
		void setPosition(float newPosition[3])
		{
			objPosition[0] = newPosition[0];
			objPosition[1] = newPosition[1];
			objPosition[2] = newPosition[2];
		}

		// Update Rotation
		void setRotation(float newRotation[3])
		{
			objRotation[0] = newRotation[0];
			objRotation[1] = newRotation[1];
			objRotation[2] = newRotation[2];
		}

		// Update Scale
		void setScale(float newScale)
		{
			objScale = newScale;
		}

		// Update Material
		void setMaterial(float newMaterial)
		{
			objMaterial = newMaterial;
		}

		// Update Shape
		void setShape(float newShape)
		{
			objShape = newShape;
		}

		// 	********************************
		//			Getter Functions
		// 	********************************

		// Get Object Position
		float getPosX()
		{
			return objPosition[0];
		}

		float getPosY()
		{
			return objPosition[1];
		}

		float getPosZ()
		{
			return objPosition[2];
		}

		// Get Object Rotation
		float getRotX()
		{
			return objRotation[0];
		}

		float getRotY()
		{
			return objRotation[1];
		}

		float getRotZ()
		{
			return objRotation[2];
		}

		float getScale()
		{
			return objScale;
		}

		// Update Material
		int getMaterial()
		{
			return objMaterial;
		}

		// Update Shape
		int getShape()
		{
			return objShape;
		}

		// ******************************
		//			Class Methods
		// ******************************

		void draw()
		{
			glPushMatrix();

			// Position
			glTranslatef(objPosition[0], objPosition[1], objPosition[2]);
			
			// Rotation
			glRotatef(objRotation[0], 1, 0, 0);
			glRotatef(objRotation[1], 0, 1, 0);
			glRotatef(objRotation[2], 0, 0, 1);

			// Material
			glColor3f(0.5, 0.5, 0.5);

			switch (objShape){
				case 1:
			    	glutSolidCube(objScale);
			    	break;
			    case 2:
			    	glutSolidSphere(objScale, 50, 50); //radius,slices,stacks
			    	break;
			    case 3:
			    	glutSolidTeapot(objScale);
			    	break;
			}

			glPopMatrix();

		}		
};

/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

void drawGrid()
{
	for (float i = 0; i<100; i = i +10)
	{
		glColor3fv(cols[1]);
		glLineWidth(2);
		glBegin(GL_LINES);
			// x-axis markers
			glVertex3f(i, 0, 0);
			glVertex3f(i, 0, 100);
			// z-axis markers
			glVertex3f(0, 0, i);
			glVertex3f(100, 0, i);
		glEnd();
	}
}

void drawScene()
{
	float vert [7] [3] = {{0,0,0}, {100,0,0}, {100,0,100}, {0,0,100}, {0,50,0}, {100,50,0}, {0,50,100}};
	
	// Draws floor and backgrounds
	glColor3fv(baseColours[0]);
	drawPolygon(0, 1, 2, 3, vert);
	glColor3fv(baseColours[1]);
	drawPolygon(0, 4, 6, 3, vert);
	glColor3fv(baseColours[2]);
	drawPolygon(0, 4, 5, 1, vert);

	drawGrid();
}

void keyboard(unsigned char key, int x, int y)
{
	int i = 0;
	int exitStatus = 0;

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;
		case '1':
			printf("Creating Cube\n");
			break;
		case '2':
			printf("Creating Sphere\n");
			break;
		case '3':
			printf("Creating Teapot\n");
			break;
			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
    //	*******************************
	// 			CAMERA CONTROLS
    //	*******************************

	/* arrow key presses move the camera */
	switch(key)
	{
		// Moving in the X-Direction
		case GLUT_KEY_LEFT:
			eye[0]-=1;
			break; 
		case GLUT_KEY_RIGHT:
			eye[0]+=1;
			break;
		// Moveing in the Z direction
		case GLUT_KEY_UP:
			eye[2]-=1;
			break; 
		case GLUT_KEY_DOWN:
			eye[2]+=1;
			break;
    }
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
    
    /************************************************************************
     
                            PERSPECTIVE SET UP!
     
     modelview moves the eye and objects, projection is for camera type
     frustum / ortho left, right, bottom, top, nearVal, farVal
     
     ************************************************************************/
	//TUTORIAL: Added from code snippet 1 from tutorial pdf
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 1, 300); 
}

void DrawSnowman(float* pos, float* rot)
{
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	//draw body
	glColor3f(1,1,1);
	glutSolidSphere(1, 16, 16);

	//draw buttons
	glPushMatrix();
	glTranslatef(0, 0.35, 0.9);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.15, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.05, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();


	glPushMatrix();
	//translate relative to body, and draw head
	glTranslatef(0, 1.25, 0);
	glRotatef(headRot[1], 0, 1, 0); //turn the head relative to the body
	glColor3f(1,1,1);
	glutSolidSphere(0.5, 16, 16);
	
	//translate and draw right eye
	glPushMatrix();
	glTranslatef(0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw left eye
	glPushMatrix();
	glTranslatef(-0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw nose
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1,0.4,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPopMatrix();//body
	glPopMatrix();//snowman
}

void initializeObjectList(sceneObject object[])
{
	// Intialize Stucture Array
	// for(int i = 0; i <10; i++)
	// {
	// 	object[i].objShape = 0;
	// 	printf("Object Shape [%i]: %i\n", i,  object[i].objShape);
	// }
	// printf(object);
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /************************************************************************
     
                                    CAMERA SET UP
     
     ************************************************************************/
	//TUTORIAL: Added from 2nd code snippet from tutorial pdf
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);

	drawScene();
	sceneObject objectList[10];

	initializeObjectList(objectList);

	DrawSnowman(pos, rot);
	
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Assignment 3 - Modeler");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
