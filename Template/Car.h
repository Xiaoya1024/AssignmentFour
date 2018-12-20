#pragma once
#include "Vector044.h"
#include "Quaternion044.h"
#include "Matrix044.h"
#include "MyName.h"
#include <gl\glut.h>
#define SLERPNUM 20		//插值数
class Car
{
public:
	Car(void);
	~Car(void);
	float wheelAngle;//轮子旋转角度
	CVector044 g_CarPos,g_CarDir,g_CarLastDir;//车的位置和方向，上一个方向 
	float g_CarSpeed;
	int g_CarIndex;
	int beginIndex,endIndex;
	CQuaternion044 currentQue,lastQue;//currentQue表示目标四元数，lastQue上一个四元数，从lastQue插值到currentQue
	bool isSlerp;//是否进行插值
	int currentT;//插值数
	float slerp_t[SLERPNUM];
	CMatrix044 slerp_cMatrix;
	//绘制的小车沿xoy平面对称，车头在x负方向
	//车身长80，宽30，高30
	void Set(float g_CarSpeed,int beginIndex,int endIndex);
	void InitBody();
	void InitWheel(float speed);
	void update(MyName myName,int beginIndex,int endIndex);
	void run();
	void DrawCar();
};

