/***C/C++  http://bbs.csdn.net/topics/100091584***/
#include <stdio.h> 
#include <stdlib.h>
/***freeglut***/
#include <glut.h>
#include <math.h>
void ChangeSize(int, int);
void RenderScene(void);
void drawcenterpoint();
void lockstate(int);
void buildPopupMenu();
void objectmenu(int);
void selectmenu(int);
void myMouse(int, int, int, int);
void drawtrangle();
void getBoundPoints();
void fillTrangle(float e1, float e2, float e3, float m1, float m2, float m3);
void fillTrangle2(float e1, float e2, float e3, float m1, float m2, float m3);
void drawpoint(int, int);
float myx = 0;
int num;
float memx, memy, xp, yp;
int mmx, mmy;
int mmxmm[85], mmymm[85];
int varnum;
int click;
float dr, dg, db;
int x1, x2, y11, y2, x3, y3, xmin, xmax, ymin, ymax;
int lock = 0;
int point = 0;
int line = 1;
int trangle = 2;
int kstate;
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(600, 80);
	glutCreateWindow("DDA");

	buildPopupMenu();

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(myMouse);

	glutMainLoop();
	return 0;
}

void myMouse(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			xp = x - memx / 2;
			xp = (num * xp) / memx;
			if (xp > 0)
				mmx = xp + 0.5;
			else
				mmx = xp - 0.5;
			yp = memy / 2 - y;
			yp = (yp * num) / memy;
			if (yp > 0)
				mmy = yp + 0.5;
			else
				mmy = yp - 0.5;
			dr = 1;
			dg = 0;
			db = 0;
			lockstate(kstate);
			mmxmm[click] = mmx;
			mmymm[click] = mmy;
			click = click + 1;
		}
		break;
	default:
		break;
	}
}

