#pragma once
#include "CObj.h"
class CPokemonanim :
    public CObj
{
public:
	CPokemonanim();
	~CPokemonanim();

private:
	CTexture* m_pTex;
	wstring m_pokemonname;
public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


public:
	void SetName(const wstring& _name);
	
public:

	virtual CPokemonanim* Clone() { return new CPokemonanim(*this); }


};

