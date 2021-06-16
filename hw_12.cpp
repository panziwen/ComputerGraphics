
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
using namespace std;

#define PROCESS_START 1
#define PROCESS_RESET 2


struct BoundingBox {
	int xMin = 0;
	int yMin = 0;
	int xMax = 0;
	int yMax = 0;
};

struct Point {
	int x = 0, y = 0;
	float r = 0.0f, g = 0.0f, b = 0.0f;
};

void buildPopupMenu();
void processMenu(int);
void changeSize(int, int);
void renderScene(void);
void mouse(int, int, int, int);
bool isContain(int, int);
void resetBoundingBox();
void findBoundingBox();
void midpoint(Point, Point);
void bottomLeftToUpRightIncreX(Point, Point, int, int);
void bottomLeftToUpRightIncreY(Point, Point, int, int);
void upLeftToBottomRightIncreX(Point, Point, int, int);
void upLeftToBottomRightMinusY(Point, Point, int, int);
void halfSpace();
void makeVertexClockWise();
float edgeFunction(Point, Point, Point);
void jordanCurveInside(int);
void crow(int);
void scanY(int, int);
void differenceX(Point&, Point&, Point&, Point&, int);
void differenceY(Point&, Point&, Point&, Point&, int);
void difference(Point&, Point&, Point&, Point&, float, float);
void scanX(Point&, Point&, int);
void increment(Point&, Point&);
void decrement(Point&, Point&);

int windowWidth = 600, windowHeight = 600;
int resolutionX = 25, resolutionY = 25;
int mouseX = 0, mouseY = 0;
std::vector<Point> vertexs;
std::vector<Point> linePoints;
std::vector<Point> fillPoints;
BoundingBox boundingBox;

