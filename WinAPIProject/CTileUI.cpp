#include "stdafx.h"
#include "CTileUI.h"

#include "CUI.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "resource.h"
#include "CToolScene.h"

CTileUI::CTileUI() :
	m_iImgIdx(0)
{
}

CTileUI::CTileUI(int n) : m_iImgIdx(n)
{
}

CTileUI::~CTileUI()
{
}

void CTileUI::update()
{
	CUI::update();
}


void CTileUI::lateupdate()
{
	CUI::lateupdate();
}


void CTileUI::finalupdate()
{
	CUI::finalupdate();
}


void CTileUI::render(HDC _dc)
{

	int iColMax = GetTexture()->Width() / TILE_SIZE;
	int iRowMax = GetTexture()->Height() / TILE_SIZE;
	int iMaxImgIdx = iColMax * iRowMax;

	if (iMaxImgIdx > m_iImgIdx)
	{
		int iRow = m_iImgIdx / iColMax;
		int iCol = m_iImgIdx % iColMax;

		BitBlt(_dc
			, (int)GetFinalPos().x, (int)GetFinalPos().y
			, TILE_SIZE, TILE_SIZE
			, GetTexture()->GetDC()
			, iCol * TILE_SIZE
			, iRow * TILE_SIZE
			, SRCCOPY);
	}

}

void CTileUI::MouseOn(Vec2 _vMousePos)
{
}

void CTileUI::MouseLBTNDown(Vec2 _vMousePos)
{
	CUI::MouseLBTNDown(_vMousePos);
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
	assert(pToolScene);
	pToolScene->SetMouseimNum(m_iImgIdx);
	pToolScene->SetMouseUiType(GetUIType());
	if (!GetUse())
	{
		GetParent()->MouseLBTNDown(_vMousePos);
	}
}

void CTileUI::MouseLBTNUp(Vec2 _vMousePos)
{
}

void CTileUI::MouseLBTNClicked(Vec2 _vMousePos)
{
}
