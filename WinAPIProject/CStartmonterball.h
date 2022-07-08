#pragma once
#include "CObj.h"
class CStartmonterball :
    public CObj
{
public:
	CStartmonterball();
	~CStartmonterball();


private:
	
	float m_gravity;

	bool  m_end;

public:

	
	void Run();
	bool Getend() {return m_end;}
public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);




	virtual CStartmonterball* Clone() { return new CStartmonterball(*this); }

};

