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

	//���°벿  
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
	//���ϰ벿  
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

	//��β

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
	//����  
	glColor3f(0, 0, 0);
	//glPointSize(10);
	//ǰ����
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

	//ǰ�ҳ���
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

	//���ҳ���
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


	//������
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
//���update��Ҫ�ǲ���npcС����
void Car::update(MyName myName,int beginIndex,int endIndex){
	float angleChange;//��������(g_CarDir,g_CarLastDir)֮����Ҫ��ת�ĽǶ�
	//��������û��֮��ת������Ԫ���ĺ�������Ҫ�Ȱ�����ת��Ϊŷ���ǣ���ת��Ϊ��Ԫ�����в�ֵ
	int pointNum=endIndex-beginIndex+1;
	CEuler044 currentEuler,lastEuler;
	if(abs(g_CarSpeed)<1e-6)return;//С���ٶ�Ϊ0
	if(g_CarSpeed>0){//С���ٶȴ���0ʱ
		
		//g_CarIndex=(g_CarIndex+pointNum)%pointNum;
		if(g_CarIndex>=endIndex)g_CarIndex=beginIndex;
		
		if(g_CarIndex==endIndex-1)//���ߵ����һ��ʱ��С���ص����
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
			float leftlen;

			leftlen=(myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-g_CarPos).len();//��λ�õ���һ�ڵ�ľ���

			if(leftlen>g_CarSpeed){//���ʣ���������ٶ�
				g_CarDir=myName.g_pos[g_CarIndex+1==endIndex?beginIndex:g_CarIndex+1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*g_CarSpeed+g_CarPos;
			}
			else{//����һ����Ҫ������һ���ڵ�
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
		if(g_CarIndex==endIndex-1){//���ߵ����һ��ʱ��С���ص����
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

			float leftlen=(myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-g_CarPos).len();//��λ�õ���һ�ڵ�ľ���
			if(leftlen>carSpeed){//���ʣ���������ٶ�
				g_CarDir=myName.g_pos[g_CarIndex-1==beginIndex?endIndex:g_CarIndex-1]-myName.g_pos[g_CarIndex];
				g_CarDir.Normalize();
				g_CarPos=g_CarDir*carSpeed+g_CarPos;
			}
			else{//����һ����Ҫ������һ���ڵ�
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
	CQuaternion044 slerp_Qua[SLERPNUM];//��Ԫ����ֵ���
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
				
				glRotatef(angle, 0, 0, 1);
			}	
			else if (g_CarDir.x > 0 && g_CarDir.y < 0) {
				
				glRotatef(-angle, 0, 0, 1);
			}
			else if (g_CarDir.x < 0 && g_CarDir.y >= 0){ 
				
				glRotatef(-angle, 0, 0, 1);
				glRotated(180,0,1,0);//��ֹС����������
			}
			else if (g_CarDir.x < 0 && g_CarDir.y < 0){ 
				
				glRotatef(angle, 0, 0, 1);
				glRotated(180,0,1,0);
			}
		}
		//���x=0,����ת90��
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
	glRotatef(180,0,1,0);//��ת��ͷ�ķ�����x��������
	InitBody();
	InitWheel(wheelAngle*g_CarSpeed);
	glPopMatrix();
}