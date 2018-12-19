#pragma once
#include "Vector044.h"
#include "Euler044.h"

class CVector044;
class CEuler044;
class CQuaternion044;
class CMatrix044
{
public:
	CMatrix044(void);
	~CMatrix044(void);
	float m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,m32,m03,m13,m23,m33;
	operator float*(){return &m00;}//״̬ת��
	void Set(float *p);

	CMatrix044& operator=(const CMatrix044&p);//����ֵ
	CMatrix044 operator*(float d);//��������

	CMatrix044 operator*(CMatrix044&p);//�������
	CMatrix044 operator/(float p);//�������
	CMatrix044 operator+(CMatrix044&p);//�������

	//������Կռ�λ�õõ�һ��λ�ã�wĬ��Ϊ1���������w����*��ͬ��
	CVector044 MulPosition(CVector044& p);//�����λ��
	//������Կռ�һ��������wΪ0
	CVector044 MulVector(CVector044& p);//���������
	//0��ʾx����ת��1��ʾy�ᣬ2��ʾz��
	CMatrix044& SetRotate(float seta,CVector044&axis);//����������ת
	CMatrix044& SetRotateByAxis(float seta,int axis);//��x��y��z����ת
	CMatrix044& SetTrans(CVector044&trans);//��������λ��
	CMatrix044& SetScale(CVector044&p);//������������
	float Determinant();//����������ʽ
	CMatrix044 Adjoint();//���Ľ׾���İ������
	float Inverse();//�������棬�ɹ���������ʽ��ֵ�����򷵻�0
	CMatrix044 GetInverse();//���������
	void split(char *buffer,float*a);
	void MyMatrix();//������

	CEuler044 ToEuler();//����ת��Ϊŷ����
	CQuaternion044 ToQuaternion();//����ת��Ϊ��Ԫ��
};

