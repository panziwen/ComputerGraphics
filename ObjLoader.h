#include <iostream>
#include <string>
#include <freeglut.h>
#include <vector>
using namespace std;
class ObjLoader {
public:
	ObjLoader(string filename);//���캯��
	void type(int x);
	void Draw();//���ƺ���
private:
	int x;
	vector<vector<GLfloat>>vSets;//��Ŷ���(x,y,z)����
	vector<vector<GLint>>fSets;//������������������
};