#include "stdafx.h"
#include "CPokemonanim.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CResMgr.h"

CPokemonanim::CPokemonanim():m_pTex(nullptr)
{
}

CPokemonanim::~CPokemonanim()
{
}

void CPokemonanim::init()
{
	


	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"Swap"+ m_pokemonname, m_pTex, Vec2(0.f, 0.f), Vec2(m_pTex->Width()/2, m_pTex->Height()), 2, 0.3f);

	pAnimator->Play(L"Swap"+ m_pokemonname, true);
	AddAnimator(pAnimator);
}

void CPokemonanim::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->finalupdate();
}

void CPokemonanim::render(HDC _dc)
{
	
	
	if (nullptr != GetAnimator())
		GetAnimator()->render(_dc);
}

void CPokemonanim::SetName(const wstring& _name)
{
	m_pTex = CResMgr::GetInst()->FindTexture(_name);
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(_name, L"Texture//Pokemon//"+ _name+L".bmp");
	}

	m_pokemonname = _name;
}
