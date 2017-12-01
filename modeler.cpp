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
#include <math.h>


//	***************************
//			Shape Class
//	***************************
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
		// If shape is set to -1, class object is empty
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

			objScale = 0;
			objMaterial = 1;
			objShape = -1;
		}

		// 	********************************
		//			Setter Functions
		// 	********************************

		// Update Position
		void setPosition(float newX, float newY, float newZ)
		{
			objPosition[0] = newX;
			objPosition[1] = newY;
			objPosition[2] = newZ;
		}

		// Update Rotation
		void setRotation(float newRotX, float newRotY, float newRotZ)
		{
			objRotation[0] = newRotX;
			objRotation[1] = newRotY;
			objRotation[2] = newRotZ;
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
			/*if(objPosition[1]-(0.5 * objScale) < 0)
			{
				objPosition[1] = objScale;
			}*/

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
			    case 4:
			    	glutSolidCone(0.5 * objScale, objScale, 50, 50);
			    	break;
			    // case 5:
			    // 	glutSolidCylinder(0.5 * objScale, objScale, 50, 50);
			    // 	break;
			}

			glPopMatrix();

		}

		void move(float newX, float newY, float newZ)
		{
			objPosition[0]+= newX;
			objPosition[1]+= newY;
			objPosition[2]+= newZ;
		}

		void rotate(float newX, float newY, float newZ)
		{
			objRotation[0]+= newX;
			objRotation[1]+= newY;
			objRotation[2]+= newZ;
		}	
};

//	********************************
//			Global Variables
//	********************************

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

float eye[3] = {100,75,100};

double* m_start = new double[3];
double* m_end = new double[3];

int maxShapesNum = 20;
int selectedObject = -1;

sceneObject objectList[20];

// Lighting
float light_pos[] = {50, 100, 50, 1.0};
float amb0[4] = {1,1,1,1};
float diff0[4] = {0.5, 0, 0.5, 1}; // Shadows
float spec0[4] = {1,1,1,1};

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
	for (float i = -50; i<=50; i = i +10)
	{
		if(i == 0)
		{
			glColor3fv(cols[0]);
		}
		else{
			glColor3fv(cols[1]);
		}
		glLineWidth(3);
		glBegin(GL_LINES);
			// x-axis markers
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);
			// z-axis markers
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);
		glEnd();
	}
}

void drawScene()
{
	float vert [7] [3] = {{-50,0,-50}, {50,0,-50}, {50,0,50}, {-50,0,50}, {-50,50,-50}, {50,50,-50}, {-50,50,50}};
	
	// // Draws floor and backgrounds
	// glColor3fv(baseColours[0]);
	// drawPolygon(0, 1, 2, 3, vert);
	// glColor3fv(baseColours[1]);
	// drawPolygon(0, 4, 6, 3, vert);
	// glColor3fv(baseColours[2]);
	// drawPolygon(0, 4, 5, 1, vert);

	/* LIGHTING */
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	drawGrid();
}

void drawObjects()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < maxShapesNum; i++){
		if (objectList[i].getShape() > 0) {
			objectList[i].draw();
		}
	}

}

void addObject(int newScale, int newShape){
	//Loop through object array and look for an empty slot
	for (int i = 0; i < maxShapesNum; i++){
		if (objectList[i].getShape() < 1){
			objectList[i].setPosition(0, 10, 0);
			objectList[i].setScale(newScale);
			objectList[i].setShape(newShape);
			selectedObject = i;
			break;
		}
	}
}

