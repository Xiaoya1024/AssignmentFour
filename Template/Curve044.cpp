#define _CRT_SECURE_NO_WARNINGS
#include "Curve044.h"
bool intersect(CVector044&a, CVector044&t, CVector044&b, CVector044&t2,CVector044&out,int type){
	CVector044 d1(t.x-a.x,t.y-a.y,t.z-a.z);
	CVector044 d2(t2.x-b.x,t2.y-b.y,t2.z-b.z);
	if(type!=-1){
		CVector044 a2=a;
		CVector044 b2=b;
		CVector044 d12=d1;
		CVector044 d22=d2;
		if(type==0)a2.x=b2.x=d12.x=d22.x=0;
		else if(type==1)a2.y=b2.y=d12.y=d22.y=0;
		else if(type==2)a2.z=b2.z=d12.z=d22.z=0;
		CVector044 cross=d12.crossMul(d22);
		float xx=cross.len();
		xx*=xx;
		CVector044 bma(b2.x-a2.x,b2.y-a2.y,b2.z-a2.z);
		float t1=(bma.crossMul(d22).dotMul(cross))/xx;
		if(t1>1.0f||t1<0.0f)
			return false;
		if((bma.crossMul(d1).dotMul(cross)/xx>1.0f))
			return false;
		out=a+d1*t1;
		return true;
	}else{
		CVector044 cross=d1.crossMul(d2);
		float xx=cross.len();
		xx*=xx;
		CVector044 bma(b.x-a.x,b.y-a.y,b.z-a.z);
		float t1=(bma.crossMul(d2)).dotMul(cross)/xx;
		if(t1>1.0f||t1<0.0f)
			return false;
		if((bma.crossMul(d1)).dotMul(cross)/xx>1.0f)
			return false;
		out=a+d1*t1;
		return true;
	}
}
float dis(CVector044 &a,CVector044&b,CVector044&p,int type,CVector044&out){
	CVector044 d(b.x-a.x,b.y-a.y,b.z-a.z);
	CVector044 d2(p.x-a.x,p.y-a.y,p.z-a.z);
	if(type==0)d.x=d2.x=0;
	else if(type==1)d.y=d2.y=0;
	else if(type==2)d.z=d2.z=0;
	float len1=d.len();
	float len2=d2.len();
	if(len1==0.0f||len2==0.0f){
		out=a;
		return len2;
	}
	if(d.dotMul(d2)>0){
		CVector044 t2=d2.project(d);
		if(type==0)t2.x=0;
		else if(type==1)t2.y=0;
		else if(type==2)t2.z=0;
		if(t2.len()>len1){
			CVector044 temp(p.x-b.x,p.y-b.y,p.z-b.z);
			if(type==0)temp.x=0;
			else if(type==1)temp.y=0;
			else if(type==2)temp.z=0;
			out=b;
			return temp.len();
		}else{
			CVector044 temp(d2.x-t2.x,d2.y-t2.y,d2.z-t2.z);
			if(type==0)temp.x=0;
			else if(type==1)temp.y=0;
			else if(type==2)temp.z=0;
			out=p-temp;
			return temp.len();
		}
	}else{
		out=a;
		return len2;
	}
}
CCurve044::CCurve044(void)
{
}


