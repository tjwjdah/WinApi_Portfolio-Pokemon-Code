#include "stdafx.h"
#include "CPokemonballanim.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
CPokemonballanim::CPokemonballanim():m_animend(false)
{
}

CPokemonballanim::~CPokemonballanim()
{
}

void CPokemonballanim::init()
{

	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"Pocketball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Pocketball", L"Texture//monsterball//Pocketball.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"throwball", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), 5, 0.2f);
	AddAnimator(pAnimator);

	pAnimator->Play(L"throwball", false);
}

void CPokemonballanim::update()
{
	if (GetPos().y < 204)
	{
		float y = GetPos().y + fDT * 300;
		SetPos(Vec2(GetPos().x, y));
	}
		if (GetAnimator()->GetCurAnimation()->GetCurFrmldx() >= GetAnimator()->GetCurAnimation()->GetCurMaxFrmIdx())
				m_animend = true;
}

void CPokemonballanim::render(HDC _dc)
{


	if (nullptr != GetAnimator())
		GetAnimator()->render(_dc);
}

void CPokemonballanim::run()
{
	m_animend = false;
	GetAnimator()->Play(L"throwball", false);
	SetPos(Vec2(688.f, 128.f));
}
