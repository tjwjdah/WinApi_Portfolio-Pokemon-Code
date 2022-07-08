#include "stdafx.h"
#include "CEvolutionMgr.h"
#include "CObjectMgr.h"
#include "CPokemon.h"
#include "CTextBar.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CStartScene.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CResMgr.h"

#include "CWingAttack.h"
#include "CSound.h"
#include "CSoundMgr.h"
CEvolutionMgr::CEvolutionMgr()
:m_prePokemon(nullptr),
m_EvoPokemon(nullptr),
m_on(false),
m_page(0)
{

}

CEvolutionMgr::~CEvolutionMgr()
{
	for (size_t i = 0; i < EvoPokemon.size(); i++)
	{
		delete EvoPokemon[i];
	}
	for (size_t i = 0; i < deletePokemon.size(); i++)
	{
		delete deletePokemon[i];
	}
}

void CEvolutionMgr::init()
{
	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Evolution.wav", L"Sound\\Evolution.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\FanfareEvolutionCongratulations.wav", L"Sound\\FanfareEvolutionCongratulations.wav");

	CPokemon* Pokemon =  CObjectMgr::GetInst()->FindPokemon(L"Ivysaur");
	Pokemon->SetLv(16);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"�̻��ؾ�", 16, Pokemon);

	 Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Venusaur");
	Pokemon->SetLv(32);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"�̻���Ǯ", 32, Pokemon);

	 Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Charmeleon");
	Pokemon->SetLv(16);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"���̸�", 16, Pokemon);

	Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Charizard");
	Pokemon->SetLv(36);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"���ڵ�", 32, Pokemon);

	 Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Wartortle");
	Pokemon->SetLv(16);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"���α�", 16, Pokemon);

	 Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Blastoise");
	Pokemon->SetLv(36);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"��Ϻα�", 36, Pokemon);

	Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Pidgeotto");
	CSkill* sk = new CWingAttack();
	Pokemon->SetLv(18);
	Pokemon->SetSkill2(sk);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"����", 18, Pokemon);

	Pokemon = CObjectMgr::GetInst()->FindPokemon(L"Pidgeot");
	Pokemon->SetLv(36);
	Pokemon->init();
	Pokemon->SetPlayerown(true);
	Pokemon->SetPos(Vec2(160.f, 232.f));
	SetEvoP(L"����", 36, Pokemon);
}

void CEvolutionMgr::update(CPokemon* _Pokemon, int _i)
{

	for (size_t i = 0; i < PrePokemon.size() ; i++)
	{
		
		if (_Pokemon->GetpName() == PrePokemon[i].c_str() && _Pokemon->GetLv() == LvupPokemon[i])
		{
			CScene* scene = CSceneMgr::GetInst()->GetCurScene();
			CStartScene* sscene = dynamic_cast<CStartScene*>(scene);
			sscene->SetpreCamera();
			m_prePokemon = _Pokemon->GetTexture();
			m_EvoPokemon = EvoPokemon[i]->GetTexture();
			CPokemon* pokemon = EvoPokemon[i]->Clone();
			pokemon->SetPlayerown(true);

			sscene->GetPlayer()->Setbattle(true);
			sscene->GetTextBar()->SetUse(true);
			wstring s = L"����!? " + _Pokemon->GetpName() + L"�� �����\n";
			sscene->GetTextBar()->pushnexttext(s.c_str());
			s = L"�����մϴ�! " + _Pokemon->GetpName() + L"��(��) " + pokemon->GetpName() + L"(��)�� ��ȭ�߽��ϴ�!\n";
			sscene->GetTextBar()->pushtext(s.c_str());

			deletePokemon.push_back(sscene->GetPlayer()->GetPokemonMember()[_i]);
			
			sscene->GetPlayer()->GetPokemonMember()[_i] = pokemon;
			m_on = true;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Evolution.wav");
			pNewSound->SetVolume(100);
			pNewSound->PlayToBGM(false);
			m_page = 0;
			CCamera::GetInst()->Setcamera(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f));
		}
	}
	if (m_on)
	{
		if (m_page == 4)
		{
		m_on = false;
		CScene* scene = CSceneMgr::GetInst()->GetCurScene();
		CStartScene* sscene = dynamic_cast<CStartScene*>(scene);
		sscene->GetPlayer()->Setbattle(false);
		sscene->GetTextBar()->SetUse(false);
		CCamera::GetInst()->Setcamera(sscene->GetpreCamera());
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Pallet-Town-Theme.wav");
		pNewSound->SetVolume(100);
		pNewSound->PlayToBGM();
		}
	}
}

void CEvolutionMgr::render(HDC _dc)
{
	if (!m_on)
		return;
	
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			m_page++;
		}
		
		if (m_page==1)
		{
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\FanfareEvolutionCongratulations.wav");
			pNewSound->SetVolume(100);
			pNewSound->Play();
			m_page++;
		}

	Vec2 v2 = CCamera::GetInst()->GetLookAt();
	if (m_page <1)
	{
		
		TransparentBlt(_dc
			,  352.f
			,  192.f
			, m_prePokemon->Width(), m_prePokemon->Height() / 2
			, m_prePokemon->GetDC()
			, 0, 0
			, m_prePokemon->Width(), m_prePokemon->Height() / 2
			, RGB(255, 0, 255));
	}
	if (m_page >= 1)
	{
		TransparentBlt(_dc
			,  352.f
			,  192.f
			, m_EvoPokemon->Width(), m_EvoPokemon->Height() / 2
			, m_EvoPokemon->GetDC()
			, 0,0
			, m_EvoPokemon->Width(), m_EvoPokemon->Height() / 2
			, RGB(255, 0, 255));
	}
}

void CEvolutionMgr::SetEvoP(const wstring& _Pre, int _lv, CPokemon* _Evo)
{
	PrePokemon.push_back(_Pre);
	LvupPokemon.push_back(_lv);
	EvoPokemon.push_back(_Evo);

}
