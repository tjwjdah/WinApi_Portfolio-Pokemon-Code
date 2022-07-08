#include "stdafx.h"
#include "CThrowPokeball.h"


#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CBattleScene.h"

#include "CPokemon.h"
#include "CTextBar.h"
#include "CBattleChoice.h"

#include "CKeyMgr.h"
#include "CPlayer.h"


#include "CSound.h"
CThrowPokeball::CThrowPokeball() :m_gravity(-650.f), m_anion(false), m_page(0),m_pTex(nullptr), m_r(0)
{
	SetObjtype(OBJ_TYPE::DEFAULT);
}

CThrowPokeball::~CThrowPokeball()
{
}

void CThrowPokeball::init()
{
	srand((unsigned int)time(0));
	m_pTex = CResMgr::GetInst()->FindTexture(L"Pocketball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Pocketball", L"Texture//monsterball//Pocketball.bmp");
	}
	m_r = rand() % 10;
	CAnimator* pAnimator = new CAnimator;

	pAnimator->AddAnimation(L"throwball", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), 5, 0.2f);

	m_pTex = CResMgr::GetInst()->FindTexture(L"PocketballCatch");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"PocketballCatch", L"Texture//monsterball//PocketballCatch.bmp");
	}

	pAnimator->AddAnimation(L"throwball2", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f),36, 0.1f);
	AddAnimator(pAnimator);
	CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
	CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scenc);
	battlescene->GetTextBar()->pushnexttext(L"레드는(은)                    몬스터볼을 사용했다!\n");
	battlescene->Getbattlechoice()->SetShow2(false);

	

}

void CThrowPokeball::update()
{
	
	if (m_page == 0)
	{
		m_gravity += (fDT * 1000);
		float x = GetPos().x + fDT * 450;
		float y = GetPos().y + fDT * m_gravity;
		SetPos(Vec2(x, y));
		if (m_gravity > 492)
			m_page++;
	}
	if (m_page == 2)
	{
		if (GetAnimator()->GetCurAnimation()->GetCurFrmldx()>2)
		{
			CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
			CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scenc);
			battlescene->GetoPokemon()->SetShow(false);
		}
		if (GetAnimator()->GetCurAnimation()->GetCurFrmldx() >= GetAnimator()->GetCurAnimation()->GetCurMaxFrmIdx())
			m_page++;
	}
	if (m_page == 3)
	{
		float y = GetPos().y + fDT *400;
		SetPos(Vec2(GetPos().x, y));
		if (GetPos().y > 240)
		{
			m_page++;
		}
	}
	if (m_page ==5)
	{

		if (m_r <= 5)
		{
			if (GetAnimator()->GetCurAnimation()->GetCurFrmldx() >= GetAnimator()->GetCurAnimation()->GetCurMaxFrmIdx())
			{
				CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
				CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scenc);
				wstring s = L"신난다! " + battlescene->GetoPokemon()->GetpName() + L"를(을) 잡았다!\n";
				battlescene->GetTextBar()->pushnexttext(s);
				CPokemon* Pokemon = battlescene->GetoPokemon()->Clone();
				Pokemon->SetPlayerown(true);
				Pokemon->SetPos(Vec2(160.f, 232.f));
				battlescene->GetPlayer()->GetPokemonMember().push_back(Pokemon);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Fanfare-TM-&-HM-Get-(RS).wav");
				pNewSound->PlayToBGM(false);
				pNewSound->SetVolume(90.f);
				m_page++;
			}
		}
		else
		{
			if (GetAnimator()->GetCurAnimation()->GetCurFrmldx() >= 15)
			{
				GetAnimator()->GetCurAnimation()->SetFrameIdx(35);
				CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
				CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scenc);
				battlescene->Getbattlechoice()->SetShow2(true);
				battlescene->Getbattlechoice()->SetShow(false);
				battlescene->GetoPokemon()->SetShow(true);

				battlescene->timeskillpush(nullptr);

				m_page=7;
			}
		}
	}
	
}

void CThrowPokeball::render(HDC _dc)
{

	if (m_pTex != nullptr) {
		if (m_page == 0)
		{
			BLENDFUNCTION ftn = {};

			ftn.BlendOp = AC_SRC_OVER;
			ftn.AlphaFormat = AC_SRC_ALPHA;
			ftn.SourceConstantAlpha = 255;
			AlphaBlend(_dc
				, (int)GetPos().x
				, (int)GetPos().y
				, 64
				, 64
				, m_pTex->GetDC()
				, 0
				, 0
				, 64
				, 64
				, ftn);
		}
		if (m_page == 1)
		{
			GetAnimator()->Play(L"throwball", false);
			m_page++;
		}
		if (m_page == 3)
		{
			BLENDFUNCTION ftn = {};

			ftn.BlendOp = AC_SRC_OVER;
			ftn.AlphaFormat = AC_SRC_ALPHA;
			ftn.SourceConstantAlpha = 255;
			AlphaBlend(_dc
				, (int)GetPos().x
				, (int)GetPos().y
				, 64
				, 64
				, m_pTex->GetDC()
				, 0
				, 0
				, 64
				, 64
				, ftn);
		}
		if (m_page ==4)
		{
			GetAnimator()->Play(L"throwball2", false);
			m_page++;
		}
		if (m_page == 6)
		{
			BLENDFUNCTION ftn = {};

			ftn.BlendOp = AC_SRC_OVER;
			ftn.AlphaFormat = AC_SRC_ALPHA;
			ftn.SourceConstantAlpha = 255;
			AlphaBlend(_dc
				, (int)GetPos().x
				, (int)GetPos().y
				, 64
				, 64
				, m_pTex->GetDC()
				, 2240
				, 0
				, 64
				, 64
				, ftn);
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
				CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scenc);
				ChangeScene(SCENE_TYPE::START);
			}
		}
	}

	
GetAnimator()->render(_dc);
}
