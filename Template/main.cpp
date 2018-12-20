#include "MyName.h"
#include "Car.h"
#include "Vector044.h"
#include "Matrix044.h"
#include "Euler044.h"
#include "Quaternion044.h"
#include "gl\glut.h"
#include "Curve044.h"

#define SLERPNUM 20		//��ֵ��
#define CAMERASLERPNUM 50//������Ĳ�ֵ��

void myDisplay(void);
void myReshape(int w,int h);
void myTimerFunc(int val);
void myKeyboardFunc(unsigned char key,int x,int y);
void mySpecialFunc(int key,int x,int y);
void myKeyboardFuncUp(unsigned char key,int x,int y);
void SetRC();
void SetView();
void updateOperate();
void CarDisplay();
void cameraSlerp();
int g_mode=0;//�켣ͨ��ģʽ
MyName myName;
Car car;
Car*npcCar=new Car[10];

int mode=0;//�ӵ����ģʽ��Ϊ0��ʾŷ���ǿ��ƣ�Ϊ1��ʾ���η�ʽ����
int g_carMode=0;//С��ģʽ
float rspeed=0.1f;
float mspeed=0.1f;
float g_IEyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//����
CMatrix044 IEyeMat;//����ӵ����
float g_EyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//ŷ���ǿ���ʱ���������ת����
CMatrix044 EyeMat;//����ӵ����

float mx=0,my=0,mz=0,rx=0,ry=0,rz=0;
float sx=1,sy=1,sz=1;
bool check_A=false,check_D=false,check_W=false,check_S=false,check_Q=false,check_E=false;
bool check_J=false,check_L=false,check_I=false,check_K=false,check_O=false,check_U=false;
bool check_LeftArrow=false,check_RightArrow=false,check_UpArrow=false,check_DownArrow=false;

/*��������Ĳ�ֵ��������*/
CVector044 cameraEye,cameraTarget;
int cameraCurrentT=0;//�������ֵ��
float g_cacheSpeed=0;//���������ֵ�����б����С�����ٶ�
bool isCameraSlerp=false;//������Ƿ���в�ֵ
CVector044 cameraPos[CAMERASLERPNUM];//�����λ�ò�ֵ���
float cameraSlerp_t[CAMERASLERPNUM];//�������ֵ��ֵ
CQuaternion044 cameraSlerp_Qua[CAMERASLERPNUM];//�������Ԫ����ֵ���
bool isClick=false;//�Ƿ����˼����ϵ�3

