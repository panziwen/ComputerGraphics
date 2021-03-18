#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <freeglut.h>
#include <iostream>
 
void ChangeSize(int , int );					 
void RenderScene(void);		
void buildPopupMenu();
void myKeyboard(unsigned char, int, int);
void mySpaceialKey(int, int, int);
double tx, tz, ty;
double thetax, thetaz, thetay;
int main(int argc, char** argv) 
{ 
	tx = 0;
	ty = 0;
	tz = 0;
	thetax = 0;
	thetaz = 0; 
	thetay = 0;
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
   glutInitWindowSize(400,400);				 
   glutInitWindowPosition(600,80);
   //glutCreateWindow("Simple Rectangle");
   glutCreateWindow("Moving Cube");
   //SetupRC();
   buildPopupMenu();
   glutReshapeFunc(ChangeSize); 
   glutDisplayFunc(RenderScene); 
   glutKeyboardFunc(myKeyboard);
   glutSpecialFunc(mySpaceialKey);
   glutMainLoop();	
   return 0; 
} 
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		thetax -= 3;
		break;
	case 'd':
		thetax += 3;
		break;
	case 'w':
		thetay += 3;
		break;
	case 's':
		thetay -= 3;
		break;
	case 'z':
		thetaz += 3;
		break;
	case 'x':
		thetaz -= 3;
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
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 

   glRotatef(thetax, 1, 0, 0);
   glRotatef(thetay, 0, 1, 0);
   glRotatef(thetaz, 0, 0, 1);


   gluLookAt(0,0,1.0f,0,0,0,0,1,0);

   glTranslatef(tx, ty, tz);

   glBegin(GL_TRIANGLES); 
	////1
	//  glColor3f( 1, 0, 0);glVertex3f( -4, 4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f(4, -4, 4);     
 //     glColor3f( 1, 0, 0);glVertex3f( 4, 4, 4); 
 //     
	//  glColor3f( 1, 0, 0);glVertex3f( 4, -4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f( -4, 4, 4); 
 //     glColor3f( 1, 0, 0);glVertex3f(-4, -4, 4);

	////2
	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, -4);

	//  glColor3f(0, 1, 0); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, -4);
	//  glColor3f(0, 1, 0); glVertex3f(4, 4, 4);

	//  //3
	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, 4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, 4);

	//  glColor3f(0, 0, 1); glVertex3f(-4, 4, -4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, 4);
	//  glColor3f(0, 0, 1); glVertex3f(-4, -4, -4);

   //1
   
	  glColor3f(1, 0, 0); glVertex3f(4, 0, 4);
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
	  glColor3f(0, 1, 1); glVertex3f(-4, 0, 4);





	//2
	 
	  glEnd();
	  glutSwapBuffers();
}