int main(int argc, char** argv) {
	srand(time(NULL));
	resetBoundingBox();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("2D Grid");

	buildPopupMenu();
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

void buildPopupMenu() {
	int process = glutCreateMenu(processMenu);
	glutAddMenuEntry("Start", PROCESS_START);
	glutAddMenuEntry("Reset", PROCESS_RESET);

	glutCreateMenu(NULL);
	glutAddSubMenu("Process", process);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenu(int option) {
	int vertexsSize = vertexs.size();
	switch (option) {
	case PROCESS_START:
		if (vertexsSize >= 4) {
			//midpoint(vertexs[vertexsSize - 1].x, vertexs[vertexsSize - 1].y, vertexs[0].x, vertexs[0].y);
			midpoint(vertexs[vertexsSize - 1], vertexs[0]);
			for (int i = 1; i < vertexsSize; i++) {
				midpoint(vertexs[i - 1], vertexs[i]);
			}
			crow(vertexsSize);
		}
		break;
	case PROCESS_RESET:
		vertexs.clear();
		linePoints.clear();
		fillPoints.clear();
		resetBoundingBox();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void changeSize(int w, int h)
{
	std::cout << "Window Size= " << w << " X " << h << std::endl;
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(resolutionX * -1 / 2 - 0.5, resolutionX / 2 + 0.5, resolutionY * -1 / 2 - 0.5, resolutionY / 2 + 0.5, -20, 40);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 1.0f, 0, 0, 0, 0, 1, 0);

	glBegin(GL_QUADS);

	for (int i = 0; i < vertexs.size(); i++) {
		glColor3f(vertexs[i].r, vertexs[i].g, vertexs[i].b); glVertex2f(vertexs[i].x - 0.5, vertexs[i].y + 0.5); //top left 
		glColor3f(vertexs[i].r, vertexs[i].g, vertexs[i].b); glVertex2f(vertexs[i].x + 0.5, vertexs[i].y + 0.5); //top right
		glColor3f(vertexs[i].r, vertexs[i].g, vertexs[i].b); glVertex2f(vertexs[i].x + 0.5, vertexs[i].y - 0.5); //bottom right
		glColor3f(vertexs[i].r, vertexs[i].g, vertexs[i].b); glVertex2f(vertexs[i].x - 0.5, vertexs[i].y - 0.5); //bottom left
	}

	for (int i = 0; i < linePoints.size(); i++) {
		glColor3f(linePoints[i].r, linePoints[i].g, linePoints[i].b); glVertex2f(linePoints[i].x - 0.5, linePoints[i].y + 0.5); //top left 
		glColor3f(linePoints[i].r, linePoints[i].g, linePoints[i].b); glVertex2f(linePoints[i].x + 0.5, linePoints[i].y + 0.5); //top right
		glColor3f(linePoints[i].r, linePoints[i].g, linePoints[i].b); glVertex2f(linePoints[i].x + 0.5, linePoints[i].y - 0.5); //bottom right
		glColor3f(linePoints[i].r, linePoints[i].g, linePoints[i].b); glVertex2f(linePoints[i].x - 0.5, linePoints[i].y - 0.5); //bottom left
	}

	for (int i = 0; i < fillPoints.size(); i++) {
		glColor3f(fillPoints[i].r, fillPoints[i].g, fillPoints[i].b); glVertex2f(fillPoints[i].x - 0.5, fillPoints[i].y + 0.5); //top left 
		glColor3f(fillPoints[i].r, fillPoints[i].g, fillPoints[i].b); glVertex2f(fillPoints[i].x + 0.5, fillPoints[i].y + 0.5); //top right
		glColor3f(fillPoints[i].r, fillPoints[i].g, fillPoints[i].b); glVertex2f(fillPoints[i].x + 0.5, fillPoints[i].y - 0.5); //bottom right
		glColor3f(fillPoints[i].r, fillPoints[i].g, fillPoints[i].b); glVertex2f(fillPoints[i].x - 0.5, fillPoints[i].y - 0.5); //bottom left
	}

	glEnd();

	glBegin(GL_LINES);

	//column
	int lineDraw = resolutionX / 2;
	for (int i = 0; i < lineDraw; i++) {
		glColor3f(0, 0, 0); glVertex2f(i * -1 - 0.5, resolutionY * -1);
		glColor3f(0, 0, 0); glVertex2f(i * -1 - 0.5, resolutionY);

		glColor3f(0, 0, 0); glVertex2f(i + 0.5, resolutionY * -1);
		glColor3f(0, 0, 0); glVertex2f(i + 0.5, resolutionY);
	}

	//row
	lineDraw = resolutionY / 2;
	for (int i = 0; i < lineDraw; i++) {
		glColor3f(0, 0, 0); glVertex2f(resolutionX * -1, i * -1 - 0.5);
		glColor3f(0, 0, 0); glVertex2f(resolutionX, i * -1 - 0.5);

		glColor3f(0, 0, 0); glVertex2f(resolutionX * -1, i + 0.5);
		glColor3f(0, 0, 0); glVertex2f(resolutionX, i + 0.5);
	}
	glEnd();

	glutSwapBuffers();
}

void mouse(int state, int button, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseX = round((x - windowWidth / 2) / (float)(windowWidth / 2) * resolutionX / 2);
		mouseY = round((windowHeight / 2 - y) / (float)(windowHeight / 2) * resolutionY / 2);

		if (!isContain(mouseX, mouseY)) {
			vertexs.push_back({ mouseX, mouseY, rand() % 256 / 255.f, rand() % 256 / 255.f, rand() % 256 / 255.f });
		}
	}
}

bool isContain(int x, int y) {
	for (int i = 0; i < vertexs.size(); i++) {
		if (vertexs[i].x == x && vertexs[i].y == y) {
			return true;
		}
	}
	return false;
}

void resetBoundingBox() {
	boundingBox.xMin = resolutionX, boundingBox.xMax = -resolutionX;
	boundingBox.yMin = resolutionY, boundingBox.yMax = -resolutionY;
}

void findBoundingBox() {
	for (int i = 0; i < vertexs.size(); i++) {
		if (vertexs[i].x > boundingBox.xMax) {
			boundingBox.xMax = vertexs[i].x;
		}
		else if (vertexs[i].x < boundingBox.xMin) {
			boundingBox.xMin = vertexs[i].x;
		}

		if (vertexs[i].y > boundingBox.yMax) {
			boundingBox.yMax = vertexs[i].y;
		}
		else if (vertexs[i].y < boundingBox.yMin) {
			boundingBox.yMin = vertexs[i].y;
		}
	}
}

void midpoint(Point v1, Point v2) {

	if (v1.y <= v2.y) {
		int dy = v2.y - v1.y;

		if (v1.x < v2.x) {
			int dx = v2.x - v1.x;

			if (dy <= dx) {
				bottomLeftToUpRightIncreX(v1, v2, dx, dy);
			}
			else {
				bottomLeftToUpRightIncreX(v1, v2, dx, dy);
			}
		}
		else {
			int dx = v1.x - v2.x;

			if (dy <= dx) {
				upLeftToBottomRightIncreX(v2, v1, dx, dy);
			}
			else {
				upLeftToBottomRightMinusY(v2, v1, dx, dy);
			}
		}
	}
	else { // y1 > y2
		int dy = v1.y - v2.y;

		if (v1.x > v2.x) {
			int dx = v1.x - v2.x;

			if (dy <= dx) {
				bottomLeftToUpRightIncreX(v2, v1, dx, dy);
			}
			else {
				bottomLeftToUpRightIncreX(v2, v1, dx, dy);
			}
		}
		else {
			int dx = v2.x - v1.x;

			if (dy <= dx) {
				upLeftToBottomRightIncreX(v1, v2, dx, dy);
			}
			else {
				upLeftToBottomRightMinusY(v1, v2, dx, dy);
			}
		}
	}
}

void bottomLeftToUpRightIncreX(Point start, Point end, int dx, int dy) {
	int d = dy - dx / 2;
	int x = start.x + 1, y = start.y;
	Point s, ds;

	differenceX(start, end, s, ds, x);

	for (; x < end.x; x++) {
		if (d < 0) {
			d += dy;
		}
		else {
			d += dy - dx;
			y++;
		}
		linePoints.push_back({ x, y, s.r, s.g, s.b });
		increment(s, ds);
	}
}

void bottomLeftToUpRightIncreY(Point start, Point end, int dx, int dy) {
	int d = dx - dy / 2;
	int x = start.x, y = start.y + 1;
	Point s, ds;

	differenceY(start, end, s, ds, y);

	for (; y < end.y; y++) {
		if (d < 0) {
			d += dx;
		}
		else {
			d += dx - dy;
			x++;
		}
		linePoints.push_back({ x, y, s.r, s.g, s.b });
		increment(s, ds);
	}
}

void upLeftToBottomRightIncreX(Point start, Point end, int dx, int dy) {
	int d = dy - dx / 2;
	int x = start.x + 1, y = start.y;
	Point s, ds;

	differenceX(start, end, s, ds, x);

	for (; x < end.x; x++) {
		if (d < 0) {
			d += dy;
		}
		else {
			d += dy - dx;
			y--;
		}
		linePoints.push_back({ x, y, s.r, s.g, s.b });
		increment(s, ds);
	}
}

void upLeftToBottomRightMinusY(Point start, Point end, int dx, int dy) {
	int d = dx - dy / 2;
	int x = start.x, y = start.y - 1;

	Point s, ds;

	differenceY(end, start, s, ds, y);

	for (; y > end.y; y--) {
		if (d < 0) {
			d += dx;
		}
		else {
			d += dx - dy;
			x++;
		}
		linePoints.push_back({ x, y, s.r, s.g, s.b });
		decrement(s, ds);
	}
}

void halfSpace() {

	Point bottomLeftBound = { boundingBox.xMin, boundingBox.yMin };
	float e1 = edgeFunction(bottomLeftBound, vertexs[0], vertexs[1]);
	float e2 = edgeFunction(bottomLeftBound, vertexs[1], vertexs[2]);
	float e3 = edgeFunction(bottomLeftBound, vertexs[2], vertexs[0]);
	int xDim = boundingBox.xMax - boundingBox.xMin + 1;

	//dy
	int a1 = vertexs[0].y - vertexs[1].y;
	int a2 = vertexs[1].y - vertexs[2].y;
	int a3 = vertexs[2].y - vertexs[0].y;

	//-dx
	int b1 = vertexs[1].x - vertexs[0].x;
	int b2 = vertexs[2].x - vertexs[1].x;
	int b3 = vertexs[0].x - vertexs[2].x;

	for (int y = boundingBox.yMin; y <= boundingBox.yMax; y++) {
		for (int x = boundingBox.xMin; x <= boundingBox.xMax; x++) {
			if (e1 < 0 && e2 < 0 && e3 < 0) {
				fillPoints.push_back({ x, y });
			}
			e1 += a1; e2 += a2; e3 += a3;
		}
		e1 += -xDim * a1 + b1; e2 += -xDim * a2 + b2; e3 += -xDim * a3 + b3;
	}
}

void makeVertexClockWise() {

	float d = edgeFunction(vertexs[2], vertexs[0], vertexs[1]);
	if (d > 0) {
		Point temp = vertexs[2];
		vertexs[2] = vertexs[1];
		vertexs[1] = temp;
	}
}

float edgeFunction(Point p, Point v1, Point v2) {
	return (v1.y - v2.y) * p.x + (v2.x - v1.x) * p.y + (v1.x * v2.y - v1.y * v2.x);
}

void jordanCurveInside(int vertexsSize) {
	int cross;
	int x0, y0, x1, y1;
	for (int row = boundingBox.yMin; row <= boundingBox.yMax; row++) {
		for (int col = boundingBox.xMin; col <= boundingBox.xMax; col++) {
			cross = 0;
			x0 = vertexs[vertexsSize - 1].x - col;
			y0 = vertexs[vertexsSize - 1].y - row;
			for (int i = 0; i < vertexsSize; i++) {
				x1 = vertexs[i].x - col;
				y1 = vertexs[i].y - row;

				if (y0 > 0 && y1 <= 0) {
					if (x1 * y0 > x0 * y1) {
						cross--;
					}
				}
				else if (y0 <= 0 && y1 > 0) {
					if (x0 * y1 > x1 * y0) {
						cross++;
					}
				}
				x0 = x1, y0 = y1;
			}
			if (cross != 0) {
				fillPoints.push_back({ col, row });
			}
		}
	}
}

void crow(int vertexsSize) {
	int iMin = 0;
	for (int i = 1; i < vertexsSize; i++) {
		if (vertexs[i].y < vertexs[iMin].y) {
			iMin = i;
		}
	}
	scanY(vertexsSize, iMin);
}

void scanY(int vertexsSize, int iMin) {
	int li, ri;
	int ly, ry;
	Point l, dl;
	Point r, dr;
	int rem;
	int y;

	li = ri = iMin;
	ly = ry = y = ceil(vertexs[iMin].y);

	for (rem = vertexsSize; rem > 0;) {
		while (ly <= y && rem > 0) {
			rem--;
			iMin = li - 1;
			if (iMin < 0) {
				iMin = vertexsSize - 1;
			}

			ly = ceil(vertexs[iMin].y);

			if (ly > y) {
				differenceY(vertexs[li], vertexs[iMin], l, dl, y);
			}

			li = iMin;
		}

		while (ry <= y && rem > 0) {
			rem--;
			iMin = ri + 1;
			if (iMin >= vertexsSize) {
				iMin = 0;
			}

			ry = ceil(vertexs[iMin].y);

			if (ry > y) {
				differenceY(vertexs[ri], vertexs[iMin], r, dr, y);
			}

			ri = iMin;
		}

		for (; y < ly && y < ry; y++) {
			scanX(l, r, y);
			increment(l, dl);
			increment(r, dr);
		}
	}
}

void differenceX(Point& v1, Point& v2, Point& e, Point& de, int x) {
	difference(v1, v2, e, de, (v2.x - v1.x), x - v1.x);
}

void differenceY(Point& v1, Point& v2, Point& e, Point& de, int y) {
	difference(v1, v2, e, de, (v2.y - v1.y), y - v1.y);
}

void difference(Point& v1, Point& v2, Point& e, Point& de, float d, float f) {
	de.x = (v2.x - v1.x) / d;
	e.x = v1.x + f * de.x;
	de.r = (v2.r - v1.r) / d;
	e.r = v1.r + f * de.r;
	de.g = (v2.g - v1.g) / d;
	e.g = v1.g + f * de.g;
	de.b = (v2.b - v1.b) / d;
	e.b = v1.b + f * de.b;
}

void scanX(Point& l, Point& r, int y) {
	int x, lx, rx;
	Point s, ds;

	lx = ceil(l.x);
	rx = ceil(r.x);
	if (lx < rx) {
		differenceX(l, r, s, ds, lx);
		for (x = lx + 1; x < rx; x++) {
			fillPoints.push_back({ x, y, s.r, s.g, s.b });
			increment(s, ds);
		}
	}
}

void increment(Point& edge, Point& delta) {
	edge.x += delta.x;
	edge.r += delta.r;
	edge.g += delta.g;
	edge.b += delta.b;
}

void decrement(Point& edge, Point& delta) {
	edge.x -= delta.x;
	edge.r -= delta.r;
	edge.g -= delta.g;
	edge.b -= delta.b;
}