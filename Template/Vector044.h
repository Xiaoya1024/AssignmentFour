#pragma once
#include <math.h>
#include <iostream>
#include <fstream>//�ļ�
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

	float x;//���Ա
	float y;
	float z;

	void Set(float x,float y,float z);
	CVector044 operator+(CVector044 &p);//���ء�+������
	CVector044 operator-(CVector044 &p);//���ء�-������
	CVector044 operator*(float p);//���ء�*������
	CVector044& operator=(CVector044 &p);//���ء�=������
	bool operator==(CVector044 &p);//���ء�==������
	bool operator!=(CVector044 &p);//���ء�!=������
	float dotMul(CVector044 &n);//������˲���
	CVector044 crossMul(CVector044 &n);//������˲���
	void Normalize();//������׼������
	CVector044 getNormalize();//��ȡ������׼�����
	float len();//������ģ����
	CVector044 project(CVector044 &n);//����ͶӰ����
	operator float*(){
		return &x;//�Զ�����ת��
	}

	float findSeta(CVector044&p);
	CVector044 rotateByZ(float angle);//������z����ת(��)angle=10��

	CEuler044 ToEuler();
	CVector044 lerp(CVector044&Vend,float t);//��ֵ
	void lerp(CVector044&Vend,int n,float*t,CVector044*Result);//��ֵ
};

