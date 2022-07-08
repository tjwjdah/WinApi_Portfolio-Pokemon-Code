#include "stdafx.h"
#include "CPokeball.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CCollider.h"

#include "CSound.h"
CPokeball::CPokeball() :m_pTex(nullptr),
m_pTex2(nullptr),
m_pTex3(nullptr),
m_pTex4(nullptr),
m_pTex5(nullptr),
m_Yes(true),
m_on(true),
m_Pokemon(nullptr)
{
}

CPokeball::~CPokeball()
{
	//if (m_Pokemon != nullptr)
		//delete m_Pokemon;
}

CPokeball::CPokeball(const CPokeball& _origin)
{
}

void CPokeball::update()
{
	if (m_on)
		return;
	if (m_Yes)
	{
		if (KEY_TAP(KEY_TYPE::KEY_DOWN))
		{
			m_Yes = false;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(80.f);
			pNewSound->Play(false);
		}
	}
	else
	{
		if (KEY_TAP(KEY_TYPE::KEY_UP))
		{
			m_Yes = true;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(80.f);
			pNewSound->Play(false);
		}
	}
}

void CPokeball::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;

	
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, m_pTex->Width(), m_pTex->Height() 
		, m_pTex->GetDC()
		, 0, 0 
		, m_pTex->Width(), m_pTex->Height() 
		, RGB(255, 0, 255));
	if (m_on)
		return;

	TransparentBlt(_dc
		, 334
		, 0
		, m_pTex2->Width(), m_pTex2->Height()
		, m_pTex2->GetDC()
		, 0, 0
		, m_pTex2->Width(), m_pTex2->Height()
		, RGB(255, 0, 255));

	TransparentBlt(_dc
		, 340
		, 10
		, m_pTex3->Width(), m_pTex3->Height()/2
		, m_pTex3->GetDC()
		, 0, 0
		, m_pTex3->Width(), m_pTex3->Height()/2
		, RGB(255, 0, 255));

	TransparentBlt(_dc
		, 712
		, 250
		, m_pTex4->Width(), m_pTex4->Height()
		, m_pTex4->GetDC()
		, 0, 0
		, m_pTex4->Width(), m_pTex4->Height()
		, RGB(255, 0, 255));
	if (m_Yes)
	{
		TransparentBlt(_dc
			, 752
			, 290
			, m_pTex5->Width(), m_pTex5->Height()
			, m_pTex5->GetDC()
			, 0, 0
			, m_pTex5->Width(), m_pTex5->Height()
			, RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_dc
			, 752
			, 345
			, m_pTex5->Width(), m_pTex5->Height()
			, m_pTex5->GetDC()
			, 0, 0
			, m_pTex5->Width(), m_pTex5->Height()
			, RGB(255, 0, 255));
	}
}

void CPokeball::init()
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"pokeball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"pokeball", L"Texture//Objects//BaseObject1//pokeball.bmp");
	}

	m_pTex2 = CResMgr::GetInst()->FindTexture(L"Squareframe");
	if (nullptr == m_pTex2)
	{
		m_pTex2 = CResMgr::GetInst()->LoadTexture(L"Squareframe", L"Texture//Squareframe.bmp");
	}

	


	m_pTex4 = CResMgr::GetInst()->FindTexture(L"YesNo");
	if (nullptr == m_pTex4)
	{
		m_pTex4 = CResMgr::GetInst()->LoadTexture(L"YesNo", L"Texture//YesNo.bmp");
	}

	m_pTex5 = CResMgr::GetInst()->FindTexture(L"BatteArrow");
	if (nullptr == m_pTex5)
	{
		m_pTex5 = CResMgr::GetInst()->LoadTexture(L"BatteArrow", L"Texture//Battle//BatteArrow.bmp");
	}

	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f, 28.f));
	pCollider->SetScale(Vec2(64.f, 64.f));
	AddCollider(pCollider);
}

void CPokeball::OnCollisionEnter(CCollider* _pOther)
{
}

void CPokeball::OnCollision(CCollider* _pOther)
{

	
}