CCurve044::~CCurve044(void)
{
}
bool CCurve044::isIntersect(CCurve044&other,std::vector<CVector044>&p,int type){
	CVector044 temp;
	for(unsigned int i=1;i<pointList.size();i++)
		for(unsigned int j=1;j<other.pointList.size();j++)
			if(intersect(pointList[i-1],pointList[i],other.pointList[j-1],other.pointList[j],temp,type))
				p.push_back(temp);
	unsigned int k=0;
	return p.size()>k;
}
float CCurve044::pointToLineDistance(CVector044&p,int type,CVector044&out){
	float dis2=FLT_MAX;
	CVector044 temp;
	for (unsigned int i=1;i<pointList.size();i++)
	{
		float m=dis(pointList[i-1],pointList[i],p,type,temp);
		if(m<dis2){
			out=temp;
			dis2=m;
		}
	}
	return dis2;
}
bool CCurve044::isInside(CVector044&p,int type){
	int cnt=0;
	CVector044 tt(FLT_MAX,FLT_MAX,FLT_MAX);
	CVector044 temp;
	for(unsigned int i=1;i<pointList.size();i++)
		if(intersect(pointList[i-1],pointList[i],p,tt,temp,type))
			cnt++;
	return cnt%2==1;
}
void CCurve044::runByLine(int begind,float begins,float movedis,CVector044&pos,int&curin,float&curdis){
	float ds2=movedis+begins;
	if(ds2>0){
		for(curin=begind;curin<int(pointList.size())-1;curin++){
			float dd=(pointList[curin+1]-pointList[curin]).len();
			if(ds2>=dd){
				ds2-=dd;
			}else{
				curdis=ds2;
				pos=(pointList[curin+1]-pointList[curin])*(ds2/dd)+pointList[curin];
				break;
			}
		}
	}
	else{
		for(curin=begind;curin>0;curin--){
			float dd=(pointList[curin]-pointList[curin-1]).len();
			if(ds2>=dd)
				ds2-=dd;
			else{
				curin=int(ds2);
				pos=(pointList[curin]-pointList[curin-1])*(ds2/dd)+pointList[curin];
				break;
			}
		}
	}
}
void split(char *buffer,float*a){
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
void CCurve044::myCurvePrint(){
	char *txt[]={
		"折线相交",
		"点到折线距离",
		"点在折线内部",
		"沿折线运动"
	};
	
	ifstream testFile;
	testFile.open("test.txt");
	ofstream outFile;
	outFile.open("out.txt");
	if(!testFile.is_open()||!outFile.is_open()){
		cout<<"Error opening file";
		exit(1);
	}
	while(!testFile.eof()){
		char buffer[256];
		testFile.getline(buffer,50);
		if(strcmp(buffer,txt[0])==0){//折线相交
			outFile<<"折线相交"<<endl;
			testFile.getline(buffer,256);
			float a[256]={0.0f};
			split(buffer,a);
			int num1=(int)a[0];
			outFile<<num1<<" ";
			int i=0,k=0;
			CVector044 vec;
			CCurve044 curve1,curve2;
			std::vector<CVector044>p;
			for(i=1;i<=num1*3;i+=3){
				vec.Set(a[i],a[i+1],a[i+2]);
				curve1.pointList.push_back(vec);
				outFile<<fixed<<setprecision(2)<<vec.x<<","<<vec.y<<","<<vec.z<<" ";
			}
			int num2=(int)a[i];
			outFile<<num2<<" ";
			for(k=i+1;k<=i+num2*3;k+=3){
				vec.Set(a[k],a[k+1],a[k+2]);
				curve2.pointList.push_back(vec);
				outFile<<fixed<<setprecision(2)<<vec.x<<","<<vec.y<<","<<vec.z<<" ";
			}
			int type=(int)a[k];
			if(curve1.isIntersect(curve2,p,type)){
				for(unsigned int j=0;j<p.size();j++)
					outFile<<fixed<<setprecision(2)<<p[j].x<<","<<p[j].y<<","<<p[j].z<<" ";
				outFile<<endl;
			}
			else
				outFile<<"0"<<endl;
		}
		else if(strcmp(buffer,txt[1])==0){//点到折线距离
			outFile<<"点到折线距离"<<endl;
			testFile.getline(buffer,256);
			float a[256]={0.0f};
			split(buffer,a);
			CVector044 point,vec,out;
			CCurve044 curve;
			point.Set(a[0],a[1],a[2]);
			outFile<<fixed<<setprecision(2)<<point.x<<","<<point.y<<","<<point.z<<" ";
			int num1=(int)a[3],i=0;
			outFile<<num1<<" ";
			for(i=4;i<4+num1*3;i+=3){
				vec.Set(a[i],a[i+1],a[i+2]);
				curve.pointList.push_back(vec);
				outFile<<fixed<<setprecision(2)<<vec.x<<","<<vec.y<<","<<vec.z<<" ";
			}
			int type=(int)a[i];
			outFile<<type<<" ";
			float dis=curve.pointToLineDistance(point,type,out);
			outFile<<fixed<<setprecision(2)<<out.x<<","<<out.y<<","<<out.z<<" "<<dis<<endl;
		}
		else if(strcmp(buffer,txt[2])==0){//点在折线内部
			outFile<<"点在折线内部"<<endl;
			testFile.getline(buffer,256);
			float a[256]={0.0f};
			split(buffer,a);
			CVector044 point,vec,out;
			CCurve044 curve;
			point.Set(a[0],a[1],a[2]);
			outFile<<fixed<<setprecision(2)<<point.x<<","<<point.y<<","<<point.z<<" ";
			int num1=(int)a[3],i=0;
			outFile<<num1<<" ";
			for(i=4;i<4+num1*3;i+=3){
				vec.Set(a[i],a[i+1],a[i+2]);
				curve.pointList.push_back(vec);
				outFile<<fixed<<setprecision(2)<<vec.x<<","<<vec.y<<","<<vec.z<<" ";
			}
			int type=(int)a[i];
			outFile<<type<<" ";
			int _isInside=0;
			if(curve.isInside(point,type))_isInside=1;
			else _isInside=0;
			outFile<<_isInside<<endl;
		}
		else if(strcmp(buffer,txt[3])==0){//沿折线运动
			outFile<<"沿折线运动"<<endl;
			testFile.getline(buffer,256);
			float a[256]={0.0f};
			split(buffer,a);
			int num1=(int)a[0];
			CCurve044 curve;
			CVector044 vec,pos;
			int begind,i=0,curind;
			float begdis,movedis,curdis;
			for(i=1;i<=num1*3;i+=3){
				vec.Set(a[i],a[i+1],a[i+2]);
				curve.pointList.push_back(vec);
				outFile<<fixed<<setprecision(2)<<vec.x<<","<<vec.y<<","<<vec.z<<" ";
			}
			begind=(int)a[i++];outFile<<begind<<" ";
			begdis=a[i++];
			movedis=a[i++];
			curve.runByLine(begind,begdis,movedis,pos,curind,curdis);
			outFile<<fixed<<setprecision(2)<<begdis<<" "<<movedis<<" "<<pos.x<<","<<pos.y<<","<<pos.z<<" ";
			outFile<<curind<<" ";
			outFile<<fixed<<setprecision(2)<<curdis<<endl;
		}
	}
}
