#include "Car.h"

Car::Car(void)
{
	g_CarSpeed=0.02f;
	isSlerp=false;
	currentT=0;
	for(int i=1;i<=SLERPNUM;i++)
		slerp_t[i-1]=float(i)/SLERPNUM;
	float _mat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	slerp_cMatrix.Set(&_mat[0]);
}

int checkIndex(int g_CarIndex,int beginIndex,int endIndex){
	int value;
	if(g_CarIndex==endIndex)value=beginIndex+1;
	else if(g_CarIndex+=endIndex)value=beginIndex;
	else value=g_CarIndex+1;
	return value;
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
//这个update主要是操纵npc小车的
void Car::update(MyName myName,int beginIndex,int endIndex){
	float angleChange;//两个向量(g_CarDir,g_CarLastDir)之间需要旋转的角度
	//由于向量没有之间转换成四元数的函数，需要先把向量转化为欧拉角，再转换为四元数进行插值
	int pointNum=endIndex-beginIndex+1;
	CEuler044 currentEuler,lastEuler;
	if(abs(g_CarSpeed)<1e-6)return;//小车速度为0
	if(g_CarSpeed>0){//小车速度大于0时
		
		//g_CarIndex=(g_CarIndex+pointNum)%pointNum;
		if(g_CarIndex>=endIndex)g_CarIndex=beginIndex;
		
		if(g_CarIndex==endIndex-1)//当走到最后一点时，小车回到起点
			g_CarDir=myName.g_pos[beginIndex]-g_CarPos;
		else{
			g_CarDir=myName.g_pos[g_CarIndex+1]-g_CarPos;
		}
		if(g_CarIndex==beginIndex){
			g_CarLastDir=g_CarPos-myName.g_pos[endIndex-1];
		}
		else{
			if(g_CarIndex==beginIndex){
				g_CarLastDir=g_CarPos-myName.g_pos[endIndex];
			}
			else{
				g_CarLastDir=g_CarPos-myName.g_pos[g_CarIndex-1];
			}
		}
			
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
			float leftlen;

			leftlen=(myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-g_CarPos).len();//当位置到下一节点的距离

			if(leftlen>g_CarSpeed){//如果剩余距离大于速度
				g_CarDir=myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*g_CarSpeed+g_CarPos;
			}
			else{//车下一步就要到达下一个节点
				currentT%=SLERPNUM;
				g_CarIndex=g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1;
				float leftlen_Last=g_CarSpeed-leftlen;
				while(leftlen_Last>(myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-myName.g_pos[g_CarIndex]).len()){
					leftlen_Last-=(myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-myName.g_pos[g_CarIndex]).len();
					g_CarIndex=g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1;
				}
				g_CarDir=myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*leftlen_Last+myName.g_pos[g_CarIndex];
			}
		}
	}
	else if(g_CarSpeed<0){
		if(g_CarIndex<=beginIndex)g_CarIndex=endIndex;
		//g_CarIndex=(g_CarIndex+pointNum)%pointNum;
		if(g_CarIndex==endIndex-1){//当走到最后一点时，小车回到起点
			g_CarLastDir=g_CarPos-myName.g_pos[beginIndex];
		}
		else
			g_CarLastDir=g_CarPos-myName.g_pos[g_CarIndex+1];

		if(g_CarIndex==beginIndex){
			g_CarDir=myName.g_pos[endIndex-1]-g_CarPos;
		}
		else
		{
			if(g_CarIndex==beginIndex)
				g_CarDir=myName.g_pos[endIndex]-g_CarPos;
			else
				g_CarDir=myName.g_pos[g_CarIndex-1]-g_CarPos;
		}
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

			float leftlen=(myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-g_CarPos).len();//当位置到下一节点的距离
			if(leftlen>carSpeed){//如果剩余距离大于速度
				g_CarDir=myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*carSpeed+g_CarPos;
			}
			else{//车下一步就要到达下一个节点
				currentT%=SLERPNUM;
				g_CarIndex=g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1;
				float leftlen_Last=carSpeed-leftlen;
				while(leftlen_Last>(myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-myName.g_pos[g_CarIndex]).len()){
					leftlen_Last-=(myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-myName.g_pos[g_CarIndex]).len();
					g_CarIndex=g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1;
				}

				g_CarDir=myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*leftlen_Last+myName.g_pos[g_CarIndex];

			}
		}
	}
	
}
void Car::run(){
	CQuaternion044 slerp_Qua[SLERPNUM];//四元数插值结果
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
				
				glRotatef(angle, 0, 0, 1);
			}	
			else if (g_CarDir.x > 0 && g_CarDir.y < 0) {
				
				glRotatef(-angle, 0, 0, 1);
			}
			else if (g_CarDir.x < 0 && g_CarDir.y >= 0){ 
				
				glRotatef(-angle, 0, 0, 1);
				glRotated(180,0,1,0);//防止小车车顶朝下
			}
			else if (g_CarDir.x < 0 && g_CarDir.y < 0){ 
				
				glRotatef(angle, 0, 0, 1);
				glRotated(180,0,1,0);
			}
		}
		//如果x=0,则旋转90°
		else
		{
			if (g_CarDir.y > 0){
				
				glRotated(90, 0, 0, 1);
			}
			else{
				
				glRotated(-90, 0, 0, 1);		
			}
		}
	}
	DrawCar();
	glPopMatrix();
}
void Car::Set(float g_CarSpeed,int beginIndex,int endIndex){
	this->g_CarSpeed=g_CarSpeed;
	this->beginIndex=beginIndex;
	this->endIndex=endIndex;
}
void Car::DrawCar(){
	glPushMatrix();
	glScalef(0.015f,0.015f,0.015f);
	glRotatef(180,0,1,0);//调转车头的方向朝向x轴正方向
	InitBody();
	InitWheel(wheelAngle*g_CarSpeed);
	glPopMatrix();
}