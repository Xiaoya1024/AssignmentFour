#include "MyName.h"
#include <gl\glut.h>
MyName::MyName(void)
{
	int _point[23]={15,22,31,38,47,54,63,74,79,89,93,97,106,121,
		129,137,146,161,174,188,202,208,214};
	for(int i=0;i<23;i++)
		point[i]=_point[i];
}
MyName::~MyName(void)
{

}

void MyName::pointJi(){
	for(float i=-0.4f;i<=0.4f;i+=0.05f)//第1画-17
		Ji.push_back(Point(i,0.2f));
	for(float j=0.4f;j>=0.05f;j-=0.05f)//第2画-8
		Ji.push_back(Point(0.0f,j));

	for(float i=-0.2f;i<=0.2f;i+=0.05f){//第3画-9
		Ji.push_back(Point(i,0.05f));
	}
	for(float j=-0.05f;j>=-0.4f;j-=0.05f){//第4画-8
		Ji.push_back(Point(-0.2f,j));
	}
	for(float i=-0.2f;i<=0.2f;i+=0.05f){//第5画-9
		Ji.push_back(Point(i,-0.05f));
	}
	for(float j=-0.05f;j>=-0.4f;j-=0.05f){//第6画-8
		Ji.push_back(Point(0.2f,j));
	}
	for(float i=-0.2f;i<=0.2f;i+=0.05f){//第7画-9
		Ji.push_back(Point(i,-0.4f));
	}
	JiNum=Ji.size();

}
void MyName::pointJiAll(){
	for(unsigned int i=0;i<Ji.size();i++){
		for(float k=-0.1f;k<=0.1f;k+=0.05f){
			JiAll.push_back(Point(Ji[i].x,Ji[i].y,k));
		}
	}
}
void MyName::pointXiao(){
	for(float j=0.25f;j>=-0.25f;j-=0.05f)
		Xiao.push_back(Point(-0.4f,j));//1-11
	for(float i=-0.4f;i<=-0.2f;i+=0.05f)
		Xiao.push_back(Point(i,0.25f));//2-5
	for(float j=0.25f;j>=-0.25f;j-=0.05f)
		Xiao.push_back(Point(-0.2f,j));//3-11
	for(float i=-0.4f;i<=-0.2f;i+=0.05f)
		Xiao.push_back(Point(i,0.0f));//4-5
	for(float i=-0.4f;i<=-0.2f;i+=0.05f)
		Xiao.push_back(Point(i,-0.25f));//5-5
	for(float i=-0.15f;i<=0.25f;i+=0.05f)
		Xiao.push_back(Point(i,0.25f));//6-9

	for(float j=0.4f;j>=0.2f;j-=0.05f)//7-16
		Xiao.push_back(Point(0.0f,j));
	Xiao.push_back(Point(0.03f,0.17f));
	Xiao.push_back(Point(0.06f,0.14f));
	Xiao.push_back(Point(0.1f,0.1f));
	Xiao.push_back(Point(0.15f,0.06f));
	Xiao.push_back(Point(0.2f,0.03f));
	Xiao.push_back(Point(0.25f,0.0f));
	Xiao.push_back(Point(0.3f,-0.03f));
	Xiao.push_back(Point(0.35f,-0.05f));
	Xiao.push_back(Point(0.4f,-0.05f));
	Xiao.push_back(Point(0.35f,0.0f));
	Xiao.push_back(Point(0.32f,0.02f));

	Xiao.push_back(Point(0.24f,0.17f));//8-8
	Xiao.push_back(Point(0.22f,0.14f));
	Xiao.push_back(Point(0.2f,0.1f));
	Xiao.push_back(Point(0.17f,0.08f));
	Xiao.push_back(Point(0.13f,0.05f));
	Xiao.push_back(Point(0.1f,0.03f));
	Xiao.push_back(Point(0.07f,0.0f));
	Xiao.push_back(Point(0.04f,-0.02f));

	for(float i=-0.1f;i<=0.25f;i+=0.05f)
		Xiao.push_back(Point(i,-0.1f));//9-8

	Xiao.push_back(Point(-0.01f,-0.15f));//10-9
	Xiao.push_back(Point(-0.02f,-0.2f));
	Xiao.push_back(Point(-0.03f,-0.24f));
	Xiao.push_back(Point(-0.05f,-0.28f));
	Xiao.push_back(Point(-0.07f,-0.3f));
	Xiao.push_back(Point(-0.1f,-0.33f));
	Xiao.push_back(Point(-0.13f,-0.36f));
	Xiao.push_back(Point(-0.16f,-0.38f));
	Xiao.push_back(Point(-0.2f,-0.4f));

	for(float j=-0.1f;j>=-0.35f;j-=0.05f)//11-16
		Xiao.push_back(Point(0.1f,j));
	Xiao.push_back(Point(0.12f,-0.33f));
	Xiao.push_back(Point(0.14f,-0.35f));
	Xiao.push_back(Point(0.17f,-0.38f));
	Xiao.push_back(Point(0.2f,-0.4f));
	Xiao.push_back(Point(0.25f,-0.4f));
	Xiao.push_back(Point(0.3f,-0.4f));
	Xiao.push_back(Point(0.35f,-0.4f));
	Xiao.push_back(Point(0.4f,-0.38f));
	Xiao.push_back(Point(0.38f,-0.35f));
	Xiao.push_back(Point(0.36f,-0.3f));
	XiaoNum=Xiao.size();
}
void MyName::pointXiaoAll(){
	for(unsigned int i=0;i<Xiao.size();i++){
		for(float k=-0.1f;k<=0.1f;k+=0.05f){
			XiaoAll.push_back(Point(Xiao[i].x,Xiao[i].y,k));
		}
	}
}
void MyName::pointYa(){
	for(float i=-0.3f;i<=0.3f;i+=0.05f)//第1画-13
		Ya.push_back(Point(i,0.3f));
	for(float j=0.3f;j>-0.4f;j-=0.05f)//第2画-15
		Ya.push_back(Point(-0.1f,j));
	for(float j=0.3f;j>-0.4f;j-=0.05f)//第3画-15
		Ya.push_back(Point(0.1f,j));

	Ya.push_back(Point(-0.3f,0.2f));//第4画-6
	Ya.push_back(Point(-0.26f,0.14f));
	Ya.push_back(Point(-0.23f,0.1f));
	Ya.push_back(Point(-0.2f,0.04f));
	Ya.push_back(Point(-0.17f,0.0f));
	Ya.push_back(Point(-0.15f,-0.05f));

	Ya.push_back(Point(0.3f,0.2f));//第5画-6
	Ya.push_back(Point(0.26f,0.14f));
	Ya.push_back(Point(0.23f,0.1f));
	Ya.push_back(Point(0.2f,0.04f));
	Ya.push_back(Point(0.17f,0.0f));
	Ya.push_back(Point(0.15f,-0.05f));

	for(float i=-0.4f;i<=0.4f;i+=0.05f)//第6画-17
		Ya.push_back(Point(i,-0.4f));
	YaNum=Ya.size();

}
void MyName::pointYaAll(){
	for(unsigned int i=0;i<Ya.size();i++){
		for(float k=-0.1f;k<=0.1f;k+=0.05f){
			YaAll.push_back(Point(Ya[i].x,Ya[i].y,k));
		}
	}
}
void MyName::DrawName(int type){//type为0表示是圆圈模式，为1表示是三角面片模式
	if(type==0){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glColor3f(0.5,0.4,0.1);
		for(int i=0;i<JiNum+XiaoNum+YaNum;i++){
			glBegin(GL_LINE_STRIP);	
			for(int j=0;j<CIRCLENUM;j++)
				glVertex3fv(g_allPos[i*CIRCLENUM+j]);
			glEnd();
		}
	}
	else if(type==1){

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
void MyName::InitName(){
	pointJi();
	pointXiao();
	pointYa();
	for(int i=0;i<CIRCLENUM;i++){
		float angle=i*2*3.14/(CIRCLENUM-1);
		g_circle[i].x=0;
		g_circle[i].y=1.2f*cos(angle);
		g_circle[i].z=1.2f*sin(angle);
	}
	int cnt=0;
	int scale=25;
	for(int i=0;i<JiNum;i++){
		Ji[i].x-=1.0f;
		g_pos[cnt].x=Ji[i].x*scale;
		g_pos[cnt].y=Ji[i].y*scale;
		g_pos[cnt++].z=Ji[i].z;
	}
	for(int i=0;i<XiaoNum;i++){
		g_pos[cnt].x=Xiao[i].x*scale;
		g_pos[cnt].y=Xiao[i].y*scale;
		g_pos[cnt++].z=Xiao[i].z;
	}
	for(int i=0;i<YaNum;i++){
		Ya[i].x+=1.0f;
		g_pos[cnt].x=Ya[i].x*scale;
		g_pos[cnt].y=Ya[i].y*scale;
		g_pos[cnt++].z=Ya[i].z;
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
}