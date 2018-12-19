#include "Vector044.h"

CVector044::CVector044()
{
	x=0.0f;
	y=0.0f;
	z=0.0f;
}
CVector044::CVector044(float x,float y,float z){
	this->x=x;
	this->y=y;
	this->z=z;
}
CVector044::CVector044(const CVector044 &n){
	this->x=n.x;
	this->y=n.y;
	this->z=n.z;
}


void CVector044::Set(float x,float y,float z){
	this->x=x;
	this->y=y;
	this->z=z;
}

//���������+
CVector044 CVector044::operator+(CVector044 &p){
	return CVector044(x+p.x,y+p.y,z+p.z);
}

//���������-
CVector044 CVector044::operator-(CVector044 &p){
	return CVector044(x-p.x,y-p.y,z-p.z);
}

//���������*
CVector044 CVector044::operator*(float p){
	return CVector044(x*p,y*p,z*p);
}
//���������=
CVector044& CVector044::operator=(CVector044 &p){
	x=p.x;y=p.y;z=p.z;
	return *this;
}
//���������==
bool CVector044::operator==(CVector044 &p){
	if(x==p.x&&y==p.y&&z==p.z){
		return true;
	}
	return false;
}
bool CVector044::operator!=(CVector044 &p){
	return !((*this)==p);
}

//������˲���
float CVector044::dotMul(CVector044 &n){
	return x*n.x+y*n.y+z*n.z;
}

//������˲���
CVector044 CVector044::crossMul(CVector044 &n){
	return CVector044(y*n.z-z*n.y,z*n.x-x*n.z,x*n.y-y*n.x);
}

//������׼��
void CVector044::Normalize(){
	float len=this->len();
	if(len==1||len==0){
		return;
	}
	x=x/len;
	y=y/len;
	z=z/len;
}

//��ȡ��׼�����
CVector044 CVector044::getNormalize(){
	this->Normalize();
	return *this;
}

//����������ģ
float CVector044::len(){
	return sqrtf((x*x)+(y*y)+(z*z));
}

CVector044 CVector044::project(CVector044 &n){//����ͶӰ����
	float uv=(this->dotMul(n))/((n.x*n.x)+(n.y*n.y)+(n.z*n.z));
	return CVector044(uv*n.x,uv*n.y,uv*n.z);
}

float CVector044::findSeta(CVector044&p){//����������֮��ļн�
	float res=this->dotMul(p);
	float a1=this->len();
	float a2=p.len();
	return acosf(res/(a1*a2));//���ص���һ������
}
CVector044 CVector044::rotateByZ(float angle){
	CVector044 res;
	res.z=this->z;
	float _angle=degreeToVal(angle);
	res.x=this->x*cos(_angle)-this->y*sin(_angle);
	res.y=this->x*sin(_angle)+this->y*cos(_angle);
	return res;
}
CVector044 CVector044::lerp(CVector044&Vend,float t){
	CVector044 a=*this;
	//a=this->getNormalize();
//	Vend.Normalize();
	return a*(1-t)+Vend*t;
}
void CVector044::lerp(CVector044&Vend,int n,float*t,CVector044*Result){
	for(int i=0;i<n;i++){
		Result[i]=lerp(Vend,t[i]);
	}
}
CEuler044 CVector044::ToEuler(){//ת��Ϊŷ����
	float len=this->len();
	float temp=y/len;
	if(temp>1){
		temp=1;
	}
	else if(temp<-1){
		temp=-1;
	}
	float angle=valToDegree(atan2(-x,-z));
	float ph=valToDegree(acos(temp));
	CEuler044 ceuler;
	ceuler.Set(angle,90-ph,0);
	ceuler.eulerNormal();
	return ceuler;
}
