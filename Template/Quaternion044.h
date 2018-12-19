#pragma once
#include "Euler044.h"
#include "Vector044.h"
#include "Matrix044.h"

class CEuler044;
class CMatrix044;
class CVector044;
class CQuaternion044
{
public:
	CQuaternion044(void);
	~CQuaternion044(void);
	float x,y,z,w;
	void Set(float x,float y,float z,float w);
	operator float*(){return &x;}

	CEuler044 ToEuler();
	CMatrix044 ToMatrix();

	void SetAngle(float angle,CVector044 axis);//四元数设置
	void GetAngle(float&angle,CVector044&axis);//求旋转轴和角度
	CQuaternion044& operator=(const CQuaternion044&p);//重载赋值
	CQuaternion044 operator+(const CQuaternion044&p);//重载‘+’
	CQuaternion044 operator*(float data);//重载数乘
	CQuaternion044 operator*(const CQuaternion044&p);//四元数乘法
	CQuaternion044 operator-(const CQuaternion044&p);//四元数求差
	CQuaternion044 operator-();//求相反数
	float dotMul(const CQuaternion044&p);//点乘
	float len();//求模
	bool Normalize();//求标准化
	CQuaternion044& Inverse();//求逆四元数，会改变自身
	CQuaternion044 GetInverse();//求逆四元数，不改变自身，生成新的四元数
	CQuaternion044 Div(const CQuaternion044&b);//求差，当前为a，求c=a-b
	CQuaternion044 Slerp(CQuaternion044&Vend,float t);//插值。从当前四元数插值到Vend四元数，t是参数[0,1]
	void Slerp(CQuaternion044&Vend,int n,float*t,CQuaternion044 *Result);//插值，一次插值出n个数据，插值参数保存在数组t中，结果返回到数组Result中。

	void myQuaternionPrint();
	void split(char *buffer,float*a);
};

