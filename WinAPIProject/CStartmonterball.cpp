#include "stdafx.h"
#include "CStartmonterball.h"


#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

CStartmonterball::CStartmonterball():m_gravity(-300.f), m_end(false)
{
	SetObjtype(OBJ_TYPE::DEFAULT);
}

CStartmonterball::~CStartmonterball()
{
}

void CStartmonterball::Run()
{
	SetPos(Vec2(110.f, 250.f));
	m_gravity = -300.f;
	m_end = false;
}

void CStartmonterball::init()
{
	
	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"startmonterball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"startmonterball", L"Texture//Battle//startmonterball.bmp");
	}
	

	CAnimator* pAnimator = new CAnimator;

	pAnimator->AddAnimation(L"startmonterball", m_pTex, Vec2(0.f, 0.f), Vec2(56.f ,52.f), 32, 0.03f);
	
	pAnimator->Play(L"startmonterball", true);
	AddAnimator(pAnimator);

	
}

void CStartmonterball::update()
{
	m_gravity += (fDT * 1000);
	if (m_end)
		return;
	if (GetPos().y< 448)
	{
		float x = GetPos().x + fDT * 110;
		float y = GetPos().y + fDT * m_gravity;
		SetPos(Vec2(x, y));
		return;
	}
	m_end = true;
}

void CStartmonterball::render(HDC _dc)
{
	if (GetPos().y < 448)
	{
		if (nullptr != GetAnimator())
			GetAnimator()->render(_dc);
	}
}
