#include "stdafx.h"
#include "CObj.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CTimeMgr.h"


CObj::CObj()
	: m_vPos()
	, m_vScale()
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_fMass(1.f)
	, m_bDead(false)
	, m_mObjtype(OBJ_TYPE::DEFAULT)
{}

CObj::CObj(const CObj & _origin)
	: m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_fMass(_origin.m_fMass)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bDead(false)
	, m_mObjtype(_origin.m_mObjtype)
{
	if(nullptr != _origin.m_pCollider)
		AddCollider(_origin.m_pCollider->Clone());	

	if(nullptr != _origin.m_pAnimator)
		AddAnimator(_origin.m_pAnimator->Clone());
}

CObj::~CObj()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CObj::update()
{
	
}

void CObj::lateupdate()
{
}

void CObj::finalupdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->finalupdate();

	if (nullptr != m_pAnimator)
		m_pAnimator->finalupdate();


	// 가속도를 구한다.
	Vec2 vAccel = m_vForce / m_fMass; 

	// 가속도를 시간동기화, 속도에 더해준다
	m_vVelocity += vAccel * fDT;
	if (abs(m_vVelocity.length()) > 200.f)
	{
		m_vVelocity.normalize();
		m_vVelocity *= 200.f;
	}

	// 속도에 따른 이동
	if (m_vForce.IsZero() && !m_vVelocity.IsZero())
	{
		Vec2 vAntiVelocity = m_vVelocity;
		vAntiVelocity.normalize();
		vAntiVelocity = vAntiVelocity * -400.f * fDT;

		if (vAntiVelocity.length() > m_vVelocity.length())
			vAntiVelocity = -m_vVelocity;
		m_vVelocity += vAntiVelocity;		
	}

	m_vPos += m_vVelocity * fDT;		

	m_vForce = Vec2(0.f, 0.f);
}

void CObj::render(HDC _dc)
{
	Rectangle(_dc
		, (int)(m_vPos.x - m_vScale.x / 2.f)
		, (int)(m_vPos.y - m_vScale.y / 2.f)
		, (int)(m_vPos.x + m_vScale.x / 2.f)
		, (int)(m_vPos.y + m_vScale.y / 2.f));

	
}

void CObj::colliderrender(HDC _dc)
{
	if (nullptr != m_pCollider)
	m_pCollider->render(_dc);
}


void CObj::AddCollider(CCollider* _pCollider)
{
	m_pCollider = _pCollider;
	m_pCollider->m_pObject = this;
}

void CObj::deleteCollder()
{
	if (nullptr != m_pCollider)
	{
			delete m_pCollider;
			m_pCollider = nullptr;
	}
}

void CObj::AddAnimator(CAnimator* _pAnimator)
{
	m_pAnimator = _pAnimator;
	m_pAnimator->m_pObject = this;
}