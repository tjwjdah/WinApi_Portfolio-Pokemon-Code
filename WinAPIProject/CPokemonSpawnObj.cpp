#include "stdafx.h"
#include "CPokemonSpawnObj.h"

#include "CObjectMgr.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"

#include "CPokemon.h"
#include "CThunder.h"
CPokemonSpawnObj::CPokemonSpawnObj():
	m_pTex(nullptr)
{
	SetObjtype(OBJ_TYPE::POKEMONSPAWNOBJ);
}

CPokemonSpawnObj::~CPokemonSpawnObj()
{
}

CPokemonSpawnObj::CPokemonSpawnObj(const CPokemonSpawnObj& _origin)
	:CObj(_origin),
	m_pTex(_origin.m_pTex)
{
}

void CPokemonSpawnObj::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CPokemonSpawnObj::update()
{
}

void CPokemonSpawnObj::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (nullptr != GetCollider())
	//	GetCollider()->render(_dc);

	if (m_pTex != nullptr) {
		BLENDFUNCTION ftn = {};

		ftn.BlendOp = AC_SRC_OVER;
		ftn.AlphaFormat = AC_SRC_ALPHA;
		ftn.SourceConstantAlpha = 255;
		AlphaBlend(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, m_pTex->Width()
			, m_pTex->Height()
			, m_pTex->GetDC()
			, 0
			, 0
			, m_pTex->Width()
			, m_pTex->Height()
			, ftn);
	}
}

void CPokemonSpawnObj::OnCollisionEnter(CCollider* _pOther)
{
	

}

CPokemon* CPokemonSpawnObj::PokemonSpawn()
{

	int r = rand() % 5;
	CPokemon* pokemon = nullptr;
	switch (r)
	{
	case 0:
		pokemon =CObjectMgr::GetInst()->FindPokemon(L"Pidgey");
		pokemon->SetLv(4);
		pokemon->init();
		return pokemon;
		break;
	case 1:
		pokemon = CObjectMgr::GetInst()->FindPokemon(L"Pidgey");
		pokemon->SetLv(5);
		pokemon->init();
		return pokemon;
		break;
	case 2:
		pokemon = CObjectMgr::GetInst()->FindPokemon(L"Rattata");
		pokemon->SetLv(4);
		pokemon->init();
		return pokemon;
		break;
	case 3:
		pokemon = CObjectMgr::GetInst()->FindPokemon(L"Rattata");
		pokemon->SetLv(5);
		pokemon->init();
		return pokemon;
		break;
	case 4:
		pokemon = CObjectMgr::GetInst()->FindPokemon(L"Pikachu");
		CSkill* Th =new CThunder();
		pokemon->SetLv(5);
		pokemon->SetSkill2(Th);
		pokemon->init();
		return pokemon;
		break;
	}

}