// 	*********************************
// 			Keyboard Controls
// 	*********************************
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
			addObject(10, 1);
			printf("Creating Cube\n");
			break;
		case '2':
			addObject(10, 2);
			printf("Creating Sphere\n");
			break;
		case '3':
			addObject(10, 3);
			printf("Creating Teapot\n");
			break;
		// Remove Objects
		case 'R':
			for (int i = 0; i < maxShapesNum; i++){
				if (objectList[i].getShape() > 0)
				{
					objectList[i].setShape(-1);
				}
			}
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
			glClear(GL_COLOR_BUFFER_BIT);
			printf("Clearing Objects\n");
			break;
		// Save Object List
		case 'S':
			printf("Saving Object List\n");
			break;
		// Load Object List
		case 'L':
			printf("Loading Object List\n");
			break;
		// Move Selected Object
		case 'w':
			objectList[selectedObject].move(0, 0, -1);
			break;
		case 'a':
			objectList[selectedObject].move(-1, 0, 0);
			break;
		case 's':
			objectList[selectedObject].move(0, 0, 1);
			break;
		case 'd':
			objectList[selectedObject].move(1, 0, 0);
			break;
		case 'r':
			objectList[selectedObject].move(0, 1, 0);
			break;
		case 'f':
			objectList[selectedObject].move(0, -1, 0);
			break;
		// Rotate - Counter Clockwise
		case 'z':
			objectList[selectedObject].rotate(1, 0, 0);
			break;
		case 'x':
			objectList[selectedObject].rotate(0, 1, 0);
			break;
		case 'c':
			objectList[selectedObject].rotate(0, 0, 1);
			break;
		// Rotate - Clockwise about axis
		// Works with Shift or Caps lock
		case 'Z':
			objectList[selectedObject].rotate(-1, 0, 0);
			break;
		case 'X':
			objectList[selectedObject].rotate(0, -1, 0);
			break;
		case 'C':
			objectList[selectedObject].rotate(0, 0, -1);
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

void mouse(int btn, int state, int x, int y){
	if(btn == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			printf("clicking\n");
			printf("(%f,%f,%f)----(%f,%f,%f)\n", m_start[0], m_start[1], m_start[2], m_end[0], m_end[1], m_end[2]);

			double matModelView[16], matProjection[16];
			int viewport[4];

			glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
			glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
			glGetIntegerv(GL_VIEWPORT, viewport);

			double winX = (double)x;
			double winY = viewport[3] - (double)y;

			gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport, &m_start[0], &m_start[1],  &m_start[2]);
			gluUnProject(winX, winY, 160.0, matModelView, matProjection, viewport, &m_end[0], &m_end[1],  &m_end[2]);
			
			printf("(%f,%f,%f)----(%f,%f,%f)\n\n", m_start[0], m_start[1], m_start[2], m_end[0], m_end[1], m_end[2]);

			//------------------------------------------

			double* R0 = new double[3];
			double* Rd = new double[3];

			double xDiff = m_end[0] - m_start[0];
			double yDiff = m_end[1] - m_start[1];
			double zDiff = m_end[2] - m_start[2];

			double mag = sqrt(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);
			R0[0] = m_start[0];
			R0[1] = m_start[1];
			R0[2] = m_start[2];

			Rd[0] = xDiff / mag;
			Rd[1] = yDiff / mag;
			Rd[2] = zDiff / mag;

			double A = Rd[0] * Rd[0] + Rd[1] * Rd[1] + Rd[2] * Rd[2];

			double* R0Pc = new double[3];

			for(int i = 0; i < 20; i++){
				if(objectList[i].getShape() != -1){
					R0Pc[0] = R0[0] - objectList[i].getPosX();
					R0Pc[1] = R0[1] - objectList[i].getPosY();
					R0Pc[2] = R0[2] - objectList[i].getPosZ();

					double B = 2 * ( R0Pc[0] * Rd[0] + R0Pc[1] * Rd[1] + R0Pc[2] * Rd[2]);
					double C = (R0Pc[0]*R0Pc[0] + R0Pc[1] * R0Pc[1] + R0Pc[2] * R0Pc[2]) - (objectList[i].getScale() * objectList[i].getScale());

					double discriminent = B*B - 4* A *C;

					if(discriminent < 0)
						printf("no intersection!\n");
					else{
						double t1 = (-B + sqrt(discriminent)) / (2*A);
						double t2 = (-B - sqrt(discriminent)) / (2*A);

						selectedObject = i;

						printf("Intersection with object %i at t= %f, %f\n", i, t1, t2);
					}
				}
			}

			/*R0Pc[0] = R0[0] - pos[0];
			R0Pc[1] = R0[1] - pos[1];
			R0Pc[2] = R0[2] - pos[2];

			double B = 2 * ( R0Pc[0] * Rd[0] + R0Pc[1] * Rd[1] + R0Pc[2] * Rd[2]);
			double C = (R0Pc[0]*R0Pc[0] + R0Pc[1] * R0Pc[1] + R0Pc[2] * R0Pc[2]) - (20 * 20);

			double discriminent = B*B - 4* A *C;

			if( discriminent < 0)
				printf("no intersection!\n");
			else{
				double t1 = (-B + sqrt(discriminent)) / (2*A);
				double t2 = (-B - sqrt(discriminent)) / (2*A);

				printf("Intersection at t= %f, %f\n", t1, t2);
			}*/
		}
	}
}
// ****************************
//			Menu Items
// ****************************
void menuProc(int value){
	switch(value) {
		case 0:
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
			glClear(GL_COLOR_BUFFER_BIT);
			glutSwapBuffers();
			drawScene();
			printf("Canvas Cleared\n");
			break;
		case 1:
			printf("Controls go here\n");
			break;
		case 2:
			printf("Exiting Program\n");
			exit(0);
			break;
		case 11:
			printf("Set Colour: Red\n");
			// objectList[selectedObject].setMaterial();
			break;
		case 21:
			objectList[selectedObject].setShape(1);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
			glClear(GL_COLOR_BUFFER_BIT);
			drawObjects();
			drawScene();
			glutSwapBuffers();
			break;
		case 22:
			objectList[selectedObject].setShape(2);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
			glClear(GL_COLOR_BUFFER_BIT);
			drawObjects();
			drawScene();
			glutSwapBuffers();
			break;
		case 23:
			objectList[selectedObject].setShape(3);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
			glClear(GL_COLOR_BUFFER_BIT);
			drawObjects();
			drawScene();
			glutSwapBuffers();
			break;
	}
}

