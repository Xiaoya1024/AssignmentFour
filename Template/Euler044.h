#pragma once
#include "Vector044.h"
#include "Matrix044.h"
#include "Quaternion044.h"
#define PI acos(-1.0)

class CVector044;
class CMatrix044;
class CQuaternion044;
class CEuler044
{
public:
	CEuler044(void);
	~CEuler044(void);

	float h,p,b;
	void Set(float h,float p,float b);
	operator float*(){return &h;}

	CVector044 ToVector3(CVector044*updir=0);//转换为向量
	CMatrix044 ToMatrix();//转换为矩阵
	CQuaternion044 ToQuaternion();//转换为四元数

	void eulerNormal();
};
float valToDegree(float val);
float degreeToVal(float degree);

