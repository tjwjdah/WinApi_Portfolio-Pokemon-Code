#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI*		m_pFocusedUI;

public:
	void update();

private:
	CUI* GetTargetUI(CUI* _pParentUI, Vec2 _vMousePos);

};

