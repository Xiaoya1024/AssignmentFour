#pragma once
#include <gl\glut.h>
class Car
{
public:
	Car(void);
	~Car(void);
	//���Ƶ�С����xoyƽ��Գƣ���ͷ��x������
	//����80����30����30
	void InitBody();
	void InitWheel(float speed);
};

