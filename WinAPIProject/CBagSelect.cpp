#include "stdafx.h"
#include "CBagSelect.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
CBagSelect::CBagSelect():ArrowPos(1)
{
	SetObjtype(OBJ_TYPE::UI);
	m_pTex = CResMgr::GetInst()->FindTexture(L"bagselect");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bagselect", L"Texture//Bag//bagselect.bmp");
	}

	m_pArrowTex = CResMgr::GetInst()->FindTexture(L"BatteArrow");
	if (nullptr == m_pArrowTex)
	{
		m_pArrowTex = CResMgr::GetInst()->LoadTexture(L"BatteArrow", L"Texture//Battle//BatteArrow.bmp");
	}
}

CBagSelect::~CBagSelect()
{
}

void CBagSelect::render(HDC _dc)
{
	if (!GetUse())
		return;
	BitBlt(_dc
		, 680
		, 456
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0, SRCCOPY);

	switch (ArrowPos)
	{
	case 1:
		BitBlt(_dc
			, 718
			, 494
			, m_pArrowTex->Width()
			, m_pArrowTex->Height()
			, m_pArrowTex->GetDC()
			, 0
			, 0, SRCCOPY);
		break;
	case 2:
		BitBlt(_dc
			, 718
			, 558
			, m_pArrowTex->Width()
			, m_pArrowTex->Height()
			, m_pArrowTex->GetDC()
			, 0
			, 0, SRCCOPY);
		break;
	}

}

void CBagSelect::update()
{

	if (!GetUse())
		return;
	if (ArrowPos == 1)
	{
		if (KEY_TAP(KEY_TYPE::KEY_DOWN))
			ArrowPos = 2;
	}
	else if (ArrowPos == 2)
	{
		if (KEY_TAP(KEY_TYPE::KEY_UP))
			ArrowPos = 1;
	}
}
