#pragma once
#include <vector>
using namespace std;
struct Point{
	float x,y,z;
	Point();
	Point(float x,float y):x(x),y(y),z(0.0f){}
	Point(float x,float y,float z):x(x),y(y),z(z){}
};
class MyName
{
public:
	MyName(void);
	~MyName(void);

	void pointJi();
	void pointXiao();
	void pointYa();

	void pointJiAll();
	void pointXiaoAll();
	void pointYaAll();

	//z������û�е�
	vector<Point> Ji;
	vector<Point> Xiao;
	vector<Point> Ya;
	//z������Ҳ�е�
	vector<Point> JiAll;
	vector<Point> XiaoAll;
	vector<Point> YaAll;
};

