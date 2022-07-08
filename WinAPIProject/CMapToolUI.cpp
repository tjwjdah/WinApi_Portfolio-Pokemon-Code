#include "stdafx.h"
#include "CMapToolUI.h"


#include "CTexture.h"
#include "CTileUI.h"


#include "CScene.h"
#include "CSceneMgr.h"
#include "CToolScene.h"


CMapToolUI::CMapToolUI()
{
}

CMapToolUI::~CMapToolUI()
{
}

void CMapToolUI::finalupdate()
{
	CPanelUI::finalupdate();
}

void CMapToolUI::render(HDC _dc)
{
	CTexture* pTex = GetTex();
	if (nullptr == pTex)
		return;

	Vec2 vPos = GetFinalPos();
	int iWidth = pTex->Width();
	int iHeight = pTex->Height();

	BitBlt(_dc
		, (int)vPos.x, (int)vPos.y
		, iWidth, iHeight
		, pTex->GetDC()
		, 0, 0
		, SRCCOPY);

	wstring strPath;

	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->render(_dc);
	}
}

void CMapToolUI::MouseOn(Vec2 _vMousePos)
{
}

void CMapToolUI::MouseLBTNDown(Vec2 _vMousePos)
{
	CPanelUI::MouseLBTNDown(_vMousePos);
}

void CMapToolUI::MouseLBTNUp(Vec2 _vMousePos)
{
}

void CMapToolUI::MouseLBTNClicked(Vec2 _vMousePos)
{
}

void CMapToolUI::PageNumUp()
{
}

void CMapToolUI::PageNumDawn()
{
}
