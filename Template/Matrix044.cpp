#define _CRT_SECURE_NO_WARNINGS
#include "Matrix044.h"

float pi=float(acos(-1.0));
#define FLOAT_EPS 1e-6



CMatrix044::CMatrix044(void)
{
	float *mat = (float*)&m00;
	for(int i=0;i<16;i++){//全部初始化为0
		mat[i]=0;
	}
}


CMatrix044::~CMatrix044(void)
{

}
void CMatrix044::Set(float *p){
	float *mat = (float*)&m00;
	for(int i=0;i<16;i++){
		mat[i]=p[i];
	}
}
CMatrix044& CMatrix044::operator=(const CMatrix044&p){//矩阵赋值
	this->m00=p.m00;
	this->m01=p.m01;
	this->m02=p.m02;
	this->m03=p.m03;
	this->m10=p.m10;
	this->m11=p.m11;
	this->m12=p.m12;
	this->m13=p.m13;
	this->m20=p.m20;
	this->m21=p.m21;
	this->m22=p.m22;
	this->m23=p.m23;
	this->m30=p.m30;
	this->m31=p.m31;
	this->m32=p.m32;
	this->m33=p.m33;
	return *this;
}
CMatrix044 CMatrix044::operator*(float d){//矩阵数乘
	float *mat = (float*)&m00;
	for(int i=0;i<16;i++){
		mat[i]*=d;
	}
	return *this;
}
CMatrix044 CMatrix044::operator/(float d){//矩阵数除
	float *mat = (float*)&m00;
	for(int i=0;i<16;i++){
		mat[i]/=d;
	}
	return *this;
}
CMatrix044 CMatrix044::operator+(CMatrix044&p){//矩阵相加
	float *mat = (float*)&m00;
	for(int i=0;i<16;i++){
		mat[i]+=p[i];
	}
	return *this;
}
CMatrix044 CMatrix044::operator*(CMatrix044&p){//矩阵相乘
	CMatrix044 vec;
	float *mat = (float*)&m00;
	for(int i=0;i<4;i++){
		vec[i]=mat[i]*p[0]+mat[i+4]*p[1]+mat[i+8]*p[2]+mat[i+12]*p[3];
		vec[i+4]=mat[i]*p[4]+mat[i+4]*p[5]+mat[i+8]*p[6]+mat[i+12]*p[7];
		vec[i+8]=mat[i]*p[8]+mat[i+4]*p[9]+mat[i+8]*p[10]+mat[i+12]*p[11];
		vec[i+12]=mat[i]*p[12]+mat[i+4]*p[13]+mat[i+8]*p[14]+mat[i+12]*p[15];
	}
	return vec;
}

