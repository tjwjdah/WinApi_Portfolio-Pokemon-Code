#include "stdafx.h"
#include "CDoor.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CCollider.h"
CDoor::CDoor() :
	m_pTex(nullptr),
	m_TelpoPos(Vec2(0.f, 0.f))
{
	SetObjtype(OBJ_TYPE::DOOR);
}

CDoor::~CDoor()
{
}

CDoor::CDoor(const CDoor& _origin) :
	CObj(_origin)
	, m_pTex(_origin.m_pTex)
{
}

void CDoor::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CDoor::init()
{

	CAnimator* m_pAni = new CAnimator;
	if (m_pTex !=nullptr) {
		m_pAni->AddAnimation(L"OPNE", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), 7, 0.5f);
		

		AddAnimator(m_pAni);
	}
	CCollider* pCollider = new CCollider;
	pCollider->SetScale(Vec2(64.f,64.f));
	pCollider->SetOffsetPos(Vec2(32.f, 32.f));

	AddCollider(pCollider);
	
}

void CDoor::update()
{
	GetAnimator()->finalupdate();
	GetCollider()->finalupdate();
}

void CDoor::render(HDC _dc)
{
	GetAnimator()->render(_dc);

}

void CDoor::OnCollisionEnter(CCollider* _pOther)
{

	
}
