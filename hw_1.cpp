#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <freeglut.h>
#include <iostream>

#define PI 3.14159265
double degreex = 0, degreey = 0, degreez = 0;
void ChangeSize(int , int );					 
void RenderScene(void);		
void buildPopupMenu();
void myKeyboard(unsigned char, int, int);
void mySpaceialKey(int, int, int);
void myMouse(int, int, int x, int y);
void drawCoordinates();
void line();
float tx, tz, ty;
float x=0, y=0, z=0;
float posx, posy;
int px, py;
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

void buildPopupMenu()
{
	int menu_id;
	menu_id = glutCreateMenu(menuSelect);
    glutAddMenuEntry("Flat",0);
    glutAddMenuEntry("Smooth",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

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
	//						 0.0,0.0, 0.0,1.0 };//XÖáÐý×ª 

	//GLfloat rotMatrixy[] = { 1.0, 0.0, 0.0,0.0,
	//					 0.0,cos(degreex * PI / 180.0), -sin(degreex * PI / 180.0),0.0,
	//					 0.0,sin(degreex * PI / 180.0), cos(degreex * PI / 180.0),0.0,
	//					 0.0,0.0, 0.0,1.0 };//YÖáÐý×ª 

	//GLfloat rotMatrixz[] = { cos(degreez * PI / 180.0), -sin(degreez * PI / 180.0), 0.0,0.0,
	//					     sin(degreez * PI / 180.0),cos(degreez * PI / 180.0), 0.0,	0.0,
	//					     0.0,0.0,1.0,0.0,
	//					     0.0,0.0, 0.0,1.0 };  //ZÖáÐý×ª 
	
	
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClearDepth(1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   line();
   drawCoordinates();
   line();
  /* glMultMatrixf(rotMatrixx);
   glMultMatrixf(rotMatrixy);
   glMultMatrixf(rotMatrixz);*/
   glMultMatrixf(m);

   glMultMatrixf(translateMatrix);
   gluLookAt(0,0,1.0f,0,0,0,0,1,0);

   //glRotatef(thetax, 1, 0, 0);
   //glRotatef(thetay, 0, 1, 0);
   //glRotatef(thetaz, 0, 0, 1);
   //glTranslatef(tx, ty, tz);

   glColor3f(1, 0, 1); glutSolidCube(6);
   glBegin(GL_TRIANGLES); 
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

