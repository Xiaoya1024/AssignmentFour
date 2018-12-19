#include "MyName.h"
MyName::MyName(void)
{
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

}
void MyName::pointYaAll(){
	for(unsigned int i=0;i<Ya.size();i++){
		for(float k=-0.1f;k<=0.1f;k+=0.05f){
			YaAll.push_back(Point(Ya[i].x,Ya[i].y,k));
		}
	}
}
