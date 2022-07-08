#include "stdafx.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CEventMgr.h"

#include "CPokemon.h"

#include "CBattleScene.h"
#include "CStartScene.h"

#include "CObjectMgr.h"

#include "CPokemonSpawnObj.h"
#include "CPokemonSwap.h"
#include "CBag.h"
#include "CMonsterball.h"
#include "CTextBar.h"
#include "CGreen.h"
#include "CTrainerBattle.h"
#include "CNurse.h"
#include "CDocter.h"
#include "CPokeball.h"

#include "CPsybeam.h"
#include "CVineWhip.h"
#include "CFlamethrower.h"
#include "CThunder.h"

#include "CSound.h"
#include "CSoundMgr.h"
CPlayer::CPlayer()
	: m_pTex(nullptr)
	, m_iHP(10)
	, m_eDir(DIR::DOWN)
	, m_eState(PLAYER_STATE::IDLE)
	, m_ePrevDir(DIR::NONE)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_fMoveSpeed(256.f)
	, m_pMoveTime(0.0f)
	, m_pMovebool(false)
	, m_pMoveTime2(0.0f)
	, m_ePrePos(0.f,0.f)
	, m_pbattleon(false)
	, m_pBag(nullptr)
	, m_pokemonspawnon(true)
{
	SetObjtype(OBJ_TYPE::PLAYER);
}

CPlayer::~CPlayer()
{
	for (size_t i = 0; i<m_PokemonMember.size(); i++)
	{
		if (m_PokemonMember[i] != nullptr)
			delete m_PokemonMember[i];
	}
	delete m_pBag;
}

