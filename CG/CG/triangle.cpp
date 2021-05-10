#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <math.h>
//#include <GL/glut.h>
#define DLL_EXPORT
#define PI 3.14159265
#define MENU_LIGHTING 0
#define MENU_POLYMODE 1
#define MENU_TEXTURING 2
#define MENU_EXIT 3
#define gourd 11
#define Lamp 12
#define octahedron 13
#define teapot 14
#define Point 15
#define Line 16
#define Face 17
#define SingleColor 18
#define RandomColors 19
#define On 20
#define Off 21
int random = 0;
int screenWidth = 640;
int screenHeight = 480;
int thing = 1;
bool isChange = false;
GLfloat sun_light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光
GLfloat pointx = 200, pointy = 200;
GLfloat xx = 0.0, yy = 0.0;
GLfloat degree1 = 0.0, degree2 = 0.0, degree3 = 0.0, pivotX = 0.0;
double tx = 0, ty = 0, tz = 0, thetaX = 0, thetaY = 0, thetaZ = 0, pivotY = 0.0, pivotZ = 0.0;
void ChangeSize(int, int);
void RenderScene(void);
void buildPopupMenu();
void myMouse(int button, int state, int x, int y);
string filePath = "data/gourd.obj";
ObjLoader objModel = ObjLoader(filePath);

//安置光源
void setLightRes() {
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //光源的位置在世界坐标系圆心，齐次坐标形式
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA模式的环境光，为0
	//GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBA模式下的镜面光 ，全白光
	//glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	//glLightfv(GL_LIGHT6, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0);   //使用指定灯光
}

void myIdle()
{
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case'r':
		thetaX = 0;
		thetaY = 0;
		thetaZ = 0;
		degree1 = 0.0;
		degree2 = 0.0;
		degree3 = 0.0;
		break;
	case'a':
		thetaX += 3; 
		degree1 += 10;
		break;
	case'd':
		thetaX -= 3;
		degree1 -= 10;
		break;
	case'w':
		thetaY += 3;
		degree2 += 10;
		break;
	case's':
		thetaY -= 3;
		degree2 -= 10;
		break;
	case'z':
		thetaZ += 3;
		degree3 += 10;
		break;
	case'x':
		thetaZ -= 3;
		degree3 -= 10;
		break;
	}
	glutPostRedisplay();
}
void mySpceialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		tx -= 0.2;
		pivotX -= 0.2;
		break;
	case GLUT_KEY_RIGHT:
		tx += 0.2;
		pivotX += 0.2;
		break;
	case GLUT_KEY_UP:
		ty += 0.2;
		pivotY += 0.2;
		break;
	case GLUT_KEY_DOWN:
		ty -= 0.2;
		pivotY -= 0.2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
//Clears the current window and draws a triangle.
//void glRotatef() {
//	GLfloat angle;
//	GLfloat x;
//	GLfloat y;
//	GLfloat z;
//};
void display() {
	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);
	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1); 
	glVertex3f(-0.5f, -0.5f, 0.0f);//x,y,z
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glColor3f(0, 1, 0);

	glEnd();
	glFlush();
}


void selectFromMenu(int option)
{
	switch (option) {
	case gourd:
		filePath = "data/gourd.obj";
		thing = 1;
		break;
	case Lamp:
		filePath = "data/Lamp.obj";
		thing = 2;
		break;
	case octahedron:
		filePath = "data/octahedron.obj";
		thing = 3;
		break;
	case teapot:
		filePath = "data/teapot.obj";
		thing = 4;
		break;
	case Point:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case Line:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case Face:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case SingleColor://白色
		sun_light_diffuse[0] = 1;
		sun_light_diffuse[1] = 1;
		sun_light_diffuse[2] = 1;
		break;
	case RandomColors:
		srand(time(0));
		random = rand() % 5;
		if (random == 0) {//蓝色
			sun_light_diffuse[0] = 0;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 1;
		}
		else if (random == 1) {//绿色
			sun_light_diffuse[0] = 0;
			sun_light_diffuse[1] = 1;
			sun_light_diffuse[2] = 0;
		}
		else if (random == 2) {//红色
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 0;
		}
		else if (random == 3) {//紫色
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 1;
		}
		else if (random == 4) {//黄色
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 1;
			sun_light_diffuse[2] = 0;
		}
		break;
	case On:
		isChange = true;
		break;
	case Off:
		//….
		break;
	default:
		break;
	}
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Simple Rectangle");
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpceialKey);
	//glutMotionFunc();
	//glutIdleFunc();
	buildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
void buildPopupMenu()
{
	int menu,obj_submenu,ren_submenu,col_submenu,bou_submenu;
	obj_submenu = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("gourd", gourd);
	glutAddMenuEntry("Lamp", Lamp);
	glutAddMenuEntry("octahedron", octahedron);
	glutAddMenuEntry("teapot", teapot);

	ren_submenu = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("Point", Point);
	glutAddMenuEntry("Line", Line);
	glutAddMenuEntry("Face", Face);

	col_submenu = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("Single Color", SingleColor);
	glutAddMenuEntry("Random Colors", RandomColors);

	bou_submenu = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("On", On);
	glutAddMenuEntry("Off", Off);

	menu = glutCreateMenu(selectFromMenu);
	glutAddSubMenu("Object", obj_submenu);
	glutAddSubMenu("Render Mode", ren_submenu);
	glutAddSubMenu("Color Mode", col_submenu);
	glutAddSubMenu("Bounding Box", bou_submenu);
}