CVector044 CMatrix044::MulPosition(CVector044& p){//矩阵乘以位置
	int i;
	CVector044 vec;
	float *mat = (float*)&m00;
	for( i=0;i<3;i++)
	{
		vec[i] = mat[i]*p.x +mat[4+i]*p.y +mat[8+i]*p.z+mat[12+i];
	}
	return vec;
}
CVector044 CMatrix044::MulVector(CVector044& p){//矩阵乘以空间向量
	int i;
	CVector044 vec;
	float *mat = (float*)&m00;
	for( i=0;i<3;i++)
	{
		vec[i] = float(mat[i]*p.x +mat[4+i]*p.y +mat[8+i]*p.z);
	}
	return vec;
}
CMatrix044& CMatrix044::SetRotate(float seta,CVector044&axis){
	axis.getNormalize();
	seta=seta/180*pi;
	m03=m13=m23=m30=m31=m32=0;
	m33=1;
	m00=axis.x*axis.x*(1-cos(seta))+cos(seta);
	m01=axis.x*axis.y*(1-cos(seta))-axis.z*sin(seta);
	m02=axis.x*axis.z*(1-cos(seta))+axis.y*sin(seta);
	m10=axis.x*axis.y*(1-cos(seta))+axis.z*sin(seta);
	m11=axis.y*axis.y*(1-cos(seta))+cos(seta);
	m12=axis.y*axis.z*(1-cos(seta))-axis.x*sin(seta);
	m20=axis.x*axis.z*(1-cos(seta))-axis.y*sin(seta);
	m21=axis.y*axis.z*(1-cos(seta))+axis.x*sin(seta);
	m22=axis.z*axis.z*(1-cos(seta))+cos(seta);
	return *this;
}
CMatrix044& CMatrix044::SetRotateByAxis(float seta,int axis){
	float c = cos(seta);
	float s = sin(seta);
	if(axis==0)
	{
		m00=1;m01=0;m02=0;m03=0;
		m10=0;m11=c;m12=-s;m13=0;
		m20=0;m21=s;m22=c;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	else if(axis==1)
	{
		m00=c;m01=0;m02=s;m03=0;
		m10=0;m11=1;m12=0;m13=0;
		m20=-s;m21=0;m22=c;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	else
	{
		m00=c;m01=-s;m02=0;m03=0;
		m10=s;m11=c;m12=0;m13=0;
		m20=0;m21=0;m22=1;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	return *this;
}
CMatrix044& CMatrix044::SetTrans(CVector044&trans){
	m00=m11=m22=m33=1;
	m03=trans.x;
	m13=trans.y;
	m23=trans.z;
	return *this;
}
CMatrix044& CMatrix044::SetScale(CVector044&p){
	m00=p.x;
	m11=p.y;
	m22=p.z;
	m33=1;
	return *this;
}
float CMatrix044::Determinant(){//求行列式
	float result=0;
	CVector044 a=CVector044(m10,m20,m30);
	CVector044 b=CVector044(m11,m21,m31);
	CVector044 c=CVector044(m12,m22,m32);
	CVector044 d=CVector044(m13,m23,m33);
	float p1=(b.crossMul(c)).dotMul(d);
	float p2=(a.crossMul(c)).dotMul(d);
	float p3=(a.crossMul(b)).dotMul(d);
	float p4=(a.crossMul(b)).dotMul(c);
	return result=m00*p1-m01*p2+m02*p3-m03*p4;
}
CMatrix044 CMatrix044::Adjoint(){//求伴随矩阵
	CVector044 v[16];
	float *mat = (float*)&m00;
	for(int i=0;i<16;i+=4){
		v[i].Set(mat[i],mat[i+1],mat[i+2]);
		v[i+1].Set(mat[i],mat[i+1],mat[i+3]);
		v[i+2].Set(mat[i],mat[i+2],mat[i+3]);
		v[i+3].Set(mat[i+1],mat[i+2],mat[i+3]);
	}
	CMatrix044 vec;
	vec[0]=(v[7].crossMul(v[11])).dotMul(v[15]);
	vec[4]=-(v[6].crossMul(v[10])).dotMul(v[14]);
	vec[8]=(v[5].crossMul(v[9])).dotMul(v[13]);
	vec[12]=-(v[4].crossMul(v[8])).dotMul(v[12]);

	vec[1]=-(v[3].crossMul(v[11])).dotMul(v[15]);
	vec[5]=(v[2].crossMul(v[10])).dotMul(v[14]);
	vec[9]=-(v[1].crossMul(v[9])).dotMul(v[13]);
	vec[13]=(v[0].crossMul(v[8])).dotMul(v[12]);

	vec[2]=(v[3].crossMul(v[7])).dotMul(v[15]);
	vec[6]=-(v[2].crossMul(v[6])).dotMul(v[14]);
	vec[10]=(v[1].crossMul(v[5])).dotMul(v[13]);
	vec[14]=-(v[0].crossMul(v[4])).dotMul(v[12]);

	vec[3]=-(v[3].crossMul(v[7])).dotMul(v[11]);
	vec[7]=(v[2].crossMul(v[6])).dotMul(v[10]);
	vec[11]=-(v[1].crossMul(v[5])).dotMul(v[9]);
	vec[15]=(v[0].crossMul(v[4])).dotMul(v[8]);

	return vec;
}
float CMatrix044::Inverse(){
	float res=Determinant();
	if(res!=0)
		return res;
	else 
		return 0;
}
CMatrix044 CMatrix044::GetInverse(){
	return Adjoint()/Determinant();
}

void CMatrix044::split(char *buffer,float *a){
	const char *sep=", '\t'";
	char *p;
	p=strtok(buffer,sep);
	int len=0;
	while(p){
		a[len]=float(atof(p));
		p=strtok(NULL,sep);
		len++;
	}
}
CEuler044 CMatrix044::ToEuler(){
	CEuler044 eul;
	eul.h=valToDegree(atan(m02/m22));
	eul.p=valToDegree(asin(-m12));
	eul.b=valToDegree(atan(m10/m11));
	return eul;
}
CQuaternion044 CMatrix044::ToQuaternion(){
	CQuaternion044 res;
	res.w=sqrt(m00+m11+m22+1)/2;
	res.x=-(m12-m21)/(4*res.w);
	res.y=-(m20-m02)/(4*res.w);
	res.z=-(m01-m10)/(4*res.w);
	return res;
}
void CMatrix044::MyMatrix(){
	char *txt[]={"矩阵相加","矩阵相乘","矩阵数乘","矩阵乘向量","矩阵乘位置","矩阵设置旋转",
		"矩阵设置平移","矩阵设置缩放","矩阵求逆"};
	char buffer[256];
	float a[32]={0};
	int len=0;
	CVector044 cVector044;
	CMatrix044 cMatrix044;
	CMatrix044 cMatrix044_1;

	ifstream testFile;
	testFile.open("test.txt");
	ofstream outFile;
	outFile.open("out.txt");
	if(!testFile.is_open()|!outFile.is_open()){
		cout<<"Error opening file";
		exit(1);
	}
	while(!testFile.eof()){
		testFile.getline(buffer,50);
		if(strcmp(buffer,txt[0])==0){//矩阵相加
			outFile<<"矩阵相加"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CMatrix044 cMatrix044;
			CMatrix044 cMatrix044_1;
			cMatrix044.Set(&a[0]);
			cMatrix044_1.Set(&a[16]);
			float* flo((cMatrix044+cMatrix044_1));
			for(int i=0;i<32;i++){
				if(i==16) outFile<<"\t";
				outFile<<fixed<<setprecision(2)<<a[i];
				if(i!=15&&i!=31) outFile<<",";
			}
			outFile<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[1])==0){//矩阵相乘
			outFile<<"矩阵相乘"<<endl;

			testFile.getline(buffer,256);
			split(buffer,a);
			CMatrix044 cMatrix044;
			CMatrix044 cMatrix044_1;
			cMatrix044.Set(&a[0]);
			cMatrix044_1.Set(&a[16]);
			float* flo((cMatrix044*cMatrix044_1));
			for(int i=0;i<32;i++){
				if(i==16) outFile<<"\t";
				outFile<<fixed<<setprecision(2)<<a[i];
				if(i!=15&&i!=31) outFile<<",";
			}
			outFile<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[2])==0){//矩阵数乘
			outFile<<"矩阵数乘"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CMatrix044 cMatrix044;
			cMatrix044.Set(&a[0]);
			float* flo(cMatrix044*a[16]);
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<a[i];
				if(i!=15) outFile<<",";
			}
			outFile<<fixed<<setprecision(2)<<"\t"<<a[16]<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[3])==0){//矩阵乘向量
			outFile<<"矩阵乘向量"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CVector044 cVector044;
			CMatrix044 cMatrix044;
			cMatrix044.Set(&a[0]);
			cVector044.Set(a[16],a[17],a[18]);

			float* flo((cMatrix044.MulVector(cVector044)));
			for(int i=0;i<19;i++){
				if(i==16) outFile<<"\t";
				outFile<<fixed<<setprecision(2)<<a[i];
				if(i!=15&&i!=18) outFile<<",";
			}
			outFile<<"\t";
			for(int i=0;i<3;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=2) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[4])==0){//矩阵乘位置
			outFile<<"矩阵乘位置"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CVector044 cVector044;
			CMatrix044 cMatrix044;
			cMatrix044.Set(&a[0]);
			cVector044.Set(a[16],a[17],a[18]);

			float* flo((cMatrix044.MulPosition(cVector044)));
			for(int i=0;i<19;i++){
				if(i==16) outFile<<"\t";
				outFile<<fixed<<setprecision(2)<<a[i];
				if(i!=15&&i!=18) outFile<<",";
			}
			outFile<<"\t";
			for(int i=0;i<3;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=2) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[5])==0){//矩阵设置旋转
			outFile<<"矩阵设置旋转"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CVector044 cVector044;
			CMatrix044 cMatrix044;

			cVector044.Set(a[1],a[2],a[3]);
			float* flo(cMatrix044.SetRotate(a[0],cVector044));
			outFile<<fixed<<setprecision(2)<<
				a[0]<<"\t"<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[6])==0){//矩阵设置平移
			outFile<<"矩阵设置平移"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CVector044 cVector044;
			CMatrix044 cMatrix044;
			cVector044.Set(a[0],a[1],a[2]);
			float* flo(cMatrix044.SetTrans(cVector044));
			outFile<<fixed<<setprecision(2)<<
				a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[7])==0){//矩阵设置缩放
			outFile<<"矩阵设置缩放"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CVector044 cVector044;
			CMatrix044 cMatrix044;
			cVector044.Set(a[0],a[1],a[2]);
			float* flo(cMatrix044.SetScale(cVector044));
			outFile<<fixed<<setprecision(2)<<
				a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[8])==0){//矩阵求逆
			outFile<<"矩阵求逆"<<endl;
			testFile.getline(buffer,256);
			split(buffer,a);
			CMatrix044 cMatrix044;
			cMatrix044.Set(&a[0]);
			float flag=cMatrix044.Inverse();
			if(fabs(flag)<= FLOAT_EPS){//没有逆矩阵
				for(int i=0;i<16;i++){
					outFile<<fixed<<setprecision(2)<<a[i];
					if(i!=15) outFile<<",";
				}
				outFile<<"\t";
				outFile<<fixed<<setprecision(2)<<0<<endl;
			}
			else{//有逆矩阵
				cMatrix044.Set(&a[0]);
				float* flo(cMatrix044.GetInverse());
				for(int i=0;i<16;i++){
					outFile<<fixed<<setprecision(2)<<a[i];
					if(i!=15) outFile<<",";
				}
				outFile<<"\t";
				for(int i=0;i<16;i++){
					if( fabs(flo[i])<= FLOAT_EPS){
						flo[i]=0;
					}
					outFile<<fixed<<setprecision(2)<<flo[i];
					if(i!=15) outFile<<",";
				}
				outFile<<endl;
			}
		}
	}
	testFile.close();
	outFile.close();
}