void CPlayer::init()
{
	/*
	// 텍스쳐 로딩
	m_pTex = CResMgr::GetInst()->FindTexture(L"Player");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"Texture\\Player.bmp");
	*/
	// 충돌체 생성
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f, 32.f));
	pCollider->SetScale(Vec2(63.f, 63.f));
	AddCollider(pCollider);

	// 애니메이터 생성
	CTexture* pAnimTex = CResMgr::GetInst()->LoadTexture(L"player", L"Texture\\player_a.bmp");
	
	CAnimator* pAnimator = new CAnimator;

	pAnimator->AddAnimation(L"IDLE_DOWN", pAnimTex, Vec2(0.f, 0.f), Vec2(64.f, 80.f), 1, 0.05f);
	pAnimator->AddAnimation(L"IDLE_LEFT", pAnimTex, Vec2(128.f, 0.f), Vec2(64.f, 80.f), 1, 0.05f);
	pAnimator->AddAnimation(L"IDLE_UP", pAnimTex, Vec2(64.f, 0.f), Vec2(64.f, 80.f), 1, 0.05f);
	pAnimator->AddAnimation(L"IDLE_RIGHT", pAnimTex, Vec2(192.f, 0.f), Vec2(64.f, 80.f), 1, 0.05f);

	pAnimTex = CResMgr::GetInst()->LoadTexture(L"playerdown", L"Texture\\playerwalkdown_a.bmp");
	pAnimator->AddAnimation(L"WALK_DOWN", pAnimTex, Vec2(0.f, 0.f), Vec2(64.f, 80.f), 3, 0.3f);

	pAnimTex = CResMgr::GetInst()->LoadTexture(L"playerleft", L"Texture\\playerwalkleft_a.bmp");
	pAnimator->AddAnimation(L"WALK_LEFT", pAnimTex, Vec2(0.f, 0.f), Vec2(64.f, 80.f), 3, 0.3f);

	pAnimTex = CResMgr::GetInst()->LoadTexture(L"playerup", L"Texture\\playerwalkup_a.bmp");
	pAnimator->AddAnimation(L"WALK_UP", pAnimTex, Vec2(0.f, 0.f), Vec2(64.f, 80.f), 3, 0.3f);

	pAnimTex = CResMgr::GetInst()->LoadTexture(L"playerright", L"Texture\\playerwalkright_a.bmp");
	pAnimator->AddAnimation(L"WALK_RIGHT", pAnimTex, Vec2(0.f, 0.f), Vec2(64.f, 80.f), 3, 0.3f);


	{
	CAnimation* pAnim = pAnimator->GetAnimation(L"IDLE_DOWN");
	tAnimFrame& tFrm = pAnim->GetFrame(0);
	tFrm.vOffset = Vec2(0.f, -16.f);
	pAnim = pAnimator->GetAnimation(L"IDLE_LEFT");
	tAnimFrame& tFrm1 = pAnim->GetFrame(0);
	tFrm1.vOffset = Vec2(0.f, -16.f);
	pAnim = pAnimator->GetAnimation(L"IDLE_UP");
	tAnimFrame& tFrm2 = pAnim->GetFrame(0);
	tFrm2.vOffset = Vec2(0.f, -16.f);
	 pAnim = pAnimator->GetAnimation(L"IDLE_RIGHT");
	tAnimFrame& tFrm3 = pAnim->GetFrame(0);
	tFrm3.vOffset = Vec2(0.f, -16.f);

	pAnim = pAnimator->GetAnimation(L"WALK_DOWN");
	tAnimFrame& tFrm4 = pAnim->GetFrame(0);
	tFrm4.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm5 = pAnim->GetFrame(1);
	tFrm5.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm6 = pAnim->GetFrame(2);
	tFrm6.vOffset = Vec2(0.f, -16.f);

	pAnim = pAnimator->GetAnimation(L"WALK_LEFT");
	tAnimFrame& tFrm7 = pAnim->GetFrame(0);
	tFrm7.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm8 = pAnim->GetFrame(1);
	tFrm8.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm9 = pAnim->GetFrame(2);
	tFrm9.vOffset = Vec2(0.f, -16.f);

	pAnim = pAnimator->GetAnimation(L"WALK_UP");
	tAnimFrame& tFrm10 = pAnim->GetFrame(0);
	tFrm10.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm11 = pAnim->GetFrame(1);
	tFrm11.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm12 = pAnim->GetFrame(2);
	tFrm12.vOffset = Vec2(0.f, -16.f);

	pAnim = pAnimator->GetAnimation(L"WALK_RIGHT");
	tAnimFrame& tFrm13 = pAnim->GetFrame(0);
	tFrm13.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm14 = pAnim->GetFrame(1);
	tFrm14.vOffset = Vec2(0.f, -16.f);
	tAnimFrame& tFrm15 = pAnim->GetFrame(2);
	tFrm15.vOffset = Vec2(0.f, -16.f);

	}
	
	
	
	
	CPokemon* Venusaur = CObjectMgr::GetInst()->FindPokemon(L"Venusaur");
	CSkill* vine = new CVineWhip();
	Venusaur->SetLv(50);
	Venusaur->init();
	Venusaur->SetPlayerown(true);
	Venusaur->SetPos(Vec2(160.f, 232.f));
	Venusaur->SetSkill2(vine);
	m_PokemonMember.push_back(Venusaur);

	

	CPokemon* Charizard = CObjectMgr::GetInst()->FindPokemon(L"Charizard");
	CSkill* Fi = new CFlamethrower();
	Charizard->SetLv(50);
	Charizard->init();
	Charizard->SetPlayerown(true);
	Charizard->SetPos(Vec2(160.f, 232.f));
	Charizard->SetSkill2(Fi);
	m_PokemonMember.push_back(Charizard);

	CPokemon* Pikachu = CObjectMgr::GetInst()->FindPokemon(L"Pikachu");
	CSkill* Th = new CThunder();
	Pikachu->SetLv(80);
	Pikachu->init();
	Pikachu->SetPlayerown(true);
	Pikachu->SetPos(Vec2(160.f, 232.f));
	Pikachu->SetSkill2(Th);
	m_PokemonMember.push_back(Pikachu);


	CPokemon* p = CObjectMgr::GetInst()->FindPokemon(L"Pidgey");
	p->SetLv(17);
	p->init();
	p->SetPlayerown(true);
	p->SetPos(Vec2(160.f, 232.f));
	m_PokemonMember.push_back(p);

	pAnimator->Play(L"IDLE_DOWN", true);

	AddAnimator(pAnimator);

	m_ePrePos = GetPos();

	m_pBag = new CBag();
	m_pBag->init();
	m_pBag->SetUse(false);
	CItem* item = new CMonsterball();
	item->Setamount(99);
	m_pBag->itemadd(item);


	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Fanfare_Pokemon_Acquisition.wav", L"Sound\\Fanfare_Pokemon_Acquisition.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\PokemonRecovery(Unused).wav", L"Sound\\PokemonRecovery(Unused).wav");
}

