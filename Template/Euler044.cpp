#include "Euler044.h"

CEuler044::CEuler044(void)
{

}

CEuler044::~CEuler044(void)
{

}
float valToDegree(float val){//弧度转化为角度
	float res=(float)(val/PI*180);
	return res;
}
float degreeToVal(float degree){//角度转化为弧度
	float res=(float)(degree/180*PI);
	return res;
}
void CEuler044::Set(float h,float p,float b){
	this->h=h;
	this->p=p;
	this->b=b;
}
CVector044 CEuler044::ToVector3(CVector044*updir){
	updir->x=cos(degreeToVal((float)(b+90)));
	updir->y=sin(degreeToVal((float)(b+90))*sin(degreeToVal(90-p)));
	if(fabs(updir->x)<=1e-6)
		updir->x=0;
	if(fabs(updir->y)<=1e-6)
		updir->y=0;
	updir->z=-cos(degreeToVal((float)(90-p)));

	CVector044 res;
	res.x=cos(degreeToVal((float)(h+90)));
	res.z=-sin(degreeToVal((float)(h+90)));
	if(fabs(p)<=1e-6)
		res.y=0;
	else
		res.y=tan(degreeToVal((float)(p+90)))*sqrtf(res.x*res.x+res.z*res.z);      
	return res;
}

CMatrix044 CEuler044::ToMatrix(){
	CMatrix044 res;
	float _h=degreeToVal(h);
	float _p=degreeToVal(p);
	float _b=degreeToVal(b);
	res.m00=cos(_h)*cos(_b)+sin(_h)*sin(_p)*sin(_b);
	res.m01=-cos(_h)*sin(_b)+sin(_h)*sin(_p)*cos(_b);
	res.m02=sin(_h)*cos(_p);
	res.m03=0;
	res.m10=sin(_b)*cos(_p);
	res.m11=cos(_b)*cos(_p);
	res.m12=-sin(_p);
	res.m13=0;
	res.m20=-sin(_h)*cos(_b)+cos(_h)*sin(_p)*sin(_b);
	res.m21=sin(_b)*sin(_h)+cos(_h)*sin(_p)*cos(_b);
	res.m22=cos(_h)*cos(_p);
	res.m23=0;
	res.m30=0;
	res.m31=0;
	res.m32=0;
	res.m33=1;
	return res;
}
CQuaternion044 CEuler044::ToQuaternion(){
	CQuaternion044 res;
	float _h=degreeToVal(h);
	float _p=degreeToVal(p);
	float _b=degreeToVal(b);
	res.w=cos(_h/2)*cos(_p/2)*cos(_b/2)+sin(_h/2)*sin(_p/2)*sin(_b/2);
	res.x=cos(_h/2)*sin(_p/2)*cos(_b/2)+sin(_h/2)*cos(_p/2)*sin(_b/2);
	res.y=sin(_h/2)*cos(_p/2)*cos(_b/2)-cos(_h/2)*sin(_p/2)*sin(_b/2);
	res.z=cos(_h/2)*cos(_p/2)*sin(_b/2)-sin(_h/2)*sin(_p/2)*cos(_b/2);
	return res;
}

void CEuler044::eulerNormal(){
	while (b > 180.0)
		b -= 360;
	while (b < -180.0)
		b += 360;
	while (p > 90.0)
		p -= 180;
	while (p < -90.0)
		p += 180;
	if (p == 90.0 || p == -90.0) {
		h -= b;
		b = 0;
	}
	while (h > 180.0)
		h -= 360;
	while (h < -180.0)
		h += 360;
}

