#pragma once
#include "CObj.h"

class CTexture;
class CThrowPokeball :
    public CObj
{
public:
	CThrowPokeball();
	~CThrowPokeball();


private:
	float m_gravity;
	CTexture* m_pTex;

	bool  m_anion;
	int   m_page;
	int   m_r;
public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


	virtual CThrowPokeball* Clone() { return new CThrowPokeball(*this); }
};

