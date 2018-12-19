#define _CRT_SECURE_NO_WARNINGS
#include "Quaternion044.h"

CQuaternion044::CQuaternion044(void)
{
}


CQuaternion044::~CQuaternion044(void)
{
}
void CQuaternion044::Set(float x,float y,float z,float w){
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}
CEuler044 CQuaternion044::ToEuler(){
	CEuler044 res;
	res.p=valToDegree(asin(2*w*x-2*y*z));
	if(fabs(cos(degreeToVal(res.p)))<=1e-6)
		res.h=valToDegree(atan((2*w*y-2*z*x)/(1-2*y*y-2*z*z)));
	else
		res.h=valToDegree(atan((2*z*x+2*w*y)/(1-2*x*x-2*y*y)));
	if(fabs(cos(degreeToVal(res.p)))<=1e-6)
		res.b=0;
	else
		res.b=valToDegree(atan((2*x*y+2*w*z)/(1-2*z*z-2*x*x)));
	return res;
}
CMatrix044 CQuaternion044::ToMatrix(){
	CMatrix044 mat;
	mat.m00=1-2*y*y-2*z*z;
	mat.m01=2*x*y-2*w*z;
	mat.m02=2*x*z+2*w*y;
	mat.m03=0;
	mat.m10=2*x*y+2*w*z;
	mat.m11=1-2*x*x-2*z*z;
	mat.m12=2*y*z-2*w*x;
	mat.m13=0;
	mat.m20=2*x*z-2*w*y;
	mat.m21=2*y*z+2*w*x;
	mat.m22=1-2*x*x-2*y*y;
	mat.m23=0;
	mat.m30=0;
	mat.m31=0;
	mat.m32=0;
	mat.m33=1;
	return mat;
}

