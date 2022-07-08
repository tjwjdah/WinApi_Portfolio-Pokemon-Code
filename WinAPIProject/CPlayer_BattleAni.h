#pragma once
#include "CObj.h"
class CPlayer_BattleAni :
    public CObj
{
public:
	CPlayer_BattleAni();
	~CPlayer_BattleAni();

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC _dc);


	virtual CPlayer_BattleAni* Clone() { return new CPlayer_BattleAni(*this); }
};

