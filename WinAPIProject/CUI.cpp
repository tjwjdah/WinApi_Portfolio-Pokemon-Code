#include "stdafx.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

#include "resource.h"

CUI::CUI()
	: m_pParent(nullptr)
	, m_vFinalPos()
	, m_pTex(nullptr)
	, m_bMouseOn(false)
	, m_bLBTNDown(false)
	, m_Use(true)
	, m_UType(UI_TYPE::DEFAULT)
{
	SetObjtype(OBJ_TYPE::UI);
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

CUI::CUI(const CUI& _origin)
	: CObj(_origin)
	, m_pParent(nullptr)
	, m_pTex(_origin.m_pTex)
	, m_bMouseOn(false)
	, m_bLBTNDown(false)
	, m_Use(_origin.m_Use)
	, m_UType(_origin.m_UType)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_origin.m_vecChildUI[i]->Clone());
	}
}

void CUI::update()
{
	// Child
	if (!m_Use)
		return;
		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->update();
		}
	
}

void CUI::lateupdate()
{
	// Child
	if (!m_Use)
		return;
		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->lateupdate();
		}

}

void CUI::finalupdate()
{
	m_vFinalPos = GetPos();

	if (!m_Use)
		return;
	if (m_pParent)
	{
		m_vFinalPos += m_pParent->m_vFinalPos;
	}

	// 마우스 왼쪽 손 대지 아니하였던 바로 그 순간
	if (KEY_AWAY(KEY_TYPE::LBTN))
	{
		m_bLBTNDown = false;
	}

	MonseOnCheck();

	// Child
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render(HDC _dc)
{
	if (nullptr == m_pTex)
		return;
		
	int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	/*if (m_bMouseOn && m_bLBTNDown)
	{
		TransparentBlt(_dc
			, (int)m_vFinalPos.x, (int)m_vFinalPos.y
			, iWidth, iHeight / 2
			, m_pTex->GetDC()
			, 0, (iHeight / 2) 
			, iWidth, iHeight / 2 
			, RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_dc
			, (int)m_vFinalPos.x, (int)m_vFinalPos.y
			, iWidth, iHeight / 2
			, m_pTex->GetDC()
			, 0, 0
			, iWidth, iHeight / 2
			, RGB(255, 0, 255));
	}	*/

	TransparentBlt(_dc
		, (int)m_vFinalPos.x, (int)m_vFinalPos.y
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));

	// Child
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::AddChildUI(CUI* _pChildUI)
{
	assert(!_pChildUI->m_pParent);

	_pChildUI->m_pParent = this;
	m_vecChildUI.push_back(_pChildUI);
}

void CUI::MouseOn(Vec2 _vMousePos)
{

}

void CUI::MouseLBTNDown(Vec2 _vMousePos)
{
	m_bLBTNDown = true;
}

void CUI::MouseLBTNUp(Vec2 _vMousePos)
{
}

void CUI::MouseLBTNClicked(Vec2 _vMousePos)
{	

}


void CUI::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CUI::MonseOnCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();	
	Vec2 vScale = GetScale();

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
