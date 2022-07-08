#pragma once

#include "CScene.h"
class CPlayer;
class CTextBar;
class CNurse;

class CPokemon;
class CStartScene
	: public CScene
{
public:
	CStartScene();
	~CStartScene();
private:
	Vec2 m_PlayerPos;

	CPlayer* m_Player;


	CNurse* m_Nurse;

	CTextBar* m_TextBar;

	list<tEvent> m_timeEventplay;
	Vec2     m_preCamera;


	CPokemon* m_p1;
	CPokemon* m_p2;
	CPokemon* m_p3;
	
	bool m_noinit;


	bool m_CoShow;

	int  soundon;
public:
	virtual void init();
	virtual void update();

	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	virtual void TileUpdate(int _iUpdate);

	virtual void Enter();
	virtual void Exit();


public:
	void timeEvenadd(CObj* _pNewObj, Vec2 _vPos, OBJ_TYPE _eType, float _dtime);
	void timeEvenadd(CObj* _pDeleteObj, float _dtime);
	void timeEvenadd(SCENE_TYPE _eNextScene, float _dtime);
	
	CTextBar* GetTextBar() { return m_TextBar; }
	CPlayer* GetPlayer() { return m_Player; }

	void SetpreCamera();
	Vec2 GetpreCamera() { return m_preCamera; }
	CNurse* GetNurse() { return m_Nurse; }
	void Setsoundon(int _onnum) { soundon = _onnum; }
};

