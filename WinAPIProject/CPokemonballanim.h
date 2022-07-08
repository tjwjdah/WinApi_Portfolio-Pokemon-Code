#pragma once
#include "CObj.h"
class CPokemonballanim :
    public CObj
{
public:
	CPokemonballanim();
	~CPokemonballanim();


private:
	bool m_animend;


public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


	virtual CPokemonballanim* Clone() { return new CPokemonballanim(*this); }


public:
	void run();
	bool Getanimend() { return m_animend; }
};


