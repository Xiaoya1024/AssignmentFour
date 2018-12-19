#pragma once
#include <math.h>
#include <iostream>
#include <fstream>//文件
#include <string>
#include<iomanip>
#include "Euler044.h"

using namespace std;
class CEuler044;
class CVector044
{
public:
	CVector044();
	//CVector044( const CVector044&other );
	CVector044(float x,float y,float z);
	CVector044(const CVector044 &n);

	float x;//类成员
	float y;
	float z;

	void Set(float x,float y,float z);
	CVector044 operator+(CVector044 &p);//重载“+”操作
	CVector044 operator-(CVector044 &p);//重载“-”操作
	CVector044 operator*(float p);//重载“*”操作
	CVector044& operator=(CVector044 &p);//重载“=”操作
	bool operator==(CVector044 &p);//重载“==”操作
	bool operator!=(CVector044 &p);//重载“!=”操作
	float dotMul(CVector044 &n);//向量点乘操作
	CVector044 crossMul(CVector044 &n);//向量叉乘操作
	void Normalize();//向量标准化操作
	CVector044 getNormalize();//获取向量标准化结果
	float len();//向量求模操作
	CVector044 project(CVector044 &n);//向量投影操作
	operator float*(){
		return &x;//自动类型转换
	}

	float findSeta(CVector044&p);
	CVector044 rotateByZ(float angle);//比如绕z轴旋转(逆)angle=10°

	CEuler044 ToEuler();
	CVector044 lerp(CVector044&Vend,float t);//插值
	void lerp(CVector044&Vend,int n,float*t,CVector044*Result);//插值
};

