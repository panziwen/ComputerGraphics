#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <freeglut.h>
#include <time.h>
#include <iostream>
using namespace std;
string f;
#define PI 3.14159265
#define SIZE1 0
#define SIZE2 1
#define SIZE3 2
int websize = 9;
int cont = 0;
float lx1, ly1, lx2, ly2;
void ChangeSize(int , int );					 
void RenderScene(void);		
void selectFromMenu(int);
int buildPopupMenu(void);
void myKeyboard(unsigned char, int, int);
void mySpaceialKey(int, int, int);
void myMouse(int, int, int x, int y);
void drawCoordinates();
void line();
int main(int argc, char** argv) 
{
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
   glutInitWindowSize(800,800);				 
   glutInitWindowPosition(600,80);
   //glutCreateWindow("Simple Rectangle");
   glutCreateWindow("Moving Cube");
   //SetupRC();
   glutReshapeFunc(ChangeSize);
   glutKeyboardFunc(myKeyboard);
   glutSpecialFunc(mySpaceialKey);
   glutMouseFunc(myMouse);
   glutDisplayFunc(RenderScene);
   buildPopupMenu();
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutMainLoop();	
   return 0; 
} 
void myKeyboard(unsigned char key, int x, int y)
{
	
}
void mySpaceialKey(int key, int x, int y)
{
	
}



void ChangeSize(int w, int h) 
{ 
   printf("Window Size= %d X %d\n",w,h); 
} 
void RenderScene(void) 
{

	int i;
	int k = websize / 2;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, websize, 0, websize); //´°¿Ú×ø±ê·¶Î§
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//»­websize*websizeÍø¸ñ
	for (i = 0; i <= websize; i++) 
	{
		glBegin(GL_LINES);
		glVertex2d(0, i * 1.0);
		glVertex2d(websize, i * 1.0);
		glEnd();
	}
	glBegin(GL_LINES); 
	for (i = 0; i <= websize; i++)
	{
		glVertex2d(i * 1.0, 0.0);
		glVertex2d(i * 1.0, websize);
	}
	if (lx1!=0&&ly1!=0&&lx2!=0&&ly2!=0)
	{
		drawCoordinates();
	}
	glEnd();
	glFlush();
	/*int k = websize / 2;
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1); glVertex2d(k, k);
	glColor3f(1, 1, 1); glVertex2d(k, k + 1);
	glColor3f(1, 1, 1); glVertex2d(k + 1, k + 1);
	glColor3f(1, 1, 1); glVertex2d(k, k);
	glColor3f(1, 1, 1); glVertex2d(k + 1, k + 1);
	glColor3f(1, 1, 1); glVertex2d(k + 1, k);*/
	glEnd();
	glFlush();

	
	glLoadIdentity();
}
void drawCoordinates()
{
	glColor3f(1, 1, 1); 
	glBegin(GL_LINES);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2, ly2);
	glEnd();
}
void line()
{
	
}
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		int setx, sety;
		//´°¿Ú×ø±ê·¶Î§
		if (cont == 2)
		{
			cont = 0;
			lx1 = lx2 = ly1 = ly2 = 0;
			glClear(GL_COLOR_BUFFER_BIT);
		}
		setx = x / (800.0/websize );
		sety = (800 - y) / (800.0/ websize);
		if (cont == 0)
		{
			lx1 = (2 * setx + 1) / 2.0;
			ly1 = (2 * sety + 1) / 2.0;
		}
		if (cont == 1)
		{
			lx2 = (2 * setx + 1) / 2.0;
			ly2 = (2 * sety + 1) / 2.0;
		}
		printf("(%d, %d)\n", int(setx)-4, int(sety)-4);
		glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 1); glVertex2d(int(setx), int(sety));
		glColor3f(1, 1, 1); glVertex2d(int(setx), int(sety) + 1);
		glColor3f(1, 1, 1); glVertex2d(int(setx) + 1, int(sety) + 1);
		glColor3f(1, 1, 1); glVertex2d(int(setx), int(sety));
		glColor3f(1, 1, 1); glVertex2d(int(setx) + 1, int(sety) + 1);
		glColor3f(1, 1, 1); glVertex2d(int(setx) + 1, int(sety));
		cont += 1;
	}
}
int buildPopupMenu(void)
{
	int menu;

	menu = glutCreateMenu(selectFromMenu);
	glutAddMenuEntry("9*9", SIZE1);
	glutAddMenuEntry("25*25", SIZE2);
	glutAddMenuEntry("45*45", SIZE3);


	return menu;
}
void selectFromMenu(int option)
{
	switch (option) {
	case SIZE1:
		websize = 9;
		cont = 0;
		lx1 = lx2 = ly1 = ly2 = 0;
		//......
		break;
	case SIZE2:
		websize = 25;
		cont = 0;
		lx1 = lx2 = ly1 = ly2 = 0;
		//....
		break;
	case SIZE3:
		websize = 45;
		cont = 0;
		lx1 = lx2 = ly1 = ly2 = 0;
		//....
		break;
	default:
		break;

	}
	glutPostRedisplay();
}

