#include <iostream>
#include <string>
#include <freeglut.h>
#include <vector>
using namespace std;
class ObjLoader {
public:
	ObjLoader(string filename);//构造函数
	void type(int x);
	void Draw();//绘制函数
private:
	int x;
	vector<vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
	vector<vector<GLint>>fSets;//存放面的三个顶点索引
};