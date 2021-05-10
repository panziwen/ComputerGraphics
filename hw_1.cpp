#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <freeglut.h>
#include <time.h>
#include <iostream>
#include "ObjLoader.h"
using namespace std;
string f;
#define PI 3.14159265
#define GOURD 0
#define LAMP 1
#define OCTAHEDRON 2
#define TEAPOT 3
#define POINT 4
#define LINE 5
#define FACE 6
#define SINGLE 7
#define RANDOM 8
#define ON 9
#define OFF 10
int random = 0;
GLfloat sun_light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float degreex = 0, degreey = 0, degreez = 0;
void ChangeSize(int , int );					 
void RenderScene(void);		
void selectFromMenu(int);
int buildPopupMenu(void);
void myKeyboard(unsigned char, int, int);
void mySpaceialKey(int, int, int);
void myMouse(int, int, int x, int y);
void drawCoordinates();
void line();
float tx, tz, ty;
float x=0, y=0, z=0;
float posx=200, posy=0;
int px=200, py=0;
int dtype = 0, cctype = 0;
int main(int argc, char** argv) 
{
	tx = 0;
	ty = 0;
	tz = 0;
	x = 0;
	y = 0; 
	z = 0;
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
   glutInitWindowSize(400,400);				 
   glutInitWindowPosition(600,80);
   //glutCreateWindow("Simple Rectangle");
   glutCreateWindow("Moving Cube");
   //SetupRC();
   buildPopupMenu();
   glutReshapeFunc(ChangeSize);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyboard);
   glutSpecialFunc(mySpaceialKey);
   glutDisplayFunc(RenderScene);
   buildPopupMenu();
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutMainLoop();	
   return 0; 
} 
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		degreey -= 10;
		break;
	case 's':
		degreey += 10;
		break;
	case 'a':
		degreex -= 10;
		break;
	case 'd':
		degreex += 10;
		break;
	case 'q':
		degreez -= 10;
		break;
	case 'e':
		degreez += 10;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void mySpaceialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		tx -= 0.2;
		break;
	case GLUT_KEY_RIGHT:
		tx += 0.2;
		break;
	case GLUT_KEY_UP:
		ty += 0.2;
		break;
	case GLUT_KEY_DOWN:
		ty -= 0.2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void setLightRes() {
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //光源的位置在世界坐标系圆心，齐次坐标形式
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA模式的环境光，为0
	//GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白�?
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBA模式下的镜面�?，全白光
	//glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	//glLightfv(GL_LIGHT6, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0);   //使用指定灯光
}
void menuSelect(int option)
{
	switch(option)
	{
	case 0:
		glShadeModel(GL_FLAT);
		glutPostRedisplay();
		break;
	case 1:
		glShadeModel(GL_SMOOTH);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}


void ChangeSize(int w, int h) 
{ 
   printf("Window Size= %d X %d\n",w,h); 
   glViewport(0, 0, w, h);             
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   glOrtho(-10,10,-10,10,-10,10);       
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
} 
void RenderScene(void) 
{
	double c = cos(degreex * PI / 180.0);
	double s = sin(degreex * PI / 180.0);
	double t = 1.0 - c;
	// if axis is not already normalised then uncomment this
	double magnitude = sqrt(px*px + py * py);

	double cx = px / magnitude;
	double cy = py / magnitude;
	double cz = 0;

	GLfloat m[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 };

	m[0] = c + cx * cx*t;
	m[5] = c + cy * cy*t;
	m[10] = c + cz * cz*t;
	m[4] = cx * cy*t + cz * s;
	m[1] = cx * cy*t - cz * s;
	m[8] = cx * cz*t - cy * s;
	m[2] = cx * cz*t + cy * s;
	m[9] = cy * cz*t + cx * s;
	m[6] = cy * cz*t - cx * s;
	GLfloat translateMatrix[] = {	1.0, 0.0, 0.0, 0.0,
									0.0, 1.0, 0.0, 0.0,
									0.0, 0.0, 1.0, 0.0,
									tx, ty, tz, 1.0 };

	//GLfloat rotMatrixx[] = { cos(degreey * PI / 180.0), 0.0, sin(degreey * PI / 180.0),0.0,
	//						 0.0,1.0, 0.0,0.0,
	//						 -sin(degreey * PI / 180.0),0.0, cos(degreey * PI / 180.0),0.0,
	//						 0.0,0.0, 0.0,1.0 };//X����ת 

	//GLfloat rotMatrixy[] = { 1.0, 0.0, 0.0,0.0,
	//					 0.0,cos(degreex * PI / 180.0), -sin(degreex * PI / 180.0),0.0,
	//					 0.0,sin(degreex * PI / 180.0), cos(degreex * PI / 180.0),0.0,
	//					 0.0,0.0, 0.0,1.0 };//Y����ת 

	//GLfloat rotMatrixz[] = { cos(degreez * PI / 180.0), -sin(degreez * PI / 180.0), 0.0,0.0,
	//					     sin(degreez * PI / 180.0),cos(degreez * PI / 180.0), 0.0,	0.0,
	//					     0.0,0.0,1.0,0.0,
	//					     0.0,0.0, 0.0,1.0 };  //Z����ת 
	
	
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClearDepth(1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //drawCoordinates();
  /* glMultMatrixf(rotMatrixx);
   glMultMatrixf(rotMatrixy);
   glMultMatrixf(rotMatrixz);*/
   glMultMatrixf(m);
   glMultMatrixf(translateMatrix);
   line();
   gluLookAt(0,0,1.0f,0,0,0,0,1,0);
   ObjLoader objModel = ObjLoader(f);
   objModel.type(dtype);
   objModel.Draw();
   setLightRes();
   //glRotatef(thetax, 1, 0, 0);
   //glRotatef(thetay, 0, 1, 0);
   //glRotatef(thetaz, 0, 0, 1);
   //glTranslatef(tx, ty, tz);

   //glColor3f(1, 0, 1); glutSolidCube(6);
   //glBegin(GL_TRIANGLES); 
	////1
	//  glColor3f( 1, 0, 0);glVertex3f( -4, 4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f(4, -4, 4);     
 //     glColor3f( 1, 0, 0);glVertex3f( 4, 4, 4); 
 //     
	//  glColor3f( 1, 0, 0);glVertex3f( 4, -4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f( -4, 4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f(-4, -4, 4);

	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, -4);

	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, -4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, 4);

	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, 4);

	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, 4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, -4);

   //2
   
	  /*glColor3f(1, 0, 0); glVertex3f(4, 0, 4);
	  glColor3f(1, 0, 0); glVertex3f(-4, 0, 4);
	  glColor3f(1, 0, 0); glVertex3f(-4, 0, -4);

	  glColor3f(1, 0, 0); glVertex3f(4, 0, 4);
	  glColor3f(1, 0, 0); glVertex3f(-4, 0, -4);
	  glColor3f(1, 0, 0); glVertex3f(4, 0, -4);

	  glColor3f( 1, 0, 0);glVertex3f( 0, 4, 0); 
      glColor3f( 1, 0, 0);glVertex3f(4, 0, -4);     
      glColor3f( 1, 0, 0);glVertex3f(-4, 0, -4); 

	  glColor3f(1, 1, 0); glVertex3f(0, 4, 0);
	  glColor3f(1, 1, 0); glVertex3f(4, 0, 4);
	  glColor3f(1, 1, 0); glVertex3f(4, 0, -4);

	  glColor3f(1, 0, 1); glVertex3f(0, 4, 0);
	  glColor3f(1, 0, 1); glVertex3f(-4, 0, 4);
	  glColor3f(1, 0, 1); glVertex3f(-4, 0, -4);

	  glColor3f(0, 1, 1); glVertex3f(0, 4, 0);
	  glColor3f(0, 1, 1); glVertex3f(4, 0, 4);
	  glColor3f(0, 1, 1); glVertex3f(-4, 0, 4);*/

	//3

	 
	  glEnd(); 
	  glFlush();
	  glutSwapBuffers();
}
void drawCoordinates()
{
	glLineWidth(3.0f);
	glColor3f(10.0f, 0.0f, 0.0f); 
	glBegin(GL_LINES);
	glVertex3f(0, 0.0f, 0.0f);
	glVertex3f(10, 0.0f, 0.0f);
	glEnd();
	glColor3f(0.0, 10.0, 0.0); 
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0, 0.0f);
	glVertex3f(0.0f, 10, 0.0f);
	glEnd();
	glColor3f(0.0, 0.0, 10.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.0f);
	glVertex3f(0, 0, 10.0f);
	glEnd();
}
void line()
{
	px = ((2 * posx / 400) - 1) * 10;
	py = (1 - (2 * posy / 400)) * 10;
	glLineWidth(3.0f);
	glColor3f(10.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0.0f, 0.0f);
	glVertex3f(px , py, 0.0f);
	glEnd();
}
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		posx = x;
		posy = y;
	}
}
int buildPopupMenu(void)
{
	int menu, submenu1, submenu2, submenu3, submenu4;

	submenu1 = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("Gourd", GOURD);
	glutAddMenuEntry("Lamp", LAMP);
	glutAddMenuEntry("Octahedron", OCTAHEDRON);
	glutAddMenuEntry("Teapot", TEAPOT); 
	submenu2 = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("Point", POINT);
	glutAddMenuEntry("Line", LINE);
	glutAddMenuEntry("Face", FACE);
	submenu3 = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("Single Color", SINGLE);
	glutAddMenuEntry("Random Colors", RANDOM);
	submenu4 = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("On", ON);
	glutAddMenuEntry("Off", OFF);

	menu = glutCreateMenu(selectFromMenu);
	glutAddSubMenu("Object", submenu1);
	glutAddSubMenu("Render Mode", submenu2);
	glutAddSubMenu("Color Mode", submenu3);
	glutAddSubMenu("Bounding Box", submenu4);


	return menu;
}
void selectFromMenu(int option)
{
	switch (option) {
	case GOURD:
		f = "D:/temp/class/ComputerGraphics/obj4/gourd.obj";
		//......
		break;
	case LAMP:
		f = "D:/temp/class/ComputerGraphics/obj4/lamp.obj";
		//....
		break;
	case OCTAHEDRON:
		f = "D:/temp/class/ComputerGraphics/obj4/octahedron.obj";
		//....
		break;
	case TEAPOT:
		f = "D:/temp/class/ComputerGraphics/obj4/teapot.obj";
		//....
		break;
	case POINT:
		dtype = 4;
		//....
		break;
	case LINE:
		dtype = 5;
		//......
		break;
	case FACE:
		dtype = 6;
		//....
		break;
	case SINGLE:
		sun_light_diffuse[0] = 1;
		sun_light_diffuse[1] = 1;
		sun_light_diffuse[2] = 1;
		//....
		break;
	case RANDOM:
		srand(time(0));
		random = rand() % 5;
		if (random == 0) {//��ɫ
			sun_light_diffuse[0] = 0;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 1;
		}
		else if (random == 1) {//��ɫ
			sun_light_diffuse[0] = 0;
			sun_light_diffuse[1] = 1;
			sun_light_diffuse[2] = 0;
		}
		else if (random == 2) {//��ɫ
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 0;
		}
		else if (random == 3) {//��ɫ
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 0;
			sun_light_diffuse[2] = 1;
		}
		else if (random == 4) {//��ɫ
			sun_light_diffuse[0] = 1;
			sun_light_diffuse[1] = 1;
			sun_light_diffuse[2] = 0;
		}
		//....
		break;
	case ON:
		//....
		break;
	case OFF:
		//....
		break;
	default:
		break;

	}
	glutPostRedisplay();
}

