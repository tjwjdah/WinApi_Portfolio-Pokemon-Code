#pragma once
#include "CObj.h"
class CEDAnim :
    public CObj
{
public:
	CEDAnim();
	~CEDAnim();


public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


	virtual CEDAnim* Clone() { return new CEDAnim(*this); }
};