void CPlayer::update()
{
	/*if (중력 ok, Gounrd 가 아니라면)
	{
		AddForce(Vec2(0.f, 500.f));
	}*/
	
	if (KEY_TAP(KEY_TYPE::ENTER))
	{
		if (m_pokemonspawnon)
			m_pokemonspawnon = false;
		else
			m_pokemonspawnon = true;
		
	}
	CheckAnimation();
	if (m_pbattleon)
		return;
	CheckState();

	CheckAnimation();

	Move();
}

void CPlayer::render(HDC _dc)
{
	// 충돌체 랜더링
	if (nullptr != GetCollider())
		//GetCollider()->render(_dc);

	// Animator 랜더링
	if (nullptr != GetAnimator())
		GetAnimator()->render(_dc);
}


void CPlayer::CheckState()
{	
	// 현재상태를 이전상태로 저장해둠
	m_ePrevState = m_eState;
	m_ePrevDir = m_eDir;
	
		if (PLAYER_STATE::IDLE == m_eState || PLAYER_STATE::MOVE == m_eState)
		{
			// 키 입력에 따라 현재 상태 및 방향이 바뀔 수 있음
			
			if (KEY_TAP(KEY_TYPE::KEY_UP) && m_eDir == DIR::UP)
			{
				GetCollider()->SetScale(Vec2(63.f, 64.f));
				m_eState = PLAYER_STATE::MOVE;
				m_eDir = DIR::UP;
			}
			else if (KEY_TAP(KEY_TYPE::KEY_UP) && m_eDir != DIR::UP && m_eState== PLAYER_STATE::IDLE)
			{
				GetCollider()->SetScale(Vec2(63.f, 64.f));
				m_pMovebool = true;
				m_pMoveTime2 = 0.f;
				m_eDir = DIR::UP;
			}
			else if (KEY_HOLD(KEY_TYPE::KEY_UP) && m_eState == PLAYER_STATE::IDLE && m_pMovebool)
			{

				m_pMoveTime2 += fDT * m_fMoveSpeed;
				if (m_pMoveTime2 >= 100.f)
				{
 					m_pMoveTime2 = 0.f;
					m_eState = PLAYER_STATE::MOVE;
					m_pMovebool = false;
				}
			}
				
			if (KEY_TAP(KEY_TYPE::KEY_DOWN) && m_eDir == DIR::DOWN)
			{
				GetCollider()->SetScale(Vec2(63.f, 64.f));
				m_eState = PLAYER_STATE::MOVE;
				m_eDir = DIR::DOWN;
			}
			else if (KEY_TAP(KEY_TYPE::KEY_DOWN) && m_eDir != DIR::DOWN && m_eState == PLAYER_STATE::IDLE)
			{
				GetCollider()->SetScale(Vec2(63.f, 64.f));
				m_eDir = DIR::DOWN;
				m_pMoveTime2 = 0.f;
				m_pMovebool = true;
			}
			else if (KEY_HOLD(KEY_TYPE::KEY_DOWN) && m_eState == PLAYER_STATE::IDLE && m_pMovebool)
			{
				m_pMoveTime2 += fDT * m_fMoveSpeed;
				if (m_pMoveTime2 >= 100.f)
				{
					m_pMoveTime2 = 0.f;
					m_eState = PLAYER_STATE::MOVE;
					m_pMovebool = false;
				}
			}

			if (KEY_TAP(KEY_TYPE::KEY_LEFT) && m_eDir == DIR::LEFT)
			{
				GetCollider()->SetScale(Vec2(64.f, 63.f));
				m_eState = PLAYER_STATE::MOVE;
				m_eDir = DIR::LEFT;;

			}
			else if (KEY_TAP(KEY_TYPE::KEY_LEFT) && m_eDir != DIR::LEFT && m_eState == PLAYER_STATE::IDLE)
			{
				GetCollider()->SetScale(Vec2(64.f, 63.f));
				m_eDir = DIR::LEFT;
				m_pMoveTime2 = 0.f;
				m_pMovebool = true;
			}
			else if (KEY_HOLD(KEY_TYPE::KEY_LEFT) && m_eState == PLAYER_STATE::IDLE && m_pMovebool)
			{
				m_pMoveTime2 += fDT * m_fMoveSpeed;
				if (m_pMoveTime2 >= 100.f)
				{
					m_pMoveTime2 = 0.f;
					m_eState = PLAYER_STATE::MOVE;
					m_pMovebool = false;
				}
			}

			if (KEY_TAP(KEY_TYPE::KEY_RIGHT) && m_eDir == DIR::RIGHT)
			{
				GetCollider()->SetScale(Vec2(64.f, 63.f));
				m_eState = PLAYER_STATE::MOVE;
				m_eDir = DIR::RIGHT;
			}
			else if (KEY_TAP(KEY_TYPE::KEY_RIGHT) && m_eDir != DIR::RIGHT && m_eState == PLAYER_STATE::IDLE)
			{
				GetCollider()->SetScale(Vec2(64.f, 63.f));
				m_eDir = DIR::RIGHT;
				m_pMoveTime2 = 0.f;
				m_pMovebool = true;
			}
			else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT) && m_eState == PLAYER_STATE::IDLE && m_pMovebool)
			{
				m_eDir = DIR::RIGHT;
				m_pMoveTime2 += fDT * m_fMoveSpeed;
				if (m_pMoveTime2 >= 100.f)
				{
					m_pMoveTime2 = 0.f;
					m_eState = PLAYER_STATE::MOVE;
					m_pMovebool = false;
				}
			}
		}

	
}