void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN&& button == GLUT_LEFT_BUTTON)
	{
		pointx = x;
		pointy = y;
	}
}

void drawlines() {
	GLfloat x = pointx;
	GLfloat y = pointy;
	xx = ((2 * x / 400) - 1) * 10;
	yy = (1 - (2 * y / 400)) * 10;
	glBegin(GL_LINES);
	glColor3f(0, 0, 0); glVertex3f(0, 0, 0);
	glColor3f(0, 0, 0); glVertex3f(xx, yy, 0);
	glEnd();
	glFlush();
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_MODELVIEW);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//像素传输
	glLoadIdentity();
	//drawlines();
	if (isChange) {
		if (thing == 1) {
			glViewport(0, 0, 400, 400);
		}
		else if (thing == 2) {
			glViewport(0, 0, 600, 600);
		}
		else if (thing == 3) {
			glViewport(0, 0, 800, 800);
		}
		else {
			glViewport(0, 0, 200, 200);
		}
		isChange = false;
	}
	GLfloat c = cos(degree1 * PI / 180.0);
	GLfloat s = sin(degree1 * PI / 180.0);
	GLfloat t = 1.0 - c;
	// if axis is not already normalised then uncomment this
	GLfloat magnitude = sqrt(pointx*pointx + pointy * pointy);

	GLfloat x = pointx / magnitude;
	GLfloat y = pointy / magnitude;
	GLfloat z = 0 / magnitude;

	GLfloat m[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 };

	m[0] = c + x * x*t;
	m[5] = c + y * y*t;
	m[10] = c + z * z*t;
	m[4] = x * y*t + z * s;
	m[1] = x * y*t - z * s;
	m[8] = x * z*t - y * s;
	m[2] = x * z*t + y * s;
	m[9] = y * z*t + x * s;
	m[6] = y * z*t - x * s;

	GLfloat MatrixX[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	pivotX, 0.0, 0.0, 1.0 };

	GLfloat MatrixY[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, pivotY, 0.0, 1.0 };

	GLfloat XMatrix[] = {
	1.0,0.0,					   0.0,						  0.0,
	0.0,cos(degree1 * PI / 180.0), -sin(degree1 * PI / 180.0),0.0,
	0.0,sin(degree1 * PI / 180.0), cos(degree1 * PI / 180.0), 0.0,
	0.0,0.0,					   0.0,						  1.0 };

	GLfloat YMatrix[] = {
	cos(degree2 * PI / 180.0), 0.0, sin(degree2 * PI / 180.0),0.0,
	0.0,					   1.0, 0.0,					  0.0,
	-sin(degree2 * PI / 180.0),0.0, cos(degree2 * PI / 180.0),0.0,
	0.0,					   0.0, 0.0,					  1.0 };
	
	GLfloat ZMatrix[] = {
	cos(degree3 * PI / 180.0), -sin(degree3 * PI / 180.0), 0.0,0.0,
	sin(degree3 * PI / 180.0),cos(degree3 * PI / 180.0),   0.0,0.0,
	0.0,					  0.0,						   1.0,0.0,
	0.0,					  0.0,						   0.0,1.0 };

	//glRotatef(thetaX, 1.0, 0.0, 0.0); // Rotate 90 on x
	//glRotatef(thetaY, 0.0, 1.0, 0.0);
	//glRotatef(thetaZ, 0.0, 0.0, 1.0);
	//glMultMatrixf(rotMatrix);
	//glTranslatef(tx, ty, tz);

	glMultMatrixf(XMatrix);			//旋轉
	glMultMatrixf(YMatrix);
	glMultMatrixf(ZMatrix);

	glMultMatrixf(MatrixX);			//平移
	glMultMatrixf(MatrixY);

	objModel = ObjLoader(filePath);
	objModel.Draw();
	setLightRes();

	//glBegin(GL_POINTS);
	//glVertex2i(1, 3);                    //画一些点
	//glVertex2i(2, 1);
	//glEnd();

	//glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// // Front 
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(1.0f, -1.0f, 1.0f);

	//// Right
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(1.0f, -1.0f, -1.0f);

	//// Back
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(-1.0f, -1.0f, -1.0f);

	//// Left
	//glColor3f(1.0f, 0.0f, 0.0f);       // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);       // Green
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glEnd();   // Done drawing the pyramid

	//glLoadIdentity();

	//glBegin(GL_LINES);
	//glColor3f(1, 0, 1);//紫
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 0, 30);
	//glEnd();

	//glBegin(GL_LINES);
	//glColor3f(1,1 , 0);//hong
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 30, 0);
	//glEnd();

	//glBegin(GL_LINES);
	//glColor3f(0, 0, 0);//hei
	//glVertex3f(0, 0, 0);
	//glVertex3f(30, 0, 0);
	//glEnd();

	glFlush();
	glutSwapBuffers();
}