void buildPopupMenu()
{
	int menu = glutCreateMenu(objectmenu);
	glutAddMenuEntry("9x9", 1);
	glutAddMenuEntry("25x25", 2);
	glutAddMenuEntry("85x85", 3);
	glutAddMenuEntry("Clean", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 19125, 0, 19125, 10, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(4.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	memx = w;
	memy = h;
	buildPopupMenu();
}

void objectmenu(int option)
{
	switch (option) {
	case 1:
		printf("9x9\n");
		myx = 19125 / 9;
		num = 9;
		varnum = 4;
		break;
	case 2:
		printf("25x25\n");
		myx = 19125 / 25;
		num = 25;
		varnum = 12;
		break;
	case 3:
		printf("85x85\n");
		myx = 19125 / 85;
		num = 85;
		varnum = 42;
		break; 
	case 4:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	default:
		break;
	}
	lock = 0;
	click = 0;
	glutPostRedisplay();
}

void selectmenu(int option)
{
	switch (option) {
	default:
		break;
	}
}

void RenderScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	for (int i = 1; i < num; i++) {
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(0, myx*i, 0);
		glVertex3f(19125, myx*i, 0);
		glVertex3f(myx*i, 0, 0);
		glVertex3f(myx*i, 19125, 0);
		glEnd();
	}

	drawtrangle();

	glutSwapBuffers();
}
void drawtrangle()
{
	kstate = trangle;
	if (click == 3)
	{
		for (int i = 0; i < click; i++) {
			drawpoint(mmxmm[i], mmymm[i]);
		}
	}
	else if (lock == 1)
	{
		drawpoint(mmxmm[0], mmymm[0]);
	}
	else if (lock != 0)
	{
		for (int i = 0; i < click; i++) {
			drawpoint(mmxmm[i], mmymm[i]);
		}
	}

	if (click == 1) {
		x1 = mmx;
		y11 = mmy;
	}
	else if (click == 2) {
		x2 = mmx;
		y2 = mmy;
	}
	else if (click == 3) {
		x3 = mmx;
		y3 = mmy;
	}
	else if (click > 3)
	{
		x3 = mmx;
		y3 = mmy;
	}

	float dx1 = x2 - x1;
	float dy1 = y2 - y11;
	float m1 = dy1 / dx1;
	float xo1 = x1, yo1 = y11;
	float b1 = y11 - m1 * x1;

	float dx2 = x3 - x2;
	float dy2 = y3 - y2;
	float m2 = dy2 / dx2;
	float xo2 = x2, yo2 = y2;
	float b2 = y2 - m2 * x2;

	float dx3 = x1 - x3;
	float dy3 = y11 - y3;
	float m3 = dy3 / dx3;
	float xo3 = x3, yo3 = y3;
	float b3 = y3 - m3 * x3;

	getBoundPoints();
	if (lock == 3) {
		fillTrangle(m1, m2, m3, b1, b2, b3);
	}
	if (lock >= 3) {
		fillTrangle2(m1, m2, m3, b1, b2, b3);
	}

	if (lock >= 3) {
		if ((m1 < 1) && (-1 < m1) && (x1 < x2)) {
			for (int i = 0; i < dx1; i++) {
				yo1 = y11 + m1 * i;
				yo1 = (int)yo1;
				drawpoint(xo1 + i, yo1);
			}
		}
		else if ((m1 < 1) && (-1 < m1) && (x1 > x2)) {
			dx1 = -dx1;
			for (int i = 0; i < dx1; i++) {
				yo1 = y11 - m1 * i;
				yo1 = (int)yo1;
				drawpoint(xo1 - i, yo1);
			}
		}
		else if (((m1 > 1) || (-1 > m1)) && (y11 < y2)) {
			m1 = dx1 / dy1;
			for (int i = 0; i < dy1; i++) {
				xo1 = x1 + m1 * i;
				xo1 = (int)xo1;
				drawpoint(xo1, yo1 + i);
			}
		}
		else if (((m1 > 1) || (-1 > m1)) && (y2 < y11)) {
			dy1 = -dy1;
			m1 = -dx1 / dy1;
			for (int i = 0; i < dy1; i++) {
				xo1 = x1 - m1 * i;
				xo1 = (int)xo1;
				drawpoint(xo1, yo1 - i);
			}
		}
		else if ((m1 == 1 || m1 == -1) && x1 < x2) {
			for (int i = 0; i < dx1; i++) {
				yo1 = y11 + m1 * i;
				yo1 = (int)yo1;
				drawpoint(xo1 + i, yo1);
			}
		}
		else if ((m1 == 1 || m1 == -1) && x2 < x1) {
			dx1 = x1 - x2;
			for (int i = 0; i < dx1; i++) {
				yo1 = y11 - m1 * i;
				yo1 = (int)yo1;
				drawpoint(xo1 - i, yo1);
			}
		}
	}

	if (lock >= 3) {
		if ((m2 < 1) && (-1 < m2) && (x2 < x3)) {
			for (int i = 0; i < dx2; i++) {
				yo2 = y2 + m2 * i;
				yo2 = (int)yo2;
				drawpoint(xo2 + i, yo2);
			}
		}
		else if ((m2 < 1) && (-1 < m2) && (x2 > x3)) {
			dx2 = -dx2;
			for (int i = 0; i < dx2; i++) {
				yo2 = y2 - m2 * i;
				yo2 = (int)yo2;
				drawpoint(xo2 - i, yo2);
			}
		}
		else if (((m2 > 1) || (-1 > m2)) && (y2 < y3)) {
			m2 = dx2 / dy2;
			for (int i = 0; i < dy2; i++) {
				xo2 = x2 + m2 * i;
				xo2 = (int)xo2;
				drawpoint(xo2, yo2 + i);
			}
		}
		else if (((m2 > 1) || (-1 > m2)) && (y3 < y2)) {
			dy2 = -dy2;
			m2 = -dx2 / dy2;
			for (int i = 0; i < dy2; i++) {
				xo2 = x2 - m2 * i;
				xo2 = (int)xo2;
				drawpoint(xo2, yo2 - i);
			}
		}
		else if ((m2 == 1 || m2 == -1) && x2 < x3) {
			for (int i = 0; i < dx2; i++) {
				yo2 = y2 + m2 * i;
				yo2 = (int)yo2;
				drawpoint(xo2 + i, yo2);
			}
		}
		else if ((m2 == 1 || m2 == -1) && x3 < x2) {
			dx2 = x2 - x3;
			for (int i = 0; i < dx2; i++) {
				yo2 = y2 - m2 * i;
				yo2 = (int)yo2;
				drawpoint(xo2 - i, yo2);
			}
		}
	}

	if (lock >= 3) {
		if ((m3 < 1) && (-1 < m3) && (x3 < x1)) {
			for (int i = 0; i < dx3; i++) {
				yo3 = y3 + m3 * i;
				yo3 = (int)yo3;
				drawpoint(xo3 + i, yo3);
			}
		}
		else if ((m3 < 1) && (-1 < m3) && (x3 > x1)) {
			dx3 = -dx3;
			for (int i = 0; i < dx3; i++) {
				yo3 = y3 - m3 * i;
				yo3 = (int)yo3;
				drawpoint(xo3 - i, yo3);
			}
		}
		else if (((m3 > 1) || (-1 > m3)) && (y3 < y11)) {
			m3 = dx3 / dy3;
			for (int i = 0; i < dy3; i++) {
				xo3 = x3 + m3 * i;
				xo3 = (int)xo3;
				drawpoint(xo3, yo3 + i);
			}
		}
		else if (((m3 > 1) || (-1 > m3)) && (y11 < y3)) {
			dy3 = -dy3;
			m3 = -dx3 / dy3;
			for (int i = 0; i < dy3; i++) {
				xo3 = x3 - m3 * i;
				xo3 = (int)xo3;
				drawpoint(xo3, yo3 - i);
			}
		}
		else if ((m3 == 1 || m3 == -1) && x3 < x1) {
			for (int i = 0; i < dx3; i++) {
				yo3 = y3 + m3 * i;
				yo3 = (int)yo3;
				drawpoint(xo3 + i, yo3);
			}
		}
		else if ((m3 == 1 || m3 == -1) && x1 < x3) {
			dx3 = x3 - x1;
			for (int i = 0; i < dx3; i++) {
				yo3 = y3 - m3 * i;
				yo3 = (int)yo3;
				drawpoint(xo3 - i, yo3);
			}
		}
	}

}
void getBoundPoints()
{
	if (x1 > x2) {
		if (x1 > x3)
			xmax = x1;
		else
			xmax = x3;
	}
	else {
		if (x2 > x3)
			xmax = x2;
		else
			xmax = x3;
	}

	if (x1 < x2) {
		if (x1 < x3)
			xmin = x1;
		else
			xmin = x3;
	}
	else {
		if (x2 < x3)
			xmin = x2;
		else
			xmin = x3;
	}

	if (y11 > y2) {
		if (y11 > y3)
			ymax = y11;
		else
			ymax = y3;
	}
	else {
		if (y2 > y3)
			ymax = y2;
		else
			ymax = y3;
	}

	if (y11 < y2) {
		if (y11 < y3)
			ymin = y11;
		else
			ymin = y3;
	}
	else {
		if (y2 < y3)
			ymin = y2;
		else
			ymin = y3;
	}

}
void fillTrangle(float m1, float m2, float m3, float b1, float b2, float b3) {
	getBoundPoints();
	float e1 = m1 * xmin - ymin + b1;
	float e2 = m2 * xmin - ymin + b2;
	float e3 = m3 * xmin - ymin + b3;
	int xDim = xmax - xmin;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			e1 = m1 * x - y + b1;
			e2 = m2 * x - y + b2;
			e3 = m3 * x - y + b3;
			if (x1 < x2) {
				if (x2 < x3) {
					if (e1 > 0 && e2 > 0 && e3 < 0 || e1 < 0 && e2 < 0 && e3 > 0)
						drawpoint(x, y);
				}
				else {
					if (x1 > x3) {
						if (e1 > 0 && e2 < 0 && e3 > 0 || e1 < 0 && e2 > 0 && e3 < 0)
							drawpoint(x, y);
					}
					else {
						if (e1 > 0 && e2 < 0 && e3 < 0 || e1 < 0 && e2 > 0 && e3 > 0)
							drawpoint(x, y);
					}
				}
			}
			else {
				if (x2 > x3) {
					if (e1 > 0 && e2 > 0 && e3 < 0 || e1 < 0 && e2 < 0 && e3 > 0)
						drawpoint(x, y);
				}
				else {
					if (x1 < x3) {
						if (e1 < 0 && e2 > 0 && e3 < 0 || e1 > 0 && e2 < 0 && e3 > 0)
							drawpoint(x, y);
					}
					else {
						if (e1 < 0 && e2 > 0 && e3 > 0 || e1 > 0 && e2 < 0 && e3 < 0)
							drawpoint(x, y);
					}
				}
			}
			if (x1 == x2) {
				if (e2 > 0 && e3 < 0 || e2 < 0 && e3 > 0) {
					drawpoint(x, y);
				}
			}
			else if (x2 == x3) {
				if (e1 > 0 && e3 < 0 || e1 < 0 && e3 > 0) {
					drawpoint(x, y);
				}
			}
			else if (x1 == x3) {
				if (e2 > 0 && e1 < 0 || e2 < 0 && e1 > 0) {
					drawpoint(x, y);
				}
			}
		}
	}
}
void fillTrangle2(float m1, float m2, float m3, float b1, float b2, float b3) {
	getBoundPoints();
	float e1 = m1 * xmin - ymin + b1;
	float e2 = m2 * xmin - ymin + b2;
	float e3 = m3 * xmin - ymin + b3;
	int xDim = xmax - xmin;
	for (int y = ymin; y <= ymax; y++) {
		for (int x = xmin; x <= xmax; x++) {
			e1 = m1 * x - y + b1;
			e2 = m2 * x - y + b2;
			e3 = m3 * x - y + b3;
			if (x1 < x2) {
				if (x2 < x3) {
					if (e1 > 0 && e2 > 0 && e3 < 0 || e1 < 0 && e2 < 0 && e3 > 0)
						drawpoint(x, y);
				}
				else {
					if (x1 > x3) {
						if (e1 > 0 && e2 < 0 && e3 > 0 || e1 < 0 && e2 > 0 && e3 < 0)
							drawpoint(x, y);
					}
					else {
						if (e1 > 0 && e2 < 0 && e3 < 0 || e1 < 0 && e2 > 0 && e3 > 0)
							drawpoint(x, y);
					}
				}
			}
			else {
				if (x2 > x3) {
					if (e1 > 0 && e2 > 0 && e3 < 0 || e1 < 0 && e2 < 0 && e3 > 0)
						drawpoint(x, y);
				}
				else {
					if (x1 < x3) {
						if (e1 < 0 && e2 > 0 && e3 < 0 || e1 > 0 && e2 < 0 && e3 > 0)
							drawpoint(x, y);
					}
					else {
						if (e1 < 0 && e2 > 0 && e3 > 0 || e1 > 0 && e2 < 0 && e3 < 0)
							drawpoint(x, y);
					}
				}
			}
			if (x1 == x2) {
				if (e2 > 0 && e3 < 0 || e2 < 0 && e3 > 0) {
					drawpoint(x, y);
				}
			}
			else if (x2 == x3) {
				if (e1 > 0 && e3 < 0 || e1 < 0 && e3 > 0) {
					drawpoint(x, y);
				}
			}
			else if (x1 == x3) {
				if (e2 > 0 && e1 < 0 || e2 < 0 && e1 > 0) {
					drawpoint(x, y);
				}
			}
		}
	}
}
void drawpoint(int a, int b) {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(myx * (a + varnum) + 1, myx * (b + varnum) + 1, 0);
	glVertex3f(myx * (a + varnum + 1) - 1, myx * (b + varnum) + 1, 0);
	glVertex3f(myx * (a + varnum + 1) - 1, myx * (b + varnum + 1) - 1, 0);
	glVertex3f(myx * (a + varnum) + 1, myx * (b + varnum + 1) - 1, 0);
	glEnd();
}
void drawcenterpoint() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(myx * (num / 2), myx * (num / 2), 0);
	glVertex3f(myx * ((num / 2) + 1), myx * (num / 2), 0);
	glVertex3f(myx * ((num / 2) + 1), myx * ((num / 2) + 1), 0);
	glVertex3f(myx * (num / 2), myx * ((num / 2) + 1), 0);
	glEnd();
}
void lockstate(int state)
{
	switch (state)
	{
	case 1:
		if (lock != 2) {
			lock++;
		}
		break;
	case 2:
		lock++;
		if (click == 3) {
			click = 0;
		}
		break;
	default:
		break;
	}
}