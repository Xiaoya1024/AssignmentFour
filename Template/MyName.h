#pragma once
#include <vector>
#include "Vector044.h"
#define CIRCLENUM 15
#define POINTNUM 231//名字轨迹点的个数
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

	CVector044 g_pos[POINTNUM];//名字上点的个数
	CVector044 g_circle[CIRCLENUM];
	CVector044 g_allPos[POINTNUM*CIRCLENUM];//名字上所有圆环点的个数
	int JiNum,XiaoNum,YaNum;
	int point[23];
	void pointJi();
	void pointXiao();
	void pointYa();

	void pointJiAll();
	void pointXiaoAll();
	void pointYaAll();

	//z方向上没有点
	vector<Point> Ji;
	vector<Point> Xiao;
	vector<Point> Ya;
	//z方向上也有点
	vector<Point> JiAll;
	vector<Point> XiaoAll;
	vector<Point> YaAll;

	void DrawName(int type);
	void InitName();
};

