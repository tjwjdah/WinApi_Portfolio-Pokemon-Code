#include "stdafx.h"
#include "CPlayer_BattleAni.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
CPlayer_BattleAni::CPlayer_BattleAni()
{
	SetObjtype(OBJ_TYPE::DEFAULT);
}

CPlayer_BattleAni::~CPlayer_BattleAni()
{
}

void CPlayer_BattleAni::init()
{
	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"battleplayerani");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"battleplayerani", L"Texture//Battle//battleplayerani.bmp");
	}


	CAnimator* pAnimator = new CAnimator;
	
	pAnimator->AddAnimation(L"battle_player", m_pTex, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 5, 0.3f);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	pAnimator->Play(L"battle_player", false);
	AddAnimator(pAnimator);
}

void CPlayer_BattleAni::update()
{
	if(GetPos().x>-192)
	{ 
	float x = GetPos().x- fDT * 300;
	SetPos(Vec2(x,GetPos().y));
	}
}

void CPlayer_BattleAni::render(HDC _dc)
{
	if (nullptr != GetAnimator())
		GetAnimator()->render(_dc);
}