int main(int argc,char**argv){
	/*CCurve044 cCurve;
	cCurve.myCurvePrint();*/

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1500,600);
	glutCreateWindow("AssignmentThree");
	glutDisplayFunc(&myDisplay);
	glutTimerFunc(1,myTimerFunc,1);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	glutKeyboardUpFunc(&myKeyboardFuncUp);
	glutSpecialFunc(&mySpecialFunc);
	SetRC();
	glutMainLoop();
}
void myDisplay(){
	glClearColor(0.8,0.8,0.8, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	SetView();
	glTranslatef(0,0,-25);
	updateOperate();
	if(g_carMode==1)
		glScalef(20,20,20);
	else
		glScalef(1,1,1);
	CarDisplay();
	myName.DrawName(g_mode);
	glPopMatrix();
	glutSwapBuffers();
}
void CarDisplay(){
	if(g_carMode==1){//˾���ӽ�
		CVector044 carDir;
		carDir=car.g_CarDir.getNormalize();
		cameraEye=car.g_CarPos+carDir*(-1);
		cameraTarget=car.g_CarPos+carDir*(10);

		if(!isCameraSlerp&&!car.isSlerp&&isClick){//����ʱû�д��ڲ�ֵ�����еĻ�
			isClick=false;
			isCameraSlerp=true;
			g_cacheSpeed=car.g_CarSpeed;
			car.g_CarSpeed=0;
			CVector044 beginCameraPos;
			beginCameraPos.Set(g_EyeMat[12],g_EyeMat[13],g_EyeMat[14]);
			CVector044 endCameraPos=cameraEye;
			beginCameraPos.lerp(endCameraPos,CAMERASLERPNUM,cameraSlerp_t,cameraPos);

			CQuaternion044 currentCameraQue,lastCameraQue;
			currentCameraQue=EyeMat.ToQuaternion();
			lastCameraQue=carDir.ToEuler().ToQuaternion();
			currentCameraQue.Slerp(lastCameraQue,CAMERASLERPNUM,cameraSlerp_t,cameraSlerp_Qua);
		}
		if(isCameraSlerp){//���в�ֵ
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cameraPos[cameraCurrentT].x,cameraPos[cameraCurrentT].y,cameraPos[cameraCurrentT].z);
			glMultMatrixf(cameraSlerp_Qua[cameraCurrentT].ToMatrix());
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();

			cameraCurrentT++;
			cameraCurrentT=cameraCurrentT%CAMERASLERPNUM;
			if(cameraCurrentT==0){//��ʱ��ֵ����
				car.g_CarSpeed=g_cacheSpeed;
				isCameraSlerp=false;
				if(car.g_CarDir.x)
					gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,0,1,0);
				else{
					if(car.g_CarDir.y<0)
						gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,1,0,0);
					else
						gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,-1,0,0);
				}
			}
		}
		
	if(!isCameraSlerp){//������ֵ��ʱ��
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cameraPos[cameraCurrentT].x,cameraPos[cameraCurrentT].y,cameraPos[cameraCurrentT].z);//�������д�����������дcameraEye������ΪС���ڶ������������ջ��������
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
			if(car.g_CarDir.x)
				gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,0,1,0);
			else{
				if(car.g_CarDir.y<0)
					gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,1,0,0);
				else
					gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,-1,0,0);
			}
		}
	}
	else if(g_carMode==0){
		CVector044 beforePos;
		CMatrix044 beforeMat;
		if(isClick){
			beforePos.Set(g_EyeMat[12],g_EyeMat[13],g_EyeMat[14]);
			beforeMat.Set(&g_EyeMat[0]);
		}
		if(isClick&&!isCameraSlerp&&!car.isSlerp){//��ʱ��˾���ӽ�ת��·���ӽ�
			isClick=false;
			isCameraSlerp=true;
			CVector044 beginCameraPos=cameraEye;
			CVector044 endCameraPos=beforePos;
			beginCameraPos.lerp(endCameraPos,CAMERASLERPNUM,cameraSlerp_t,cameraPos);

			CQuaternion044 currentCameraQue,lastCameraQue;
			currentCameraQue=car.g_CarDir.getNormalize().ToEuler().ToQuaternion();
			lastCameraQue=EyeMat.ToQuaternion();
			currentCameraQue.Slerp(lastCameraQue,CAMERASLERPNUM,cameraSlerp_t,cameraSlerp_Qua);
		}
		if(isCameraSlerp){//���в�ֵ
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cameraPos[cameraCurrentT].x,cameraPos[cameraCurrentT].y,cameraPos[cameraCurrentT].z);
			glMultMatrixf(cameraSlerp_Qua[cameraCurrentT].ToMatrix());
			if(mode==0)
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			else
				glGetFloatv(GL_MODELVIEW_MATRIX,g_IEyeMat);
			glPopMatrix();

			cameraCurrentT++;
			cameraCurrentT=cameraCurrentT%CAMERASLERPNUM;
			if(cameraCurrentT==0){
				isCameraSlerp=false;//��ֵ����
				CVector044 updir;
				updir.Set(0,1,0);
				updir=beforeMat.MulVector(updir);
				gluLookAt(beforePos.x,beforePos.y,beforePos.z,car.g_CarPos.x,car.g_CarPos.y,car.g_CarPos.z,updir.x,updir.y,updir.z);
			}
		}
	}
	car.run();
	for(int i=0;i<10;i++){
		npcCar[i].run();
	}
}
void myReshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,GLfloat(w)/h,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myTimerFunc(int val){
	if(!(fabs(car.g_CarSpeed)<1e-6))
		car.wheelAngle+=0.5;
	car.update(myName,car.beginIndex,car.endIndex);
	for(int i=0;i<10;i++)
		npcCar[i].update(myName,car.beginIndex,car.endIndex);
	myDisplay();
	glutTimerFunc(1,myTimerFunc,1);
}
void myKeyboardFuncUp(unsigned char key,int x,int y){
	switch(key){
	case 'w'://����ƽ��
		check_W= false;
		break;
	case 's'://����ƽ��
		check_S = false;
		break;
	case 'a'://����ƽ��
		check_A = false;
		break;
	case 'd'://����ƽ��
		check_D = false;
		break;
	case 'q'://�ӵ�ƽ������
		check_Q = false;
		break;
	case 'e'://�ӵ�ƽ����Զ
		check_E = false;
		break;
	case 'i'://�ӵ�������ת
		check_I= false;
		break;
	case 'k'://�ӵ�������ת
		check_K = false;
		break;
	case 'j'://�ӵ�������ת
		check_J = false;
		break;
	case 'l'://�ӵ�������ת
		check_L = false;
		break;
	case 'u'://��z��������ת
		check_U = false;
		break;
	case 'o'://��z�Ḻ����ת
		check_O= false;
		break;
	}
}
void mySpecialFunc(int key,int x,int y){
	switch(key){
	case GLUT_KEY_LEFT:
		if(mode==0&&g_carMode==1){
			
		}
		break;
	case GLUT_KEY_RIGHT:
		if(mode==0&&g_carMode==1){
			
		}
		break;
	case GLUT_KEY_UP:
		if(mode==0&&g_carMode==1){
			if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
				car.g_CarDir=car.g_CarDir*(-1);
				car.g_CarIndex--;
			}
			car.g_CarSpeed=car.g_CarSpeed+0.01f;
			if(car.g_CarSpeed>0.2f)
				car.g_CarSpeed=0.2f;
		}
		break;
	case GLUT_KEY_DOWN:
		if(mode==0&&g_carMode==1){
			if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
				car.g_CarDir=car.g_CarDir*(-1);
				car.g_CarIndex++;
			}
			car.g_CarSpeed=car.g_CarSpeed-0.01f;
			if(car.g_CarSpeed<-0.2f)
				car.g_CarSpeed=-0.2f;
		}
		break;
	}
}
void myKeyboardFunc(unsigned char key,int x,int y){
	switch(key){
	case ' ':
		g_mode = 1 - g_mode;//���ֹ��ģʽ
		break;
	case '1':
		mode=0;//ŷ����
		break;
	case '2':
		mode=1;//����
		break;
	case '3':
		{
			if(isCameraSlerp==false)
			{
				g_carMode=1-g_carMode;//С���ӽ�ģʽ:0-��ͨ��1-˾��
				mode=0;
				isClick=true;
			}
			break;
		}
	case '.'://�ص����
		g_mode=0;
		g_carMode=0;
		mode=0;
		car.g_CarSpeed=0.03f;
		car.g_CarPos=myName.g_pos[0];
		car.g_CarDir=myName.g_pos[1]-myName.g_pos[0];
		car.g_CarDir.Normalize();
		car.g_CarIndex=0;
		mx=0;
		my=0;
		mz=0;
		rx=0;
		ry=0;
		rz=0;
		for(int i=0;i<16;i++){
			g_EyeMat[i]=g_IEyeMat[i];
		}
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-rz, 0, 0, 1);
		glRotatef(-rx, 1, 0, 0);
		glRotatef(-ry, 0, 1, 0);
		glTranslatef(-mx, -my, -mz);
		glGetFloatv(GL_MODELVIEW_MATRIX, g_EyeMat);
		glPopMatrix();
		break;
	case '='://С���ٶȼ���
		if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
				car.g_CarDir=car.g_CarDir*(-1);
				car.g_CarIndex--;
		}
		car.g_CarSpeed=car.g_CarSpeed+0.01f;
		if(car.g_CarSpeed>0.2f)
			car.g_CarSpeed=0.2f;
		break;
	case '+':
		if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			car.g_CarDir=car.g_CarDir*(-1);
			car.g_CarIndex--;
		}
		car.g_CarSpeed=car.g_CarSpeed+0.01f;
		
		if(car.g_CarSpeed>0.2f)
			car.g_CarSpeed=0.2f;
		break;
	case '-'://С���ٶȼ���
		if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			car.g_CarDir=car.g_CarDir*(-1);
			car.g_CarIndex++;
		}
		car.g_CarSpeed=car.g_CarSpeed-0.01f;
		if(car.g_CarSpeed<-0.2f)
			car.g_CarSpeed=-0.2f;
		break;
	case '_':
		if(fabs(car.g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			car.g_CarDir=car.g_CarDir*(-1);
			car.g_CarIndex++;
		}
		car.g_CarSpeed=car.g_CarSpeed-0.01f;
		if(car.g_CarSpeed<-0.2f)
			car.g_CarSpeed=-0.2f;
		break;
	case '[':
		mspeed-=0.01f;
		if(mspeed<0.01){
			mspeed=0.01f;
		}
		break;
	case ']':
		mspeed+=0.01f;
		break;
	case '{':
		rspeed-=0.01f;
		if(rspeed<0.01f){
			rspeed=0.01f;
		}
		break;
	case '}':
		rspeed+=0.01f;
		break;
	case 'w'://����ƽ��
		check_W= true;
		break;
	case 's'://����ƽ��
		check_S=true;
		break;
	case 'a'://����ƽ��
		check_A = true;
		break;
	case 'd'://����ƽ��
		check_D = true;
		break;
	case 'q'://�ӵ�ƽ������
		check_Q = true;
		break;
	case 'e'://�ӵ�ƽ����Զ
		check_E = true;
		break;
	case 'i'://�ӵ�������ת
		check_I = true;
		break;
	case 'k'://�ӵ�������ת
		check_K = true;
		break;
	case 'j'://�ӵ�������ת
		check_J = true;
		break;
	case 'l'://�ӵ�������ת
		check_L = true;
		break;
	case 'u'://��z��������ת
		check_U = true;
		break;
	case 'o'://��z�Ḻ����ת
		check_O= true;
		break;
	
	}
}
void updateOperate(){
	bool bChange = false;
	if(check_W){//w
		if(mode==0){//������ģ��
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,-mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{//�����������
			mx+=g_IEyeMat[4]*mspeed;
			my+=g_IEyeMat[5]*mspeed;
			mz+=g_IEyeMat[6]*mspeed;
			bChange=true;
		}
	}
	if(check_S){//s
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}else{
			mx-=g_IEyeMat[4]*mspeed;
			my-=g_IEyeMat[5]*mspeed;
			mz-=g_IEyeMat[6]*mspeed;
			bChange=true;
		}
	}
	if(check_A){//a
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			mx-=g_IEyeMat[0]*mspeed;
			my-=g_IEyeMat[1]*mspeed;
			mz-=g_IEyeMat[2]*mspeed;
			bChange=true;
		}

	}
	if(check_D){//d
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			mx+=g_IEyeMat[0]*mspeed;
			my+=g_IEyeMat[1]*mspeed;
			mz+=g_IEyeMat[2]*mspeed;
			bChange=true;
		}

	}
	if(check_Q){//q
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			mx-=g_IEyeMat[8]*mspeed;
			my-=g_IEyeMat[9]*mspeed;
			mz-=g_IEyeMat[10]*mspeed;
			bChange=true;
		}

	}
	if(check_E){//e
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,-mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			mx+=g_IEyeMat[8]*mspeed;
			my+=g_IEyeMat[9]*mspeed;
			mz+=g_IEyeMat[10]*mspeed;
			bChange=true;
		}

	}
	if(check_I){//i
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			rx+=rspeed;
		}

	}
	if(check_K){//k
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			rx-=rspeed;
		}

	}
	if(check_J){
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			ry+=rspeed;
		}

	}
	if(check_L){
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			ry-=rspeed;
		}

	}
	if(check_U){
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			rz+=rspeed;
		}
	}
	if(check_O){
		if(mode==0){
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{
			bChange=true;
			rz-=rspeed;
		}
	}

	if(bChange)//�����ӵ����������
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(mx,my,mz);
		glRotatef(ry,0,1,0);
		glRotatef(rx,1,0,0);
		glRotatef(rz,0,0,1);
		glGetFloatv(GL_MODELVIEW_MATRIX,g_IEyeMat);
		glPopMatrix();
	}
}
void SetRC(){
	myName.InitName();

	car.Set(0.02f,0,231);
	car.g_CarPos=myName.g_pos[car.beginIndex];
	car.g_CarDir=myName.g_pos[car.beginIndex+1]-myName.g_pos[car.beginIndex];
	car.g_CarDir.Normalize();
	car.g_CarIndex=car.beginIndex;

	//��ʼ��npcС��
	for(int i=0;i<10;i++){
		npcCar[i].Set(0.02f,i*20+10,i*20+30);
		npcCar[i].g_CarPos=myName.g_pos[npcCar[i].beginIndex];
		npcCar[i].g_CarDir=myName.g_pos[npcCar[i].beginIndex+1]-myName.g_pos[npcCar[i].beginIndex];
		npcCar[i].g_CarDir.Normalize();
		npcCar[i].g_CarIndex=npcCar[i].beginIndex;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for(int i=1;i<=CAMERASLERPNUM;i++)
		cameraSlerp_t[i-1]=float(i)/CAMERASLERPNUM;
}
void SetView()
{
	if(mode==0)//ŷ����
	{
		glLoadMatrixf(g_EyeMat);
		EyeMat.Set(&g_EyeMat[0]);
	}
	else//��������
	{
		glRotatef(-rz,0,0,1);	
		glRotatef(-rx,1,0,0);
		glRotatef(-ry,0,1,0);
		glTranslatef(-mx,-my,-mz);
		IEyeMat.Set(&g_IEyeMat[0]);
	}
}