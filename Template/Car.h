#pragma once
#include <gl\glut.h>
class Car
{
public:
	Car(void);
	~Car(void);
	//绘制的小车沿xoy平面对称，车头在x负方向
	//车身长80，宽30，高30
	void InitBody();
	void InitWheel(float speed);
};

