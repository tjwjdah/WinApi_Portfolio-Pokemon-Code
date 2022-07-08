#include "stdafx.h"
#include "CPanelUI.h"

#include "CTexture.h"

#include "CKeyMgr.h"


CPanelUI::CPanelUI() :m_vStartPos(Vec2(0.f, 0.f))
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::finalupdate()
{
	if (IsLBTNDown())
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vDiff = vMousePos - m_vStartPos;

		m_vStartPos = vMousePos;

		SetPos(GetPos() + vDiff);
	}

	CUI::finalupdate();
}

void CPanelUI::render(HDC _dc)
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
		
		vecChild[i]->render(_dc);
	}
}

void CPanelUI::MouseOn(Vec2 _vMousePos)
{
}

void CPanelUI::MouseLBTNDown(Vec2 _vMousePos)
{
	CUI::MouseLBTNDown(_vMousePos);

	m_vStartPos = _vMousePos;
}

void CPanelUI::MouseLBTNUp(Vec2 _vMousePos)
{
}

void CPanelUI::MouseLBTNClicked(Vec2 _vMousePos)
{
	
}

void CPanelUI::PageNumUp()
{
}

void CPanelUI::PageNumDawn()
{
}
