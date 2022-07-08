#pragma once
#include "CScene.h"
class COPScene :
    public CScene
{
public:
	COPScene();
	~COPScene();
	
private:
	CTexture* m_pTex1;
	CTexture* m_pTex2;

	bool      m_on;
	bool      m_on2;
public:
	virtual void init();
	virtual void update();

	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);


	virtual void Enter();
	virtual void Exit();
};

