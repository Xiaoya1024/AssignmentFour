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

	void SetAngle(float angle,CVector044 axis);//��Ԫ������
	void GetAngle(float&angle,CVector044&axis);//����ת��ͽǶ�
	CQuaternion044& operator=(const CQuaternion044&p);//���ظ�ֵ
	CQuaternion044 operator+(const CQuaternion044&p);//���ء�+��
	CQuaternion044 operator*(float data);//��������
	CQuaternion044 operator*(const CQuaternion044&p);//��Ԫ���˷�
	CQuaternion044 operator-(const CQuaternion044&p);//��Ԫ�����
	CQuaternion044 operator-();//���෴��
	float dotMul(const CQuaternion044&p);//���
	float len();//��ģ
	bool Normalize();//���׼��
	CQuaternion044& Inverse();//������Ԫ������ı�����
	CQuaternion044 GetInverse();//������Ԫ�������ı����������µ���Ԫ��
	CQuaternion044 Div(const CQuaternion044&b);//����ǰΪa����c=a-b
	CQuaternion044 Slerp(CQuaternion044&Vend,float t);//��ֵ���ӵ�ǰ��Ԫ����ֵ��Vend��Ԫ����t�ǲ���[0,1]
	void Slerp(CQuaternion044&Vend,int n,float*t,CQuaternion044 *Result);//��ֵ��һ�β�ֵ��n�����ݣ���ֵ��������������t�У�������ص�����Result�С�

	void myQuaternionPrint();
	void split(char *buffer,float*a);
};

