#include "MyName.h"
#include "Car.h"
#include "Vector044.h"
#include "Matrix044.h"
#include "Euler044.h"
#include "Quaternion044.h"
#include "gl\glut.h"
#include "Curve044.h"
#define CIRCLENUM 15
#define POINTNUM 231//���ֹ켣��ĸ���
#define SLERPNUM 40		//��ֵ��
#define CAMERASLERPNUM 100//������Ĳ�ֵ��

void myDisplay(void);
void myReshape(int w,int h);
void myTimerFunc(int val);
void myKeyboardFunc(unsigned char key,int x,int y);
void myKeyboardFuncUp(unsigned char key,int x,int y);
void SetRC();
void DrawName();
void DrawCar();
void update();
void SetView();
void updateOperate();
void CarDisplay();
void cameraSlerp();

int g_mode=0;//�켣ͨ��ģʽ
float wheelAngle=0;//������ת�Ƕ�
CVector044 g_CarPos,g_CarDir,g_CarLastDir;//����λ�úͷ�����һ������
CVector044 g_circle[CIRCLENUM];
CVector044 g_pos[POINTNUM];
CVector044 g_allPos[POINTNUM*CIRCLENUM];
float g_CarSpeed=0.02f;//�����ٶ�
float g_cacheSpeed=0;//���������ֵ�����б����С�����ٶ�
int g_CarIndex=0;//��ǰ�����ڵĽڵ�λ��

MyName myName;
int point[23]={15,22,31,38,47,54,63,74,79,89,93,97,106,121,
	129,137,146,161,174,188,202,208,214};
int JiNum=0,XiaoNum=0,YaNum=0;

Car car;

int mode=0;//�ӵ����ģʽ��Ϊ0��ʾŷ���ǿ��ƣ�Ϊ1��ʾ���η�ʽ����
int g_carMode=0;//С��ģʽ
int dir=1;
float rspeed=0.1f;
float mspeed=0.1f;
float g_IEyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//����
CMatrix044 IEyeMat;//����ӵ����
float g_EyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//ŷ���ǿ���ʱ���������ת����
CMatrix044 EyeMat;//����ӵ����

float _mat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float rotateMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float templateMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

CMatrix044 slerp_cMatrix;
float mx=0,my=0,mz=0,rx=0,ry=0,rz=0;
float sx=1,sy=1,sz=1;
bool check_A=false,check_D=false,check_W=false,check_S=false,check_Q=false,check_E=false;
bool check_J=false,check_L=false,check_I=false,check_K=false,check_O=false,check_U=false;

int currentT=0;//��ֵ��
bool isSlerp=false;//�Ƿ���в�ֵ
CQuaternion044 currentQue,lastQue;//currentQue��ʾĿ����Ԫ����lastQue��һ����Ԫ������lastQue��ֵ��currentQue
float slerp_t[SLERPNUM];
CQuaternion044 slerp_Qua[SLERPNUM];//��Ԫ����ֵ���

/*��������Ĳ�ֵ��������*/
CVector044 cameraEye,cameraTarget;
int cameraCurrentT=0;//�������ֵ��
bool isCameraSlerp=false;//������Ƿ���в�ֵ
CVector044 cameraPos[CAMERASLERPNUM];//�����λ�ò�ֵ���

//currentCameraQue��ʾ�����Ŀ����Ԫ����lastCameraQue��һ����Ԫ������lastCameraQue��ֵ��currentCameraQue
float cameraSlerp_t[CAMERASLERPNUM];//�������ֵ��ֵ
CQuaternion044 cameraSlerp_Qua[CAMERASLERPNUM];//�������Ԫ����ֵ���
bool isClick=false;//�Ƿ����˼����ϵ�3

