#include "stdafx.h"
#include "CHouse.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CDoor.h"

CHouse::CHouse():
	m_pTex(nullptr)
  , m_pDoor(nullptr)
 , m_pDoorPos(Vec2(0.f,0.f))
{

	SetObjtype(OBJ_TYPE::HOUSE);
}

CHouse::~CHouse()
{
	if (m_pDoor != nullptr)
		delete m_pDoor;
}

CHouse::CHouse(const CHouse& _origin):
	CObj(_origin)
	, m_pTex(_origin.m_pTex)
	, m_pDoorPos(_origin.m_pDoorPos)
{
	m_pDoor = _origin.m_pDoor->Clone();
}

void CHouse::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CHouse::SetDoor(CDoor* _Door)
{
	m_pDoor = _Door;
}

void CHouse::SetDoorPos(Vec2 _pos)
{
	m_pDoorPos = _pos;
	
}

void CHouse::update()
{
	if (m_pDoor != nullptr)
	{

		m_pDoor->SetPos(GetPos() + m_pDoorPos);
		m_pDoor->update();
	}
}

void CHouse::render(HDC _dc)
{

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (nullptr != GetCollider())
	//	GetCollider()->render(_dc);

	if (m_pTex != nullptr) {
		BLENDFUNCTION ftn = {};

		ftn.BlendOp = AC_SRC_OVER;
		ftn.AlphaFormat = AC_SRC_ALPHA;
		ftn.SourceConstantAlpha = 255;
		AlphaBlend(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, m_pTex->Width()
			, m_pTex->Height()
			, m_pTex->GetDC()
			, 0
			, 0
			, m_pTex->Width()
			, m_pTex->Height()
			, ftn);
	}
	if (m_pDoor != nullptr)
		m_pDoor->render(_dc);
}

void CHouse::OnCollisionEnter(CCollider* _pOther)
{
	
}
