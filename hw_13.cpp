
#ifdef __APPLE_CC__
#include <glut.h>
#else
#include <glut.h>
#endif
//注意轉動的時候 輸入法不能是中文

#include <iostream>
#include <fstream>
#include<glut.h>
#include<vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#define _USE_MATH_DEFINES // for C
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <time.h>  
#define PI 3.1415926535
#define X .525731112119133606f
#define Z .850650808352039932f
#define MENU_FILL 0
#define MENU_LINE 1

void buildPopupMenu();
void menu(int);
void changeSize(int, int);
void renderScene();
void subdivide(GLfloat[3], GLfloat[3], GLfloat[3], int);
void normalize(float[3]);
void myKeyboard(unsigned char, int, int);

GLfloat vdata[20][3] = { {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
								{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
								{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} };

GLuint tindices[29][3] = { {1,4,0}, {4,9,0}, {4,9,5}, {8,5,4}, {1,8,4},
								{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
								{3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
								{10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7} };
GLfloat thetaX = 0, thetaY = 0, thetaZ = 0, thetaArb = 0;
int depth = 0;
int windowWidth = 1200, windowHeight = 600;
int renderMode = GL_FILL;

int main(int argc, char** argv)
{
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };

	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.6, 0.4, 1.0 };
	GLfloat mat_ambient[] = { 0.8, 0.6, 0.4, 1.0 };
	GLfloat mat_shininess = { 20.0 };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(150, 80);
	glutCreateWindow("Lab13");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Set lighting intensity, color and position
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	buildPopupMenu();
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return 0;
}

void buildPopupMenu() {
	glutCreateMenu(menu);
	glutAddMenuEntry("Fill", MENU_FILL);
	glutAddMenuEntry("Line", MENU_LINE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int option) {
	switch (option) {
	case MENU_FILL:
		renderMode = GL_FILL;
		break;
	case MENU_LINE:
		renderMode = GL_LINE;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void changeSize(int w, int h) {
	windowWidth = w, windowHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
	GLfloat rotXMatrix[] = {
		1.0f, 0.0f,                      0.0f,                           0.0f,
		0.0f, cos(thetaX * PI / 180.0f), sin(thetaX * PI / 180.0f),      0.0f,
		0.0f, sin(thetaX * PI / 180.0f) * -1, cos(thetaX * PI / 180.0f),      0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	GLfloat rotYMatrix[] = {
		cos(thetaY * PI / 180.0f),       0.0f, sin(thetaY * PI / 180.0f) * -1,      0.0f,
		0.0f,                            1.0f, 0.0f,                                0.0f,
		sin(thetaY * PI / 180.0f),       0.0f, cos(thetaY * PI / 180.0f),           0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	GLfloat rotZMatrix[] = {
		cos(thetaZ * PI / 180.0f), sin(thetaZ * PI / 180.0f), 0.0f,  0.0f,
		sin(thetaZ * PI / 180.0f) * -1, cos(thetaZ * PI / 180.0f),   0.0f,  0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, renderMode);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_FLAT);
	glViewport(0, 0, windowWidth / 3, windowHeight);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0, 0, 0, 0, 1, 0);

	glMultMatrixf(rotXMatrix);
	glMultMatrixf(rotYMatrix);
	glMultMatrixf(rotZMatrix);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 20; i++)
	{
		glNormal3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glNormal3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glNormal3fv(&vdata[tindices[i][2]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}

	glEnd();

	glViewport(windowWidth / 3, 0, windowWidth / 3, windowHeight);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0, 0, 0, 0, 1, 0);
	glShadeModel(GL_SMOOTH);

	glMultMatrixf(rotXMatrix);
	glMultMatrixf(rotYMatrix);
	glMultMatrixf(rotZMatrix);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 20; i++) {
		glNormal3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glNormal3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glNormal3fv(&vdata[tindices[i][2]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}

	glEnd();

	glViewport(windowWidth / 3 * 2, 0, windowWidth / 3, windowHeight);
	glLoadIdentity();
	gluLookAt(.0, .0, 1.0, 0, 0, 0, 0, 1, 0);
	glMultMatrixf(rotXMatrix);
	glMultMatrixf(rotYMatrix);
	glMultMatrixf(rotZMatrix);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++)
	{
		subdivide(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], depth);
	}
	glEnd();
	glutSwapBuffers();
}

void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{
	GLfloat v12[3], v23[3], v31[3]; int i;
	if (depth == 0) {
		glNormal3fv(&v1[0]);
		glVertex3fv(&v1[0]);
		glNormal3fv(&v2[0]);
		glVertex3fv(&v2[0]);
		glNormal3fv(&v3[0]);
		glVertex3fv(&v3[0]);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}
	for (int i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}
	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}

void normalize(float v[3])
{
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= d; v[1] /= d; v[2] /= d;
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		thetaX = 0, thetaY = 0, thetaZ = 0;
		break;
	case 'a':
		thetaX -= 3;
		break;
	case 'd':
		thetaX += 3;
		break;
	case 'w':
		thetaY += 3;
		break;
	case 's':
		thetaY -= 3;
		break;
	case 'z':
		thetaZ -= 3;
		break;
	case 'x':
		thetaZ += 3;
		break;
	case '+':
		depth += 1;
		break;
	case '-':
		if (depth > 0) {
			depth -= 1;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}