#pragma once
#include "CObj.h"

class CMissile :
	public CObj
{
private:	
	Vec2	m_vDir;
	float	m_fSpeed;

public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual CMissile* Clone() { return new CMissile(*this); }

public:
	CMissile();
};

