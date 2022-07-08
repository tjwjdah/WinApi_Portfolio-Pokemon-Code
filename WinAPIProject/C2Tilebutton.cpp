#include "stdafx.h"
#include "C2Tilebutton.h"

#include "CSceneMgr.h"
#include "CToolScene.h"
#include "CScene.h"
#include "CTexture.h"

C2Tilebutton::C2Tilebutton() :m_On(false)
{
}

C2Tilebutton::~C2Tilebutton()
{
}

void C2Tilebutton::render(HDC _dc)
{
	if (nullptr == GetTexture())
		return;

	int iWidth = GetTexture()->Width();
	int iHeight = GetTexture()->Height();
	if (!m_On)
	{
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y
			, iWidth, iHeight / 2
			, GetTexture()->GetDC()
			, 0, 0
			, iWidth, iHeight / 2
			, RGB(255, 0, 255));

	}
	else
	{
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y
			, iWidth, iHeight / 2
			, GetTexture()->GetDC()
			, 0, (iHeight / 2)
			, iWidth, iHeight / 2
			, RGB(255, 0, 255));
	}
}

void C2Tilebutton::MouseLBTNDown(Vec2 _vMousePos)
{

	CUI::MouseLBTNDown(_vMousePos);

	

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
	if (!m_On)
	{
		m_On = true;
		pToolScene->Set2TileOn(m_On);
		
	}
	else
	{

		m_On = false;
		pToolScene->Set2TileOn(m_On);
		
	}
}
