#include "MyName.h"
#include "Car.h"
#include "Vector044.h"
#include "Matrix044.h"
#include "Euler044.h"
#include "Quaternion044.h"
#include "gl\glut.h"
#include "Curve044.h"
#define CIRCLENUM 15
#define POINTNUM 231//名字轨迹点的个数
#define SLERPNUM 40		//插值数
#define CAMERASLERPNUM 100//摄像机的插值数

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

int g_mode=0;//轨迹通道模式
float wheelAngle=0;//轮子旋转角度
CVector044 g_CarPos,g_CarDir,g_CarLastDir;//车的位置和方向，上一个方向
CVector044 g_circle[CIRCLENUM];
CVector044 g_pos[POINTNUM];
CVector044 g_allPos[POINTNUM*CIRCLENUM];
float g_CarSpeed=0.02f;//车的速度
float g_cacheSpeed=0;//在摄像机插值过程中保存的小车的速度
int g_CarIndex=0;//当前车所在的节点位置

MyName myName;
int point[23]={15,22,31,38,47,54,63,74,79,89,93,97,106,121,
	129,137,146,161,174,188,202,208,214};
int JiNum=0,XiaoNum=0,YaNum=0;

Car car;

int mode=0;//视点控制模式，为0表示欧拉角控制，为1表示漫游方式控制
int g_carMode=0;//小车模式
int dir=1;
float rspeed=0.1f;
float mspeed=0.1f;
float g_IEyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//漫游
CMatrix044 IEyeMat;//相机视点矩阵
float g_EyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//欧拉角控制时摄像机的旋转矩阵
CMatrix044 EyeMat;//相机视点矩阵

float _mat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float rotateMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float templateMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

CMatrix044 slerp_cMatrix;
float mx=0,my=0,mz=0,rx=0,ry=0,rz=0;
float sx=1,sy=1,sz=1;
bool check_A=false,check_D=false,check_W=false,check_S=false,check_Q=false,check_E=false;
bool check_J=false,check_L=false,check_I=false,check_K=false,check_O=false,check_U=false;

int currentT=0;//插值数
bool isSlerp=false;//是否进行插值
CQuaternion044 currentQue,lastQue;//currentQue表示目标四元数，lastQue上一个四元数，从lastQue插值到currentQue
float slerp_t[SLERPNUM];
CQuaternion044 slerp_Qua[SLERPNUM];//四元数插值结果

/*对摄像机的插值操作参数*/
CVector044 cameraEye,cameraTarget;
int cameraCurrentT=0;//摄像机插值数
bool isCameraSlerp=false;//摄像机是否进行插值
CVector044 cameraPos[CAMERASLERPNUM];//摄像机位置插值结果

