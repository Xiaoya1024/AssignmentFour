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
	operator float*(){return &m00;}//状态转换
	void Set(float *p);

	CMatrix044& operator=(const CMatrix044&p);//矩阵赋值
	CMatrix044 operator*(float d);//矩阵数乘

	CMatrix044 operator*(CMatrix044&p);//矩阵相乘
	CMatrix044 operator/(float p);//矩阵相除
	CMatrix044 operator+(CMatrix044&p);//矩阵相加

	//矩阵乘以空间位置得到一个位置，w默认为1，结果不除w，与*不同。
	CVector044 MulPosition(CVector044& p);//矩阵乘位置
	//矩阵乘以空间一个向量，w为0
	CVector044 MulVector(CVector044& p);//矩阵乘向量
	//0表示x轴旋转，1表示y轴，2表示z轴
	CMatrix044& SetRotate(float seta,CVector044&axis);//矩阵设置旋转
	CMatrix044& SetRotateByAxis(float seta,int axis);//按x，y，z轴旋转
	CMatrix044& SetTrans(CVector044&trans);//矩阵设置位移
	CMatrix044& SetScale(CVector044&p);//矩阵设置缩放
	float Determinant();//求矩阵的行列式
	CMatrix044 Adjoint();//求四阶矩阵的伴随矩阵
	float Inverse();//矩阵求逆，成功返回行列式的值，否则返回0
	CMatrix044 GetInverse();//返回逆矩阵
	void split(char *buffer,float*a);
	void MyMatrix();//输出结果

	CEuler044 ToEuler();//矩阵转化为欧拉角
	CQuaternion044 ToQuaternion();//矩阵转化为四元数
};

