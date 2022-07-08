#pragma once
#include "CObj.h"

class CMonster :
	public CObj
{
private:
	CTexture* m_pTex;

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);
	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual CMonster* Clone() { return new CMonster(*this); }

public:
	CMonster();
	~CMonster();
};

