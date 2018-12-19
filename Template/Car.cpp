#include "Car.h"

Car::Car(void)
{
}

Car::~Car(void)
{
}
void Car::InitBody(){

	//车下半部  
	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-40.0f, 0.0f, 15.0f);
	glVertex3f(-40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, -15.0f);
	glVertex3f(40.0f, 0.0f, 15.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8,0.8);
	glVertex3f(-40.0f, -15.0f, 15.0f);
	glVertex3f(-40.0f, -15.0f, -15.0f);
	glVertex3f(40.0f, -15.0f, -15.0f);
	glVertex3f(40.0f, -15.0f, 15.0f);
	glEnd();
	//车上半部  
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-20.0f, 0.0f, 15.0f);
	glVertex3f(25.0f, 0.0f, 15.0f);
	glColor3f(0.1, 0.1, 0.1);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glVertex3f(-10.0f, 10.0f, 15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-20.0f, 0.0f, -15.0f);
	glVertex3f(25.0f, 0.0f, -15.0f);
	glColor3f(0.1, 0.1, 0.1);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-10.0f, 10.0f, 15.0f);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-20.0f, 0.0f, 15.0f);
	glVertex3f(-20.0f, 0.0f, -15.0f);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(-10.0f, 10.0f, -15.0f);
	glVertex3f(-10.0f, 10.0f, 15.0f);

	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(20.0f, 10.0f, 15.0f);
	glVertex3f(20.0f, 10.0f, -15.0f);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(25.0f, 0.0f, -15.0f);
	glVertex3f(25.0f, 0.0f, 15.0f);
	glEnd();

	//车尾

	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(35.0f,0.0f,15.0f);
	glVertex3f(35.0f,0.0f,-15.0f);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(45.0f,5.0f,-15.0f);
	glVertex3f(45.0f,5.0f,15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(40.0f,0.0f,15.0f);
	glVertex3f(40.0f,0.0f,-15.0f);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(45.0f,5.0f,-15.0f);
	glVertex3f(45.0f,5.0f,15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(35.0f,0.0f,15.0f);
	glVertex3f(40.0f,0.0f,15.0f);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(45.0f,5.0f,15.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(35.0f,0.0f,-15.0f);
	glVertex3f(40.0f,0.0f,-15.0f);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(45.0f,5.0f,-15.0f);
	glEnd();
}
void Car::InitWheel(float speed){
	//车轮  
	glColor3f(0, 0, 0);
	//glPointSize(10);
	//前左车轮
	glTranslated(-20.0f, -15.0f, 15.0f);
	glPushMatrix();
	glRotatef(speed*200,0,0,1);
	glutSolidTorus(2, 6, 5, 100);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glVertex3f(6.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//前右车轮
	glColor3f(0, 0, 0);
	glTranslated(0.0f, 0.0f, -30.0f);
	glPushMatrix();
	glRotatef(speed*200,0,0,1);
	glutSolidTorus(2, 6, 5, 100);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(6.0f, 0.0f, -2.0f);
	glEnd();
	glPopMatrix();

	//后右车轮
	glColor3f(0, 0, 0);
	glTranslated(45.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(speed*200,0,0,1);
	glutSolidTorus(2, 6, 5, 100);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(6.0f, 0.0f, -2.0f);
	glEnd();
	glPopMatrix();


	//后左车轮
	glColor3f(0, 0, 0);
	glTranslated(0.0f, 0.0f, 30.0f);
	glPushMatrix();
	glRotatef(speed*200,0,0,1);
	glutSolidTorus(2, 6, 5, 100);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glVertex3f(6.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();
}
