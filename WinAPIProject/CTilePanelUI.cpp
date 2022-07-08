#include "stdafx.h"
#include "CTilePanelUI.h"

#include "CTexture.h"
#include "CTileUI.h"


#include "CScene.h"
#include "CSceneMgr.h"
#include "CToolScene.h"
#include "CKeyMgr.h"

#define TILEPageMax 6
#define TILE2PageMax 2
#define OBJECTPageMax 2
CTilePanelUI::CTilePanelUI() :
	PageNum(1),
	m_ShowUIType(UI_TYPE::TILE)
	, PageMax(TILEPageMax)
{
}

CTilePanelUI::~CTilePanelUI()
{
}

void CTilePanelUI::finalupdate()
{
	
	CPanelUI::finalupdate();
}

void CTilePanelUI::render(HDC _dc)
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



	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->render(_dc);
	}
}

void CTilePanelUI::MouseOn(Vec2 _vMousePos)
{
}

void CTilePanelUI::MouseLBTNDown(Vec2 _vMousePos)
{
	CPanelUI::MouseLBTNDown(_vMousePos);
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
	assert(pToolScene);
	pToolScene->SetMouseimNum(-1);
}

void CTilePanelUI::MouseLBTNUp(Vec2 _vMousePos)
{
}

void CTilePanelUI::MouseLBTNClicked(Vec2 _vMousePos)
{
}

void CTilePanelUI::PageNumUp()
{
	const vector<CUI*>& vecChild = GetChild();
	int l = 0;

	if (PageNum < PageMax)
	{
		PageNum++;
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			if (vecChild[i]->GetUIType() == m_ShowUIType)
			{
				l++;
				if (l > 30 * (PageNum - 1) && l <= 30 * PageNum)
				{
					vecChild[i]->SetUse(true);
				}
				else
				{
					vecChild[i]->SetUse(false);
				}
			}
		}
	}
}

void CTilePanelUI::PageNumDawn()
{
	const vector<CUI*>& vecChild = GetChild();
	int l = 0;

	if (PageNum > 1)
	{
		PageNum--;
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			if (vecChild[i]->GetUIType() == m_ShowUIType)
			{
				l++;
				if (l > 30 * (PageNum - 1) && l <= 30 * PageNum)
				{
					vecChild[i]->SetUse(true);
				}
				else
				{
					vecChild[i]->SetUse(false);
				}
			}
		}
	}
}

void CTilePanelUI::ChangeShowUIType(UI_TYPE UIType)
{
	switch (UIType)
	{
	case UI_TYPE::TILE:
		PageMax = TILEPageMax;
		break;
	case UI_TYPE::TILE2:
		PageMax = TILE2PageMax;
		break;
	case UI_TYPE::OBJECT:
		PageMax = OBJECTPageMax;
		break;
	}
	
	int l = 0;

	PageNum = 1;
	 const vector<CUI*>& vecChild = GetChild();
	 for (size_t i = 0; i < vecChild.size(); ++i)
	 {
		 if (vecChild[i]->GetUIType() == m_ShowUIType)
		 {
				 vecChild[i]->SetUse(false);
		 }
	 }
	 m_ShowUIType = UIType;
	 for (size_t i = 0; i < vecChild.size(); ++i)
	 {
		 if (vecChild[i]->GetUIType() == m_ShowUIType)
		 {
			 l++;
			 if ( l <= 30 )
			 {
				 vecChild[i]->SetUse(true);
			 }
		 }
	 }
}
