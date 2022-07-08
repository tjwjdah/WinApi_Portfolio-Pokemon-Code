#include "stdafx.h"
#include "CEDAnim.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"
CEDAnim::CEDAnim()
{
}

CEDAnim::~CEDAnim()
{
}

void CEDAnim::init()
{

	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"EDAnim");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"EDAnim", L"Texture//EDAnim.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"EDAnim", m_pTex, Vec2(0.f, 0.f), Vec2(188.f, 236.f), 6, 0.2f);
	AddAnimator(pAnimator);

	pAnimator->Play(L"EDAnim", true);
}

void CEDAnim::update()
{
}

void CEDAnim::render(HDC _dc)
{
	if (GetAnimator() != nullptr)
		GetAnimator()->render(_dc);
}