void mouseMenu(){
	//int subMenu_id = glutCreateMenu(menuProc2);

	// Shapes will be assigned as the following
	// 2 - Red
	// 3 - Orange
	// 4 - Yellow
	// 5 - Green
	// 6 - Blue
	// 7 - Purple
	// 0 - Black
	// 1 - White
	int subMenu_colour = glutCreateMenu(menuProc);
	glutAddMenuEntry("Red",		11);
	glutAddMenuEntry("Orange",	12);
	glutAddMenuEntry("Yellow",	13);
	glutAddMenuEntry("Green",	14);
	glutAddMenuEntry("Blue",	15);
	glutAddMenuEntry("Purple",	16);
	glutAddMenuEntry("White",	17);
	glutAddMenuEntry("Black",	18);

	// Shapes will be assigned as the following
	// 1 - Cubes
	// 2 - Spheres
	// 3 - Teapots
	int subMenu_shapes = glutCreateMenu(menuProc);
	glutAddMenuEntry("Cube",		21);
	glutAddMenuEntry("Sphere",		22);
	glutAddMenuEntry("Teapot",	23);

	// Main menu layout
	int main_id = glutCreateMenu(menuProc);
	glutAddSubMenu("Colour", subMenu_colour);
	glutAddSubMenu("Change Shape", subMenu_shapes);
	glutAddMenuEntry("Clear Canvas", 0);
	glutAddMenuEntry("Help", 1);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	drawObjects();
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
	glLoadIdentity();
	gluPerspective(45, 1, 1, 300);

	m_start[0] = 0;
	m_start[1] = 0;
	m_start[2] = 0;

	m_end[0] = 0;
	m_end[1] = 0;
	m_end[2] = 0;
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

	/* LIGHTING */
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	drawObjects();
	drawScene();

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	// Initialize Windows
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Assignment 3 - Modeler");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	init();
	mouseMenu();
	
	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
