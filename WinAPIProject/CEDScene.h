#pragma once
#include "CScene.h"
class CEDScene :
    public CScene
{
public:
	CEDScene();
	~CEDScene();

private:
	CTexture* m_pTex;

public:
	virtual void init();
	virtual void update();

	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);


	virtual void Enter();
	virtual void Exit();

};