void CPlayer::CheckAnimation()
{
	// 상태가 변경된 경우
	if (m_ePrevState != m_eState || m_ePrevDir != m_eDir)
	{
		if (PLAYER_STATE::MOVE == m_eState )
		{
			switch (m_eDir)
			{
			case DIR::UP:
				GetAnimator()->Play(L"WALK_UP", true);
				break;
			case DIR::DOWN:
				GetAnimator()->Play(L"WALK_DOWN", true);
				break;
			case DIR::LEFT:
				GetAnimator()->Play(L"WALK_LEFT", true);
				break;
			case DIR::RIGHT:
				GetAnimator()->Play(L"WALK_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::IDLE == m_eState)
		{
			switch (m_eDir)
			{
			case DIR::UP:
				GetAnimator()->Play(L"IDLE_UP", true);
				break;
			case DIR::DOWN:
				GetAnimator()->Play(L"IDLE_DOWN", true);
				break;
			case DIR::LEFT:
				GetAnimator()->Play(L"IDLE_LEFT", true);
				break;
			case DIR::RIGHT:
				GetAnimator()->Play(L"IDLE_RIGHT", true);
				break;
			}
		}
	}
}

void CPlayer::Move()
{
	if (PLAYER_STATE::MOVE != m_eState)
		return;

	Vec2 vPos = GetPos();

		switch (m_eDir)
		{
		case DIR::UP:
		{
			if (GetCollider()->GetDir() == DIR::UP)
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				if (m_pMoveTime >= 64.f)
				{
					m_eState = PLAYER_STATE::IDLE;

					m_pMoveTime = 0.0f;
					if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{
						m_eDir = DIR::DOWN;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						m_eDir = DIR::LEFT;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
						m_eState = PLAYER_STATE::MOVE;
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						m_eDir = DIR::RIGHT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
				}
			}
			else
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				vPos.y -= fDT * m_fMoveSpeed;
				CCamera::GetInst()->CCameraYUp((-fDT * m_fMoveSpeed));
				if (m_pMoveTime >= 64.f)
				{
						//vPos.y += m_pMoveTime - 64.f;
						vPos.y = m_ePrePos.y - 64.f;
						m_ePrePos.y = vPos.y;
						//vPos.y -= 0.01f;
						m_eState = PLAYER_STATE::IDLE;
						m_pMoveTime = 0.0f;
						
						
						if (KEY_HOLD(KEY_TYPE::KEY_UP))
						{
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
						}
						else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
						{
							m_eDir = DIR::DOWN;
							m_eState = PLAYER_STATE::MOVE;
							GetCollider()->SetScale(Vec2(63.f, 64.f));
						}
						else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
						{
							m_eDir = DIR::LEFT;
							m_eState = PLAYER_STATE::MOVE;
							GetCollider()->SetScale(Vec2(64.f, 63.f));
						}
						else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
						{
							m_eDir = DIR::RIGHT;
							m_eState = PLAYER_STATE::MOVE;
							GetCollider()->SetScale(Vec2(64.f, 63.f));
						}
					}
			}
		}
		break;
		case DIR::DOWN:
		{
			if (GetCollider()->GetDir() == DIR::DOWN)
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				if (m_pMoveTime >= 64.f)
				{
					m_eState = PLAYER_STATE::IDLE;

					m_pMoveTime = 0.0f;

					if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{

						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eDir = DIR::UP;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						m_eDir = DIR::LEFT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						m_eDir = DIR::RIGHT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}

				}
			}
			else
			{ 
			m_pMoveTime += fDT * m_fMoveSpeed;
			vPos.y += fDT * m_fMoveSpeed;
			CCamera::GetInst()->CCameraYUp(fDT* m_fMoveSpeed);
			if (m_pMoveTime >= 64.f)
			{
				//vPos.y -= m_pMoveTime - 64.f;
				vPos.y = m_ePrePos.y + 64.f;
				m_ePrePos.y = vPos.y;
				//vPos.y -= 0.01f;
				m_eState = PLAYER_STATE::IDLE;
				m_pMoveTime = 0.0f;
			
				if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
				{
					m_eState = PLAYER_STATE::MOVE;
					GetCollider()->SetScale(Vec2(63.f, 64.f));
				}
				else if (KEY_HOLD(KEY_TYPE::KEY_UP))
				{
					m_eDir = DIR::UP;
					m_eState = PLAYER_STATE::MOVE;
					GetCollider()->SetScale(Vec2(63.f, 64.f));
				}
				else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
				{
					m_eDir = DIR::LEFT;
					m_eState = PLAYER_STATE::MOVE;
					GetCollider()->SetScale(Vec2(64.f, 63.f));
				}
				else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
				{
					m_eDir = DIR::RIGHT;
					m_eState = PLAYER_STATE::MOVE;
					GetCollider()->SetScale(Vec2(64.f, 63.f));
				}
				}
			}
		}
			break;
		case DIR::LEFT:
			//AddForce(Vec2(-200.f, 0));
		{
			if (GetCollider()->GetDir() == DIR::LEFT)
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				if (m_pMoveTime >= 64.f)
				{
					m_eState = PLAYER_STATE::IDLE;

					m_pMoveTime = 0.0f;

					if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						GetCollider()->SetScale(Vec2(64.f, 63.f));
						m_eState = PLAYER_STATE::MOVE;
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{
						m_eDir = DIR::DOWN;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));

					}
					else if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eDir = DIR::UP;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						GetCollider()->SetScale(Vec2(64.f, 63.f));
						m_eDir = DIR::RIGHT;
						m_eState = PLAYER_STATE::MOVE;
					}

				}
			}
			else
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				vPos.x -= fDT * m_fMoveSpeed;
				CCamera::GetInst()->CCameraXUp(-(fDT* m_fMoveSpeed));
				if (m_pMoveTime >= 64.f)
				{
					//vPos.x += m_pMoveTime - 64.f;
					vPos.x = m_ePrePos.x - 64.f;
					m_ePrePos.x = vPos.x;
					m_eState = PLAYER_STATE::IDLE;
					m_pMoveTime = 0.0f;
					
					if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{
						m_eDir = DIR::DOWN;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eDir = DIR::UP;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						m_eDir = DIR::RIGHT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					
				}
			}
			
		}
			break;
		case DIR::RIGHT:
			//AddForce(Vec2(200.f, 0));
		{
			if (GetCollider()->GetDir() == DIR::RIGHT)
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				if (m_pMoveTime >= 64.f)
				{
					m_eState = PLAYER_STATE::IDLE;

					m_pMoveTime = 0.0f;

					if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						m_eDir = DIR::LEFT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eDir = DIR::UP;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{
						m_eDir = DIR::DOWN;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}

				}
				
			}
			else
			{
				m_pMoveTime += fDT * m_fMoveSpeed;
				vPos.x += fDT * m_fMoveSpeed;
				CCamera::GetInst()->CCameraXUp(fDT* m_fMoveSpeed);
				if (m_pMoveTime >= 64.f)
				{
					//vPos.x -= m_pMoveTime - 64.f;
					vPos.x = m_ePrePos.x + 64.f;
					m_ePrePos.x = vPos.x;
					m_eState = PLAYER_STATE::IDLE;
					m_pMoveTime = 0.0f;
					
					if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
					{
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
					{
						m_eDir = DIR::LEFT;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(64.f, 63.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_UP))
					{
						m_eDir = DIR::UP;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
					else if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
					{
						m_eDir = DIR::DOWN;
						m_eState = PLAYER_STATE::MOVE;
						GetCollider()->SetScale(Vec2(63.f, 64.f));
					}
				}
			}
		}
			break;
	}

	SetPos(vPos);
}
	
