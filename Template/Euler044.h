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

	CVector044 ToVector3(CVector044*updir=0);//ת��Ϊ����
	CMatrix044 ToMatrix();//ת��Ϊ����
	CQuaternion044 ToQuaternion();//ת��Ϊ��Ԫ��

	void eulerNormal();
};
float valToDegree(float val);
float degreeToVal(float degree);