void CQuaternion044::SetAngle(float angle,CVector044 axis){
	w = (float)(cos((angle / 2)*PI / 180));
	x = (float)(axis.x*sin((angle / 2)*PI / 180));
	y = (float)(axis.y*sin((angle / 2)*PI / 180));
	z = (float)(axis.z*sin((angle / 2)*PI / 180));
}
void CQuaternion044::GetAngle(float&angle,CVector044&axis){
	CQuaternion044 res;
	res=*this;
	res.Normalize();
	angle=(float)(2*valToDegree(acos(res.w)));
	axis.x=(float)(res.x/sin((angle/2)*PI/180));
	axis.y=(float)(res.y/sin((angle/2)*PI/180));
	axis.z=(float)(res.z/sin((angle/2)*PI/180));
}
CQuaternion044& CQuaternion044::operator=(const CQuaternion044&p){
	x=p.x;
	y=p.y;
	z=p.z;
	w=p.w;
	return *this;
}
CQuaternion044 CQuaternion044::operator+(const CQuaternion044&p){
	CQuaternion044 res;
	res.x=x+p.x;
	res.y=y+p.y;
	res.z=z+p.z;
	res.w=w+p.w;
	return res;
}
CQuaternion044 CQuaternion044::operator*(float data){
	CQuaternion044 res;
	res.x=x*data;
	res.y=y*data;
	res.z=z*data;
	res.w=w*data;
	return res;
}
CQuaternion044 CQuaternion044::operator*(const CQuaternion044&p){
	CQuaternion044 res;
	res.w = w * p.w - x * p.x - y * p.y - z * p.z;
	res.x = w * p.x + x * p.w - y * p.z + z * p.y;
	res.y = w * p.y + y * p.w - z * p.x + x * p.z;
	res.z = w * p.z + z * p.w - x * p.y + y * p.x;
	return res;
}
CQuaternion044 CQuaternion044::operator-(const CQuaternion044&p){
	CQuaternion044 res;
	res.x=x-p.x;
	res.y=y-p.y;
	res.z=z-p.z;
	res.w=w-p.w;
	return res;
}
CQuaternion044 CQuaternion044::operator-(){
	CQuaternion044 res;
	res.x=-x;
	res.y=-y;
	res.z=-z;
	res.w=-w;
	return res;
}
float CQuaternion044::dotMul(const CQuaternion044&p){
	float res;
	res=x*p.x+y*p.y+z*p.z+w*p.w;
	return res;
}
float CQuaternion044::len(){
	return sqrtf(x*x+y*y+z*z+w*w);
}
bool CQuaternion044::Normalize(){
	float length=len();
	if(fabs(length)<=1e-6)return false;
	x=x/length;
	y=y/length;
	z=z/length;
	w=w/length;
	return true;
}
CQuaternion044& CQuaternion044::Inverse(){
	float length=len();
	if(fabs(length)<=1e-6)
		length=1;
	w=w/length/length;
	x=-x/length/length;
	y=-y/length/length;
	z=-z/length/length;
	return *this;
}
CQuaternion044 CQuaternion044::GetInverse(){
	CQuaternion044 res;
	float length=len();
	if(fabs(length)<=1e-6)
		length=1;
	res.w=w/length/length;
	res.x=-x/length/length;
	res.y=-y/length/length;
	res.z=-z/length/length;
	return res;
}
CQuaternion044 CQuaternion044::Div(const CQuaternion044&b){
	CQuaternion044 inv,res;
	inv=this->GetInverse();
	res=inv*b;
	return res;
}
CQuaternion044 CQuaternion044::Slerp(CQuaternion044&Vend,float t){
	this->Normalize();
	Vend.Normalize();
	float v=this->dotMul(Vend);
	if(v<0){
		Vend=-Vend;
		v=-v;
	}
	float k0,k1;
	if(v>0.9995f){
		k0=1-t;
		k1=t;
	}
	else{
		float v1=sqrtf(1.0f-v*v);
		float v2=atan2(v1,v);
		k0=sin((1.0f-t)*v2)/v1;
		k1=sin(t*v2)/v1;
	}
	return (*this)*k0+Vend*k1;

}
void CQuaternion044::Slerp(CQuaternion044&Vend,int n,float*t,CQuaternion044 *Result){
	for(int i=0;i<n;i++){
		Result[i]=Slerp(Vend,t[i]);
	}
}
void CQuaternion044::split(char *buffer,float*a){
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
void CQuaternion044::myQuaternionPrint(){
	char *txt[]={
		"欧拉角转换向量",
		"向量转换欧拉角",
		"欧拉角转换四元数",
		"四元数转换欧拉角",
		"欧拉角转换矩阵",
		"矩阵转换欧拉角",
		"矩阵转换四元数",
		"四元数转换矩阵",
		"欧拉角标准化",
		"四元数单位化",
		"四元数相乘",
		"四元数求差",
		"四元数点乘",
		"四元数求逆",
		"四元数求角度和旋转轴",
		"四元数插值"
	};
	char buffer[256];

	ifstream testFile;
	testFile.open("test.txt");
	ofstream outFile;
	outFile.open("out.txt");
	if(!testFile.is_open()||!outFile.is_open()){
		cout<<"Error opening file";
		exit(1);
	}
	while(!testFile.eof()){
		testFile.getline(buffer,50);
		if (strcmp(buffer,txt[0])==0){//欧拉角转换向量
			outFile<<"欧拉角转换向量"<<endl;
			testFile.getline(buffer,256);
			float a[3]={0};
			split(buffer,a);
			CEuler044 cEuler;
			CVector044 cVector,updir;
			cEuler.Set(a[0],a[1],a[2]);
			cVector=cEuler.ToVector3(&updir);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cVector.x<<","<<cVector.y<<","<<cVector.z<<"\t"<<
				updir.x<<","<<updir.y<<","<<updir.z<<endl;
		}
		else if(strcmp(buffer,txt[1])==0){//向量转换欧拉角
			outFile<<"向量转换欧拉角"<<endl;
			testFile.getline(buffer,256);
			float a[3]={0};
			split(buffer,a);
			CVector044 cVector;
			CEuler044 cEuler;
			cVector.Set(a[0],a[1],a[2]);
			cEuler=cVector.ToEuler();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cEuler.h<<","<<cEuler.p<<","<<cEuler.b<<endl;
		}
		else if(strcmp(buffer,txt[2])==0){//欧拉角转换四元数
			outFile<<"欧拉角转换四元数"<<endl;
			testFile.getline(buffer,256);
			float a[3]={0};
			split(buffer,a);
			CEuler044 cEuler;
			CQuaternion044 cQuaternion;
			cEuler.Set(a[0],a[1],a[2]);
			cQuaternion=cEuler.ToQuaternion();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion.x<<","<<cQuaternion.y<<","<<cQuaternion.z<<","
				<<cQuaternion.w<<endl;
		}
		else if(strcmp(buffer,txt[3])==0){
			outFile<<"四元数转换欧拉角"<<endl;//四元数转换欧拉角
			testFile.getline(buffer,256);
			float a[4]={0};
			split(buffer,a);
			CEuler044 cEuler;
			CQuaternion044 cQuaternion;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cEuler=cQuaternion.ToEuler();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cEuler.h<<","<<cEuler.p<<","<<cEuler.b<<endl;
		}
		else if(strcmp(buffer,txt[4])==0){//欧拉角转换矩阵
			outFile<<"欧拉角转换矩阵"<<endl;
			testFile.getline(buffer,256);
			float a[3]={0};
			split(buffer,a);
			CEuler044 cEuler;
			CMatrix044 cMatrix;
			cEuler.Set(a[0],a[1],a[2]);
			cMatrix=cEuler.ToMatrix();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			float* flo(cMatrix);
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15) outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[5])==0){//矩阵转换欧拉角
			outFile<<"矩阵转换欧拉角"<<endl;
			testFile.getline(buffer,256);
			float a[16]={0};
			split(buffer,a);
			CEuler044 cEuler;
			CMatrix044 cMatrix;
			cMatrix.Set(&a[0]);
			cEuler=cMatrix.ToEuler();
			for(int i=0;i<16;i++){
				outFile<<a[i];
				if(i!=15)outFile<<",";
			}
			outFile<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cEuler.h<<","<<cEuler.p<<","<<cEuler.b<<endl;
		}
		else if(strcmp(buffer,txt[6])==0){//矩阵转换四元数
			outFile<<"矩阵转换四元数"<<endl;
			testFile.getline(buffer,256);
			float a[16]={0};
			split(buffer,a);
			CMatrix044 cMatrix;
			CQuaternion044 cQuaternion;
			cMatrix.Set(&a[0]);
			cQuaternion=cMatrix.ToQuaternion();
			for(int i=0;i<16;i++){
				outFile<<a[i];
				if(i!=15)outFile<<",";
			}
			outFile<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion.x<<","<<cQuaternion.y<<","<<cQuaternion.z<<","<<
				cQuaternion.w<<endl;
		}
		else if(strcmp(buffer,txt[7])==0){//四元数转换矩阵
			outFile<<"四元数转换矩阵"<<endl;
			testFile.getline(buffer,256);
			float a[4]={0};
			split(buffer,a);
			CMatrix044 cMatrix;
			CQuaternion044 cQuaternion;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cMatrix=cQuaternion.ToMatrix();
			float* flo(cMatrix);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			for(int i=0;i<16;i++){
				outFile<<fixed<<setprecision(2)<<flo[i];
				if(i!=15)outFile<<",";
			}
			outFile<<endl;
		}
		else if(strcmp(buffer,txt[8])==0){//欧拉角标准化
			outFile<<"欧拉角标准化"<<endl;
			testFile.getline(buffer,256);
			float a[3]={0};
			split(buffer,a);
			CEuler044 cEuler;
			cEuler.Set(a[0],a[1],a[2]);
			cEuler.eulerNormal();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cEuler.h<<","<<cEuler.p<<","<<cEuler.b<<endl;
		}
		else if(strcmp(buffer,txt[9])==0){//四元数单位化
			outFile<<"四元数单位化"<<endl;
			testFile.getline(buffer,256);
			float a[4]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion.Normalize();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion.x<<","<<cQuaternion.y<<","<<cQuaternion.z<<","
				<<cQuaternion.w<<endl;
		}
		else if(strcmp(buffer,txt[10])==0){//四元数相乘
			outFile<<"四元数相乘"<<endl;
			testFile.getline(buffer,256);
			float a[8]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion,cQuaternion1,cQuaternion2;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion1.Set(a[4],a[5],a[6],a[7]);
			cQuaternion2=cQuaternion*(cQuaternion1);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<a[4]<<","<<a[5]<<","<<a[6]<<","<<a[7]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion2.x<<","<<cQuaternion2.y<<","<<cQuaternion2.z<<","
				<<cQuaternion2.w<<endl;
		}
		else if(strcmp(buffer,txt[11])==0){//四元数求差
			outFile<<"四元数求差"<<endl;
			testFile.getline(buffer,256);
			float a[8]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion,cQuaternion1,cQuaternion2;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion1.Set(a[4],a[5],a[6],a[7]);
			cQuaternion2=cQuaternion.Div(cQuaternion1);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<a[4]<<","<<a[5]<<","<<a[6]<<","<<a[7]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion2.x<<","<<cQuaternion2.y<<","<<cQuaternion2.z<<","
				<<cQuaternion2.w<<endl;
		}
		else if(strcmp(buffer,txt[12])==0){//四元数点乘
			outFile<<"四元数点乘"<<endl;
			testFile.getline(buffer,256);
			float a[8]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion,cQuaternion1;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion1.Set(a[4],a[5],a[6],a[7]);
			float res=cQuaternion.dotMul(cQuaternion1);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<a[4]<<","<<a[5]<<","<<a[6]<<","<<a[7]<<"\t";
			outFile<<fixed<<setprecision(2)<<res<<endl;
		}
		else if(strcmp(buffer,txt[13])==0){//四元数求逆
			outFile<<"四元数求逆"<<endl;
			testFile.getline(buffer,256);
			float a[4]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion,cQuaternion1;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion1=cQuaternion.GetInverse();
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion1.x<<","<<cQuaternion1.y<<","<<cQuaternion1.z<<","
				<<cQuaternion1.w<<endl;
		}
		else if(strcmp(buffer,txt[14])==0){//四元数求角度和旋转轴
			outFile<<"四元数求角度和旋转轴"<<endl;
			testFile.getline(buffer,256);
			float a[4]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			float angle;
			CVector044 axis;
			cQuaternion.GetAngle(angle,axis);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				angle<<"\t"<<axis.x<<","<<axis.y<<","<<axis.z<<endl;
		}
		else if(strcmp(buffer,txt[15])==0){//四元数插值
			outFile<<"四元数插值"<<endl;
			testFile.getline(buffer,256);
			float a[9]={0};
			split(buffer,a);
			CQuaternion044 cQuaternion,cQuaternion1,cQuaternion2;
			float angle=0;
			cQuaternion.Set(a[0],a[1],a[2],a[3]);
			cQuaternion1.Set(a[4],a[5],a[6],a[7]);
			angle=a[8];
			cQuaternion2=cQuaternion.Slerp(cQuaternion1,angle);
			outFile<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<"\t";
			outFile<<a[4]<<","<<a[5]<<","<<a[6]<<","<<a[7]<<"\t"<<a[8]<<"\t";
			outFile<<fixed<<setprecision(2)<<
				cQuaternion2.x<<","<<cQuaternion2.y<<","<<cQuaternion2.z<<","
				<<cQuaternion2.w<<endl;
		}
	}
	testFile.close();
	outFile.close();
}