int main(int argc,char**argv){
	CCurve044 cCurve;
	cCurve.myCurvePrint();

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
	SetRC();
	glutMainLoop();
	
}
void update(){
	float angleChange;//��������(g_CarDir,g_CarLastDir)֮����Ҫ��ת�ĽǶ�
	//��������û��֮��ת������Ԫ���ĺ�������Ҫ�Ȱ�����ת��Ϊŷ���ǣ���ת��Ϊ��Ԫ�����в�ֵ
	CEuler044 currentEuler,lastEuler;
	if(abs(g_CarSpeed)<1e-6)return;//С���ٶ�Ϊ0

	if(g_CarSpeed>0){//С���ٶȴ���0ʱ
		g_CarIndex=(g_CarIndex+POINTNUM)%POINTNUM;
		if(g_CarIndex==POINTNUM-1)//���ߵ����һ��ʱ��С���ص����
			g_CarDir=g_pos[0]-g_CarPos;
		else{
			g_CarDir=g_pos[g_CarIndex+1]-g_CarPos;
		}
		if(g_CarIndex==0){
			g_CarLastDir=g_CarPos-g_pos[POINTNUM-1];
		}
		else
			g_CarLastDir=g_CarPos-g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM];
		angleChange=g_CarLastDir.findSeta(g_CarDir);//С����Ҫ��ת�Ļ���

		if(angleChange>0.1f&&currentT!=SLERPNUM){//ֻ�нǶȴ���0.1ʱ�Ž��в�ֵ��ת
			isSlerp=true;
			g_CarDir.Normalize();
			g_CarLastDir.Normalize();
			if(g_CarLastDir.x){
				float rotatAngle=atan(fabs(g_CarLastDir.y/g_CarLastDir.x));
				rotatAngle=valToDegree(rotatAngle);
				if(g_CarLastDir.x>0&&g_CarLastDir.y>=0)//���ϣ���������
					lastEuler.Set(0,0,rotatAngle);
				else if(g_CarLastDir.x>0&&g_CarLastDir.y<0)//���£�˳ʱ����ת
					lastEuler.Set(0,0,-rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y>=0)//���ϣ���ת���ķ���֮��˳ʱ����ת
					lastEuler.Set(180,0,rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y<0)//���£���ת���ķ���֮����ʱ����ת
					lastEuler.Set(180,0,-rotatAngle);
			}
			else{//���x=0,������ת90��
				if(g_CarLastDir.y>0)
					lastEuler.Set(0,0,90);
				else
					lastEuler.Set(0,0,-90);
			}
			lastQue=lastEuler.ToQuaternion();

			if(g_CarDir.x){
				float rotateAngle=atan(fabs(g_CarDir.y/g_CarDir.x));
				rotateAngle=valToDegree(rotateAngle);

				if(g_CarDir.x>0&&g_CarDir.y>=0)
					currentEuler.Set(0,0,rotateAngle);
				else if(g_CarDir.x>0&&g_CarDir.y<0)
					currentEuler.Set(0,0,-rotateAngle);
				else if(g_CarDir.x<0&&g_CarDir.y>=0)
					currentEuler.Set(180,0,rotateAngle);
				else if(g_CarDir.x<0&&g_CarDir.y<0)
					currentEuler.Set(180,0,-rotateAngle);
			}
			else{
				if(g_CarDir.y>0)
					currentEuler.Set(0,0,90);
				else
					currentEuler.Set(0,0,-90);
			}
			currentQue=currentEuler.ToQuaternion();
			return;
		}
		else{
			isSlerp=false;//˵����ʱ�ߵ���ֱ��
			float leftlen=(g_pos[(g_CarIndex+1)%POINTNUM]-g_CarPos).len();//��λ�õ���һ�ڵ�ľ���
			if(leftlen>g_CarSpeed){//���ʣ���������ٶ�
				g_CarDir=g_pos[(g_CarIndex+1)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*g_CarSpeed+g_CarPos;
			}
			else{//����һ����Ҫ������һ���ڵ�
				currentT%=SLERPNUM;
				g_CarIndex=(g_CarIndex+1)%POINTNUM;
				float leftlen_Last=g_CarSpeed-leftlen;
				while(leftlen_Last>(g_pos[(g_CarIndex+1)%POINTNUM]-g_pos[g_CarIndex]).len()){
					leftlen_Last-=(g_pos[(g_CarIndex+1)%POINTNUM]-g_pos[g_CarIndex]).len();
					g_CarIndex=(g_CarIndex+1)%POINTNUM;
				}
				g_CarDir=g_pos[(g_CarIndex+1)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*leftlen_Last+g_pos[g_CarIndex];
			}
		}
	}
	else if(g_CarSpeed<0){

		g_CarIndex=(g_CarIndex+POINTNUM)%POINTNUM;
		if(g_CarIndex==POINTNUM-1){//���ߵ����һ��ʱ��С���ص����
			g_CarLastDir=g_CarPos-g_pos[0];
		}
		else
			g_CarLastDir=g_CarPos-g_pos[g_CarIndex+1];

		if(g_CarIndex==0){
			g_CarDir=g_pos[POINTNUM-1]-g_CarPos;
		}
		else
			g_CarDir=g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_CarPos;

		angleChange=g_CarDir.findSeta(g_CarLastDir);//С����Ҫ��ת�Ļ���

		if(angleChange>0.1f&&currentT!=SLERPNUM){
	
			isSlerp=true;
			g_CarDir.Normalize();
			g_CarLastDir.Normalize();
			if(g_CarLastDir.x){
				float rotatAngle=atan(fabs(g_CarLastDir.y/g_CarLastDir.x));
				rotatAngle=valToDegree(rotatAngle);

				if(g_CarLastDir.x>0&&g_CarLastDir.y>=0)//���ϣ���������
					lastEuler.Set(0,0,rotatAngle);
				else if(g_CarLastDir.x>0&&g_CarLastDir.y<0)//���£�˳ʱ����ת
					lastEuler.Set(0,0,-rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y>=0)//���ϣ���ת���ķ���֮��˳ʱ����ת
					lastEuler.Set(180,0,rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y<0)//���£���ת���ķ���֮����ʱ����ת
					lastEuler.Set(180,0,-rotatAngle);
			}
			else{//���x=0,������ת90��
				if(g_CarLastDir.y>0)
					lastEuler.Set(0,0,90);
				else
					lastEuler.Set(0,0,-90);
			}
			lastQue=lastEuler.ToQuaternion();

			if(g_CarDir.x){
				float rotateAngle=atan(fabs(g_CarDir.y/g_CarDir.x));
				rotateAngle=valToDegree(rotateAngle);

				if(g_CarDir.x>0&&g_CarDir.y>=0)
					currentEuler.Set(0,0,rotateAngle);
				else if(g_CarDir.x>0&&g_CarDir.y<0)
					currentEuler.Set(0,0,-rotateAngle);
				else if(g_CarDir.x<0&&g_CarDir.y>=0)
					currentEuler.Set(180,0,rotateAngle);
				else if(g_CarDir.x<0&&g_CarDir.y<0)
					currentEuler.Set(180,0,-rotateAngle);
			}
			else{
				if(g_CarDir.y>0)
					currentEuler.Set(0,0,90);
				else
					currentEuler.Set(0,0,-90);
			}
			currentQue=currentEuler.ToQuaternion();
			return;
		}
		else{
			isSlerp=false;//˵����ʱ�ߵ���ֱ��
			float carSpeed=-g_CarSpeed;
			float leftlen=(g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_CarPos).len();//��λ�õ���һ�ڵ�ľ���
			if(leftlen>carSpeed){//���ʣ���������ٶ�
				g_CarDir=g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*carSpeed+g_CarPos;
			}
			else{//����һ����Ҫ������һ���ڵ�
				currentT%=SLERPNUM;
				g_CarIndex=(g_CarIndex-1+POINTNUM)%POINTNUM;
				float leftlen_Last=carSpeed-leftlen;
				while(leftlen_Last>(g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_pos[g_CarIndex]).len()){
					leftlen_Last-=(g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_pos[g_CarIndex]).len();
					g_CarIndex=(g_CarIndex-1+POINTNUM)%POINTNUM;
				}
				
				g_CarDir=g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*leftlen_Last+g_pos[g_CarIndex];
				
			}
		}
	}
}
void myDisplay(){
	glClearColor(0.8,0.8,0.8, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	SetView();
	glTranslatef(0,0,-25);
	updateOperate();
	if(g_carMode==1)
		glScalef(5,5,5);
	else
		glScalef(1,1,1);
	CarDisplay();
	DrawName();
	glPopMatrix();
	glutSwapBuffers();
}
void CarDisplay(){
	if(g_carMode==1){//˾���ӽ�
		CVector044 carDir;
		carDir=g_CarDir.getNormalize();
		cameraEye=g_CarPos+carDir*(-1);
		cameraTarget=g_CarPos+carDir*(10);

		if(!isCameraSlerp&&!isSlerp&&isClick){//����ʱû�д��ڲ�ֵ�����еĻ�
			isClick=false;
			isCameraSlerp=true;
			g_cacheSpeed=g_CarSpeed;
			g_CarSpeed=0;
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
				g_CarSpeed=g_cacheSpeed;
				isCameraSlerp=false;
				if(g_CarDir.x)
					gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,0,1,0);
				else{
					if(g_CarDir.y<0)
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
			if(g_CarDir.x)
				gluLookAt(cameraEye.x,cameraEye.y,cameraEye.z,cameraTarget.x,cameraTarget.y,cameraTarget.z,0,1,0);
			else{
				if(g_CarDir.y<0)
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
		if(isClick&&!isCameraSlerp&&!isSlerp){//��ʱ��˾���ӽ�ת��·���ӽ�
			isClick=false;
			isCameraSlerp=true;
			CVector044 beginCameraPos=cameraEye;
			CVector044 endCameraPos=beforePos;
			beginCameraPos.lerp(endCameraPos,CAMERASLERPNUM,cameraSlerp_t,cameraPos);

			CQuaternion044 currentCameraQue,lastCameraQue;
			currentCameraQue=g_CarDir.getNormalize().ToEuler().ToQuaternion();
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
					gluLookAt(beforePos.x,beforePos.y,beforePos.z,g_CarPos.x,g_CarPos.y,g_CarPos.z,updir.x,updir.y,updir.z);
				}
		}
	}
	
	//С���˶�
	glPushMatrix();
	glTranslatef(g_CarPos.x,g_CarPos.y,g_CarPos.z);
	if(isSlerp){//С����ת���в�ֵ
		lastQue.Slerp(currentQue,SLERPNUM,slerp_t,slerp_Qua);
		slerp_cMatrix=slerp_Qua[currentT].ToMatrix();//�õ���ת����
		glMultMatrixf(slerp_cMatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX,slerp_cMatrix);

		DrawCar();
		currentT++;
	}
	else{//С��ֱ��
			if (g_CarDir.x)
			{
				float angle = atan(fabs((g_CarDir.y / g_CarDir.x))); //���㻡��
				angle = valToDegree(angle); //����Ƕ�
				if (g_CarDir.x > 0 && g_CarDir.y >=0){
					glRotated(angle, 0, 0, 1);
				}	
				else if (g_CarDir.x > 0 && g_CarDir.y < 0) {
					glRotated(-angle, 0, 0, 1);
				}
				else if (g_CarDir.x < 0 && g_CarDir.y >= 0){ 
					glRotated(-angle, 0, 0, 1);
					glRotated(180,0,1,0);//��ֹС����������
				}
				else if (g_CarDir.x < 0 && g_CarDir.y < 0){ 
					glRotated(angle, 0, 0, 1);
					glRotated(180,0,1,0);
				}
			}
			//���x=0,����ת90��
			else
			{
				if (g_CarDir.y > 0){
					glRotated(90, 0, 0, 1);
				}
				else
					glRotated(-90, 0, 0, 1);			
			}
	}
	DrawCar();
	glPopMatrix();
}
void DrawName(){//һ��ʼ����λ�õ�z��Ϊ0
	if(g_mode==0){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glColor3f(0.5,0.4,0.1);
		for(int i=0;i<JiNum+XiaoNum+YaNum;i++){
			glBegin(GL_LINE_STRIP);	
			for(int j=0;j<CIRCLENUM;j++)
				glVertex3fv(g_allPos[i*CIRCLENUM+j]);
			glEnd();
		}
	}
	else if(g_mode==1){

		CMatrix044 mat;
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);
		for(int i=0;i<JiNum+XiaoNum+YaNum-2;i++){
			int flag=0;
			for(int j=0;j<23;j++){
				if(i==point[j]){
					flag=1;
					glEnd();
					glColor4f(1,1,1,0.3);
					glBegin(GL_TRIANGLE_STRIP);
					break;
				}
			}
			if(flag==0){
				glColor3f(0.5,0.4,0.1);
			}
			for(int j=0;j<CIRCLENUM;j++){
				int index1=i*CIRCLENUM+j;
				int index2=index1+CIRCLENUM;
				glVertex3fv(g_allPos[index1]);
				glVertex3fv(g_allPos[index2]);
			}
		}
		glEnd();
	}
}
void DrawCar(){
	glPushMatrix();
	glScalef(0.03f,0.03f,0.03f);
	glRotatef(180,0,1,0);//��ת��ͷ�ķ�����x��������
	car.InitBody();
	car.InitWheel(wheelAngle*g_CarSpeed);
	glPopMatrix();
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
	if(!(fabs(g_CarSpeed)<1e-6)){
		wheelAngle+=0.1;
	}
	update();
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
	case '.':
		g_mode=0;
		g_carMode=0;
		mode=0;
		g_CarSpeed=0.03f;
		g_CarPos=g_pos[0];
		g_CarDir=g_pos[1]-g_pos[0];
		g_CarDir.Normalize();
		g_CarIndex=0;
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
		if(fabs(g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
				g_CarDir=g_CarDir*(-1);
				g_CarIndex--;
		}
		g_CarSpeed=g_CarSpeed+0.01f;
		if(g_CarSpeed>0.2f)
			g_CarSpeed=0.2f;
		break;
	case '+':
		if(fabs(g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			g_CarDir=g_CarDir*(-1);
			g_CarIndex--;
		}
		g_CarSpeed=g_CarSpeed+0.01f;
		
		if(g_CarSpeed>0.2f)
			g_CarSpeed=0.2f;
		break;
	case '-'://С���ٶȼ���
		if(fabs(g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			g_CarDir=g_CarDir*(-1);
			g_CarIndex++;
		}
		g_CarSpeed=g_CarSpeed-0.01f;
		if(g_CarSpeed<-0.2f)
			g_CarSpeed=-0.2f;
		break;
	case '_':
		if(fabs(g_CarSpeed)<= 1e-6){//�����ʱ����Ϊ0����Ҫ�������ٵĻ�����Ҫ��ת���н��ķ�����Ϊ����ʼ������
			g_CarDir=g_CarDir*(-1);
			g_CarIndex++;
		}
		g_CarSpeed=g_CarSpeed-0.01f;
		if(g_CarSpeed<-0.2f)
			g_CarSpeed=-0.2f;
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
	//��������·��(0,0,0)
	myName.pointJi();
	myName.pointXiao();
	myName.pointYa();
	for(int i=0;i<CIRCLENUM;i++){
		float angle=i*2*3.14/(CIRCLENUM-1);
		g_circle[i].x=0;
		g_circle[i].y=1*cos(angle);
		g_circle[i].z=1*sin(angle);
	}
	JiNum=myName.Ji.size();
	XiaoNum=myName.Xiao.size();
	YaNum=myName.Ya.size();

	int cnt=0;
	int scale=25;
	for(int i=0;i<JiNum;i++){
		myName.Ji[i].x-=1.0f;
		g_pos[cnt].x=myName.Ji[i].x*scale;
		g_pos[cnt].y=myName.Ji[i].y*scale;
		g_pos[cnt++].z=myName.Ji[i].z;
	}
	for(int i=0;i<XiaoNum;i++){
		g_pos[cnt].x=myName.Xiao[i].x*scale;
		g_pos[cnt].y=myName.Xiao[i].y*scale;
		g_pos[cnt++].z=myName.Xiao[i].z;
	}
	for(int i=0;i<YaNum;i++){
		myName.Ya[i].x+=1.0f;
		g_pos[cnt].x=myName.Ya[i].x*scale;
		g_pos[cnt].y=myName.Ya[i].y*scale;
		g_pos[cnt++].z=myName.Ya[i].z;
	}
	CMatrix044 mat;
	for(int i=0;i<cnt;i++){
		CVector044 dir;
		float rotang=0;
		int flag=0;
		for(int j=0;j<22;j++){
			if(i==point[j]){
				flag=1;
				dir=g_pos[i]-g_pos[(i+cnt-1)%cnt];
				break;
			}
		}
		if(flag==0){
			dir=g_pos[(i+1)%cnt]-g_pos[i];
		}
		dir.Normalize();//����
		rotang=acos(dir.x);//dir�루1��0��0)�����н�
		if(dir.y<0)rotang=-rotang;
		mat.SetRotateByAxis(rotang,2);//����Ϊ��ת����
		mat[12]=g_pos[i].x;
		mat[13]=g_pos[i].y;
		mat[14]=g_pos[i].z;
		for(int j=0;j<CIRCLENUM;j++){
			int index=i*CIRCLENUM+j;
			g_allPos[index]=mat.MulPosition(g_circle[j]);
		}
	}
	g_CarPos=g_pos[0];
	g_CarDir=g_pos[1]-g_pos[0];
	g_CarDir.Normalize();
	g_CarIndex=0;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	slerp_cMatrix.Set(&_mat[0]);
	
	for(int i=1;i<=SLERPNUM;i++)
		slerp_t[i-1]=float(i)/SLERPNUM;
	for(int i=1;i<=CAMERASLERPNUM;i++)
		cameraSlerp_t[i-1]=float(i)/CAMERASLERPNUM;
	
}
void SetView()
{
	if(mode==0)//ŷ����
	{
		glLoadMatrixf(g_EyeMat);
		EyeMat.Set(&g_EyeMat[0]);
		//EyeMat=EyeMat.GetInverse();
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