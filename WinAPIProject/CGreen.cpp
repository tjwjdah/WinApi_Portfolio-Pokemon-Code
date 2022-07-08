#include "stdafx.h"
#include "CGreen.h"
#include "CTexture.h"

#include "CResMgr.h"

#include "CObjectMgr.h"
#include "CPokemon.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CPlayer.h"

#include "CHydroPump.h"
#include "CFlamethrower.h"
#include "CPsybeam.h"

CGreen::CGreen() :
	m_pTex(nullptr),
	m_BattleTex(nullptr),
	m_on(true)
{
	SetObjtype(OBJ_TYPE::TRAINER);
}

CGreen::~CGreen()
{
	for (size_t i = 0; i < m_PokemonMember.size(); i++)
	{
		if (m_PokemonMember[i] != nullptr)
			delete m_PokemonMember[i];
	}
	
}

void CGreen::init()
{
	m_pTex= CResMgr::GetInst()->FindTexture(L"green2");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"green2", L"Texture\\TrainerBattle\\Trainer\\green2.bmp");


	m_BattleTex = CResMgr::GetInst()->FindTexture(L"battlegreen");
	if (nullptr == m_BattleTex)
		m_BattleTex = CResMgr::GetInst()->LoadTexture(L"battlegreen", L"Texture\\TrainerBattle\\Trainer\\battlegreen.bmp");


	CPokemon* Blastoise = CObjectMgr::GetInst()->FindPokemon(L"Blastoise");
	CSkill* hy = new CHydroPump();
	Blastoise->SetSkill2(hy);
	Blastoise->SetLv(40);
	Blastoise->init();
	Blastoise->SetPos(Vec2(588.f, 48.f));
	m_PokemonMember.push_back(Blastoise);

	CPokemon* Alakazam = CObjectMgr::GetInst()->FindPokemon(L"Alakazam");
	CSkill* Psy = new CPsybeam();
	Alakazam->SetSkill2(Psy);
	Alakazam->SetLv(40);
	Alakazam->init();
	Alakazam->SetPos(Vec2(588.f, 48.f));
	m_PokemonMember.push_back(Alakazam);

	CPokemon* Arcanine = CObjectMgr::GetInst()->FindPokemon(L"Arcanine");
	CSkill* Fl = new CFlamethrower();
	Arcanine->SetSkill2(Fl);
	Arcanine->SetLv(40);
	Arcanine->init();
	Arcanine->SetPos(Vec2(588.f, 48.f));
	m_PokemonMember.push_back(Arcanine);


	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f, 32.f));
	pCollider->SetScale(Vec2(64.f, 64.f));
	AddCollider(pCollider);
	m_script = L"테스트\n";
	m_name = L"그린";
}

void CGreen::update()
{
}

void CGreen::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	TransparentBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y - 16
		, m_pTex->Width(), m_pTex->Height()
		, m_pTex->GetDC()
		, 0, 0
		, m_pTex->Width(), m_pTex->Height()
		, RGB(255, 0, 255));

}
