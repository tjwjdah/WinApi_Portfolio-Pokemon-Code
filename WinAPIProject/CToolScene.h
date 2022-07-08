#pragma once
#include "CScene.h"

class CToolScene :
    public CScene
{
private:
	HMENU		m_hMenu;


	int			m_MouseimNum;
	UI_TYPE     m_MouseUiType;
	CTexture*  m_pTex;
	CTexture* m_pTex2;
	CTexture* m_pTex3;

	Vec2 m_PlayerPos;

	bool		m_2TileOn;
	bool		m_colliderOn;

public:
	virtual void init();
	virtual void update();
	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void CreateTile(UINT _iXCount, UINT _iYCount);
	virtual void TileUpdate(int _iUpdate);

	virtual void Enter();
	virtual void Exit();

public:
	void SetMouseimNum(int _Num) { m_MouseimNum = _Num; }
	void SetMouseUiType(UI_TYPE _Type) { m_MouseUiType = _Type; }
	void Set2TileOn(bool _2TileOn) { m_2TileOn = _2TileOn; }
	void SetcolliderOn(bool _colliderOn) { m_colliderOn = _colliderOn; }

	bool UIMouseOnCheck();

/*
private:
	void CreateTile(UINT _iXCount, UINT _iYCount);

	void TileUpdate(int _iUpdate);
*/
	
	void KeyCheck();

public:
	CToolScene();
	~CToolScene();

	friend INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	friend void LoadTile();
};