void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (m_pokemonspawnon)
	{
		if (nullptr != dynamic_cast<CPokemonSpawnObj*>(_pOther->GetObj()))
		{
			int r = rand() % 100;
			if (r < 20)
			{

				CPokemonSpawnObj* spawn = dynamic_cast<CPokemonSpawnObj*>(_pOther->GetObj());
				CBattleScene* battlescene = dynamic_cast<CBattleScene*>(CSceneMgr::GetInst()->GetBattleScene());
				battlescene->SetPokemon(m_PokemonMember, spawn->PokemonSpawn());
				battlescene->SetPlayer(this);
				CCamera::GetInst()->FadeOut(0.2f);
				CCamera::GetInst()->FadeIn(0.2f);
				CCamera::GetInst()->FadeOut(0.2f);
				CCamera::GetInst()->FadeIn(0.2f);
				CCamera::GetInst()->FadeOut(0.2f);
				CStartScene* Start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
				m_pbattleon = true;
				Start->timeEvenadd(SCENE_TYPE::BATTLE, 1.f);


			}
		}
	}

	if (nullptr == dynamic_cast<CPokemonSpawnObj*>(_pOther->GetObj()))
	{
		if (m_eDir == DIR::RIGHT || m_eDir == DIR::LEFT)
		{
			if (GetCollider()->GetFinalPos().x < _pOther->GetFinalPos().x)
				GetCollider()->SetDir(DIR::RIGHT);
			else if (GetCollider()->GetFinalPos().x > _pOther->GetFinalPos().x)
				GetCollider()->SetDir(DIR::LEFT);
		}
		if (m_eDir == DIR::UP || m_eDir == DIR::DOWN) {
			if (GetCollider()->GetFinalPos().y < _pOther->GetFinalPos().y)
				GetCollider()->SetDir(DIR::DOWN);
			else if (GetCollider()->GetFinalPos().y > _pOther->GetFinalPos().y)
				GetCollider()->SetDir(DIR::UP);
		}
	}

}

