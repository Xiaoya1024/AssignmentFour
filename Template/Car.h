#pragma once
#include "Vector044.h"
#include "Quaternion044.h"
#include "Matrix044.h"
#include "MyName.h"
#include <gl\glut.h>
#define SLERPNUM 20		//��ֵ��
class Car
{
public:
	Car(void);
	~Car(void);
	float wheelAngle;//������ת�Ƕ�
	CVector044 g_CarPos,g_CarDir,g_CarLastDir;//����λ�úͷ�����һ������ 
	float g_CarSpeed;
	int g_CarIndex;
	int beginIndex,endIndex;
	CQuaternion044 currentQue,lastQue;//currentQue��ʾĿ����Ԫ����lastQue��һ����Ԫ������lastQue��ֵ��currentQue
	bool isSlerp;//�Ƿ���в�ֵ
	int currentT;//��ֵ��
	float slerp_t[SLERPNUM];
	CMatrix044 slerp_cMatrix;
	//���Ƶ�С����xoyƽ��Գƣ���ͷ��x������
	//����80����30����30
	void Set(float g_CarSpeed,int beginIndex,int endIndex);
	void InitBody();
	void InitWheel(float speed);
	void update(MyName myName,int beginIndex,int endIndex);
	void run();
	void DrawCar();
};