//currentCameraQue表示摄像机目标四元数，lastCameraQue上一个四元数，从lastCameraQue插值到currentCameraQue
float cameraSlerp_t[CAMERASLERPNUM];//摄像机插值数值
CQuaternion044 cameraSlerp_Qua[CAMERASLERPNUM];//摄像机四元数插值结果
bool isClick=false;//是否点击了键盘上的3

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
	float angleChange;//两个向量(g_CarDir,g_CarLastDir)之间需要旋转的角度
	//由于向量没有之间转换成四元数的函数，需要先把向量转化为欧拉角，再转换为四元数进行插值
	CEuler044 currentEuler,lastEuler;
	if(abs(g_CarSpeed)<1e-6)return;//小车速度为0

	if(g_CarSpeed>0){//小车速度大于0时
		g_CarIndex=(g_CarIndex+POINTNUM)%POINTNUM;
		if(g_CarIndex==POINTNUM-1)//当走到最后一点时，小车回到起点
			g_CarDir=g_pos[0]-g_CarPos;
		else{
			g_CarDir=g_pos[g_CarIndex+1]-g_CarPos;
		}
		if(g_CarIndex==0){
			g_CarLastDir=g_CarPos-g_pos[POINTNUM-1];
		}
		else
			g_CarLastDir=g_CarPos-g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM];
		angleChange=g_CarLastDir.findSeta(g_CarDir);//小车需要旋转的弧度

		if(angleChange>0.1f&&currentT!=SLERPNUM){//只有角度大于0.1时才进行插值旋转
			isSlerp=true;
			g_CarDir.Normalize();
			g_CarLastDir.Normalize();
			if(g_CarLastDir.x){
				float rotatAngle=atan(fabs(g_CarLastDir.y/g_CarLastDir.x));
				rotatAngle=valToDegree(rotatAngle);
				if(g_CarLastDir.x>0&&g_CarLastDir.y>=0)//右上，不做处理
					lastEuler.Set(0,0,rotatAngle);
				else if(g_CarLastDir.x>0&&g_CarLastDir.y<0)//右下，顺时针旋转
					lastEuler.Set(0,0,-rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y>=0)//左上，调转车的方向之后顺时针旋转
					lastEuler.Set(180,0,rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y<0)//左下，调转车的方向之后逆时针旋转
					lastEuler.Set(180,0,-rotatAngle);
			}
			else{//如果x=0,则是旋转90°
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
			isSlerp=false;//说明此时走的是直线
			float leftlen=(g_pos[(g_CarIndex+1)%POINTNUM]-g_CarPos).len();//当位置到下一节点的距离
			if(leftlen>g_CarSpeed){//如果剩余距离大于速度
				g_CarDir=g_pos[(g_CarIndex+1)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*g_CarSpeed+g_CarPos;
			}
			else{//车下一步就要到达下一个节点
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
		if(g_CarIndex==POINTNUM-1){//当走到最后一点时，小车回到起点
			g_CarLastDir=g_CarPos-g_pos[0];
		}
		else
			g_CarLastDir=g_CarPos-g_pos[g_CarIndex+1];

		if(g_CarIndex==0){
			g_CarDir=g_pos[POINTNUM-1]-g_CarPos;
		}
		else
			g_CarDir=g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_CarPos;

		angleChange=g_CarDir.findSeta(g_CarLastDir);//小车需要旋转的弧度

		if(angleChange>0.1f&&currentT!=SLERPNUM){
	
			isSlerp=true;
			g_CarDir.Normalize();
			g_CarLastDir.Normalize();
			if(g_CarLastDir.x){
				float rotatAngle=atan(fabs(g_CarLastDir.y/g_CarLastDir.x));
				rotatAngle=valToDegree(rotatAngle);

				if(g_CarLastDir.x>0&&g_CarLastDir.y>=0)//右上，不做处理
					lastEuler.Set(0,0,rotatAngle);
				else if(g_CarLastDir.x>0&&g_CarLastDir.y<0)//右下，顺时针旋转
					lastEuler.Set(0,0,-rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y>=0)//左上，调转车的方向之后顺时针旋转
					lastEuler.Set(180,0,rotatAngle);
				else if(g_CarLastDir.x<0&&g_CarLastDir.y<0)//左下，调转车的方向之后逆时针旋转
					lastEuler.Set(180,0,-rotatAngle);
			}
			else{//如果x=0,则是旋转90°
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
			isSlerp=false;//说明此时走的是直线
			float carSpeed=-g_CarSpeed;
			float leftlen=(g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_CarPos).len();//当位置到下一节点的距离
			if(leftlen>carSpeed){//如果剩余距离大于速度
				g_CarDir=g_pos[(g_CarIndex-1+POINTNUM)%POINTNUM]-g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*carSpeed+g_CarPos;
			}
			else{//车下一步就要到达下一个节点
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
	if(g_carMode==1){//司机视角
		CVector044 carDir;
		carDir=g_CarDir.getNormalize();
		cameraEye=g_CarPos+carDir*(-1);
		cameraTarget=g_CarPos+carDir*(10);

		if(!isCameraSlerp&&!isSlerp&&isClick){//当此时没有处于插值过程中的话
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

		if(isCameraSlerp){//进行插值
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cameraPos[cameraCurrentT].x,cameraPos[cameraCurrentT].y,cameraPos[cameraCurrentT].z);
			glMultMatrixf(cameraSlerp_Qua[cameraCurrentT].ToMatrix());
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();

			cameraCurrentT++;
			cameraCurrentT=cameraCurrentT%CAMERASLERPNUM;
			if(cameraCurrentT==0){//此时插值结束
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
		
	if(!isCameraSlerp){//当不插值的时候
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cameraPos[cameraCurrentT].x,cameraPos[cameraCurrentT].y,cameraPos[cameraCurrentT].z);//这里必须写成这个，不能写cameraEye。。因为小车在动。。所以最终会稍有误差
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
		if(isClick&&!isCameraSlerp&&!isSlerp){//此时从司机视角转到路人视角
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
		if(isCameraSlerp){//进行插值
			
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
					isCameraSlerp=false;//插值结束
					CVector044 updir;
					updir.Set(0,1,0);
					updir=beforeMat.MulVector(updir);
					gluLookAt(beforePos.x,beforePos.y,beforePos.z,g_CarPos.x,g_CarPos.y,g_CarPos.z,updir.x,updir.y,updir.z);
				}
		}
	}
	
	//小车运动
	glPushMatrix();
	glTranslatef(g_CarPos.x,g_CarPos.y,g_CarPos.z);
	if(isSlerp){//小车旋转进行插值
		lastQue.Slerp(currentQue,SLERPNUM,slerp_t,slerp_Qua);
		slerp_cMatrix=slerp_Qua[currentT].ToMatrix();//得到旋转矩阵
		glMultMatrixf(slerp_cMatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX,slerp_cMatrix);

		DrawCar();
		currentT++;
	}
	else{//小车直行
			if (g_CarDir.x)
			{
				float angle = atan(fabs((g_CarDir.y / g_CarDir.x))); //计算弧度
				angle = valToDegree(angle); //计算角度
				if (g_CarDir.x > 0 && g_CarDir.y >=0){
					glRotated(angle, 0, 0, 1);
				}	
				else if (g_CarDir.x > 0 && g_CarDir.y < 0) {
					glRotated(-angle, 0, 0, 1);
				}
				else if (g_CarDir.x < 0 && g_CarDir.y >= 0){ 
					glRotated(-angle, 0, 0, 1);
					glRotated(180,0,1,0);//防止小车车顶朝下
				}
				else if (g_CarDir.x < 0 && g_CarDir.y < 0){ 
					glRotated(angle, 0, 0, 1);
					glRotated(180,0,1,0);
				}
			}
			//如果x=0,则旋转90°
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
void DrawName(){//一开始名字位置的z轴为0
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
	glRotatef(180,0,1,0);//调转车头的方向朝向x轴正方向
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
	case 'w'://向上平移
		check_W= false;
		break;
	case 's'://向下平移
		check_S = false;
		break;
	case 'a'://向左平移
		check_A = false;
		break;
	case 'd'://向右平移
		check_D = false;
		break;
	case 'q'://视点平移拉近
		check_Q = false;
		break;
	case 'e'://视点平移拉远
		check_E = false;
		break;
	case 'i'://视点向上旋转
		check_I= false;
		break;
	case 'k'://视点向下旋转
		check_K = false;
		break;
	case 'j'://视点向左旋转
		check_J = false;
		break;
	case 'l'://视点向右旋转
		check_L = false;
		break;
	case 'u'://绕z轴正向旋转
		check_U = false;
		break;
	case 'o'://绕z轴负向旋转
		check_O= false;
		break;
	}
}
void myKeyboardFunc(unsigned char key,int x,int y){
	switch(key){
	case ' ':
		g_mode = 1 - g_mode;//名字轨道模式
		break;
	case '1':
		mode=0;//欧拉角
		break;
	case '2':
		mode=1;//漫游
		break;
	case '3':
		{
			if(isCameraSlerp==false)
			{
				g_carMode=1-g_carMode;//小车视角模式:0-普通，1-司机
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
	case '='://小车速度加速
		if(fabs(g_CarSpeed)<= 1e-6){//如果此时车速为0，还要继续加速的话，就要调转车行进的方向作为车初始化方向
				g_CarDir=g_CarDir*(-1);
				g_CarIndex--;
		}
		g_CarSpeed=g_CarSpeed+0.01f;
		if(g_CarSpeed>0.2f)
			g_CarSpeed=0.2f;
		break;
	case '+':
		if(fabs(g_CarSpeed)<= 1e-6){//如果此时车速为0，还要继续加速的话，就要调转车行进的方向作为车初始化方向
			g_CarDir=g_CarDir*(-1);
			g_CarIndex--;
		}
		g_CarSpeed=g_CarSpeed+0.01f;
		
		if(g_CarSpeed>0.2f)
			g_CarSpeed=0.2f;
		break;
	case '-'://小车速度减速
		if(fabs(g_CarSpeed)<= 1e-6){//如果此时车速为0，还要继续减速的话，就要调转车行进的方向作为车初始化方向
			g_CarDir=g_CarDir*(-1);
			g_CarIndex++;
		}
		g_CarSpeed=g_CarSpeed-0.01f;
		if(g_CarSpeed<-0.2f)
			g_CarSpeed=-0.2f;
		break;
	case '_':
		if(fabs(g_CarSpeed)<= 1e-6){//如果此时车速为0，还要继续减速的话，就要调转车行进的方向作为车初始化方向
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
	case 'w'://向上平移
		check_W= true;
		break;
	case 's'://向下平移
		check_S=true;
		break;
	case 'a'://向左平移
		check_A = true;
		break;
	case 'd'://向右平移
		check_D = true;
		break;
	case 'q'://视点平移拉近
		check_Q = true;
		break;
	case 'e'://视点平移拉远
		check_E = true;
		break;
	case 'i'://视点向上旋转
		check_I = true;
		break;
	case 'k'://视点向下旋转
		check_K = true;
		break;
	case 'j'://视点向左旋转
		check_J = true;
		break;
	case 'l'://视点向右旋转
		check_L = true;
		break;
	case 'u'://绕z轴正向旋转
		check_U = true;
		break;
	case 'o'://绕z轴负向旋转
		check_O= true;
		break;
	}
}
void updateOperate(){
	bool bChange = false;
	if(check_W){//w
		if(mode==0){//动的是模型
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,-mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else{//动的是摄像机
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
	if(bChange)//计算视点矩阵的逆矩阵
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
	//定义名字路径(0,0,0)
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
		dir.Normalize();//方向
		rotang=acos(dir.x);//dir与（1，0，0)点计算夹角
		if(dir.y<0)rotang=-rotang;
		mat.SetRotateByAxis(rotang,2);//设置为旋转矩阵
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
	if(mode==0)//欧拉角
	{
		glLoadMatrixf(g_EyeMat);
		EyeMat.Set(&g_EyeMat[0]);
		//EyeMat=EyeMat.GetInverse();
	}
	else//自由漫游
	{
		glRotatef(-rz,0,0,1);	
		glRotatef(-rx,1,0,0);
		glRotatef(-ry,0,1,0);
		glTranslatef(-mx,-my,-mz);
		IEyeMat.Set(&g_IEyeMat[0]);
	}
}