void CPlayer::OnCollision(CCollider* _pOther)
{
	if (nullptr != dynamic_cast<CGreen*>(_pOther->GetObj()))
	{
		/*if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			if (dynamic_cast<CGreen*>(_pOther->GetObj())->GetOn())
			{
				CStartScene* start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
				start->GetTextBar()->pushnexttext(dynamic_cast<CGreen*>(_pOther->GetObj())->Getscript());
				start->GetTextBar()->SetUse(true);
				start->GetTextBar()->pushnexttext(L"테스트\n");
				dynamic_cast<CGreen*>(_pOther->GetObj())->SetOn(false);
				
			}
		}*/
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			CStartScene* start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
			if (!dynamic_cast<CGreen*>(_pOther->GetObj())->GetOn())
			{
				if (!start->GetTextBar()->GetUse())
				{
					CTrainerBattle* TrainerBattle = dynamic_cast<CTrainerBattle*>(CSceneMgr::GetInst()->GetTrainerBattle());
					TrainerBattle->SetPlayer(this, dynamic_cast<CGreen*>(_pOther->GetObj()));

					ChangeScene(SCENE_TYPE::TRAINERBATTLE);
				}
				
			}
			else
			{

				start->GetTextBar()->pushnexttext(L"여어, 레드 온 거냐! 하하, 기쁘군! 라이벌인 네가 약하다면 싸울 맛이 안나니까 말이야!\n");
				start->GetTextBar()->pushtext(L"지금 나는 포켓몬 리그 정점에 있어! 레드 이게 무슨 의미인지 알겠나? \n");
				start->GetTextBar()->pushtext(L"알았어 가르쳐주지! 바로 내가! 이 세상에서 가장! 강하다는거야!\n");
				start->GetTextBar()->SetUse(true);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);

				dynamic_cast<CGreen*>(_pOther->GetObj())->SetOn(false);
				//dynamic_cast<CDocter*>(_pOther->GetObj())->SetOn(true);
			}

		}

	}else if (nullptr != dynamic_cast<CNurse*>(_pOther->GetObj()))
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			CStartScene* start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
			if (dynamic_cast<CNurse*>(_pOther->GetObj())->GetOn())
			{
				start->GetTextBar()->pushnexttext(L"포켓몬을 회복시키겠습니다.\n");
				start->GetTextBar()->SetUse(true);
				start->GetNurse()->SetPokeball(m_PokemonMember.size());
				for (size_t i = 0; i < m_PokemonMember.size(); i++)
				{
					m_PokemonMember[i]->SetHp(m_PokemonMember[i]->Getm_maxhp());
				}
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\PokemonRecovery(Unused).wav");
				pNewSound->Play(false);
				pNewSound->SetVolume(100.f);

				dynamic_cast<CNurse*>(_pOther->GetObj())->SetOn(false);
			}
			else
			{
				start->GetNurse()->SetPokeball(0);
				dynamic_cast<CNurse*>(_pOther->GetObj())->SetOn(true);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
			}
			
		}
	}
	else if (nullptr != dynamic_cast<CDocter*>(_pOther->GetObj()))
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			CStartScene* start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
			if (!dynamic_cast<CDocter*>(_pOther->GetObj())->GetOn())
			{
				if(!start->GetTextBar()->GetUse())
					dynamic_cast<CDocter*>(_pOther->GetObj())->SetOn(true);
			}
			else
			{
				start->GetTextBar()->pushnexttext(L"자 레드! 책상위에 있는 3개의 몬스터볼에는 각각 다른 포켓몬이 들어있단다!\n");
				start->GetTextBar()->pushtext(L"차분히 생각해서 정하는게 좋을꺼다.\n");
				start->GetTextBar()->SetUse(true);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);

				dynamic_cast<CDocter*>(_pOther->GetObj())->SetOn(false);
				//dynamic_cast<CDocter*>(_pOther->GetObj())->SetOn(true);
			}

		}
	}
	else if (nullptr != dynamic_cast<CPokeball*>(_pOther->GetObj()))
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			CStartScene* start = dynamic_cast<CStartScene*>(CSceneMgr::GetInst()->GetCurScene());
			if (!(dynamic_cast<CPokeball*>(_pOther->GetObj())->GetOn()))
			{
				if (dynamic_cast<CPokeball*>(_pOther->GetObj())->GetYes())
				{
					CPokemon* pokemon = dynamic_cast<CPokeball*>(_pOther->GetObj())->GetPokemon()->Clone();
					pokemon->SetPlayerown(true);
					m_PokemonMember.push_back(pokemon);
					dynamic_cast<CPokeball*>(_pOther->GetObj())->SetOn(true);

					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Fanfare_Pokemon_Acquisition.wav");
					pNewSound->Play(false);
					pNewSound->SetVolume(90.f);

					DeleteObject(dynamic_cast<CPokeball*>(_pOther->GetObj()));
					
					m_pbattleon = false;
					
				}
				else
				{
					m_pbattleon = false;
					dynamic_cast<CPokeball*>(_pOther->GetObj())->SetOn(true);
					dynamic_cast<CPokeball*>(_pOther->GetObj())->SetYes(true);
				}
			}
			else
			{
				if (dynamic_cast<CPokeball*>(_pOther->GetObj())->GetPokemon()->GetPokemonType1() == POKEMON_TYPE::FIRE)
					start->GetTextBar()->pushnexttext(L"레드는 불 포켓몬 파이리로 할거니?!\n");
				else if(dynamic_cast<CPokeball*>(_pOther->GetObj())->GetPokemon()->GetPokemonType1() == POKEMON_TYPE::WATER)
					start->GetTextBar()->pushnexttext(L"레드는 물 포켓몬 꼬부기로 할거니?!\n");
				else if (dynamic_cast<CPokeball*>(_pOther->GetObj())->GetPokemon()->GetPokemonType1() == POKEMON_TYPE::GRASS)
					start->GetTextBar()->pushnexttext(L"레드는 풀 포켓몬 이상해씨로 할거니?!\n");
				start->GetTextBar()->SetUse(true);

				m_pbattleon = true;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);

				dynamic_cast<CPokeball*>(_pOther->GetObj())->SetOn(false);
			}

		}
	}
	
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{


}

