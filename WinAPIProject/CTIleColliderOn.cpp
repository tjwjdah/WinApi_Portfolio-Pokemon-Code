#include "stdafx.h"
#include "CTIleColliderOn.h"

#include "CSceneMgr.h"
#include "CToolScene.h"
#include "CScene.h"
#include "CTexture.h"

CTIleColliderOn::CTIleColliderOn()
{
}

CTIleColliderOn::~CTIleColliderOn()
{
}

void CTIleColliderOn::render(HDC _dc)
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

void CTIleColliderOn::MouseLBTNDown(Vec2 _vMousePos)
{
	
	CUI::MouseLBTNDown(_vMousePos);



	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
	if (!m_On)
		{
			m_On = true;
			pToolScene->SetcolliderOn(m_On);
			//pToolScene->SetMouseimNum(-1);
			//pToolScene->SetMouseUiType(UI_TYPE::COLLIDER);
		
		}
		else
		{

			m_On = false;
			pToolScene->SetcolliderOn(m_On);
			//pToolScene->SetMouseimNum(-1);
			//pToolScene->SetMouseUiType(UI_TYPE::DEFAULT);
		
		}
	

}
