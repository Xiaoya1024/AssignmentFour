#pragma once
#include"Vector044.h"
#include <vector>
class CCurve044
{
public:
	CCurve044(void);
	~CCurve044(void);
	std::vector<CVector044>pointList;
	bool isIntersect(CCurve044&other,std::vector<CVector044>&p,int type);
	float pointToLineDistance(CVector044&p,int type,CVector044&out);
	bool isInside(CVector044&p,int type);
	void runByLine(int begind,float begins,float movedis,CVector044&pos,int&curin,float&curdis);
	void myCurvePrint();
};

