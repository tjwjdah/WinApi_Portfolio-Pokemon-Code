#include "stdafx.h"
#include "CPokemonMemberCount.h"


#include "CResMgr.h"
#include "CTexture.h"
#include "CPokemon.h"
CPokemonMemberCount::CPokemonMemberCount() :m_Player(false)
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"MemberCountMonsterball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"MemberCountMonsterball", L"Texture//TrainerBattle//MemberCountMonsterball.bmp");
	}
	m_pTex2 = CResMgr::GetInst()->FindTexture(L"DMemberCountMonsterball");
	if (nullptr == m_pTex2)
	{
		m_pTex2 = CResMgr::GetInst()->LoadTexture(L"DMemberCountMonsterball", L"Texture//TrainerBattle//DMemberCountMonsterball.bmp");
	}

}

CPokemonMemberCount::~CPokemonMemberCount()
{
}

void CPokemonMemberCount::render(HDC _dc)
{
	if (!GetUse())
		return;
	if (GetTexture() == nullptr)
		return;
	if (m_Player)
	{
		TransparentBlt(_dc
			, 544
			, 352
			, GetTexture()->Width(), GetTexture()->Height()
			, GetTexture()->GetDC()
			, 0, 0
			, GetTexture()->Width(), GetTexture()->Height()
			, RGB(255, 0, 255));
		for (size_t i = 0; i < m_pokemonmember.size(); i++)
		{
			if (m_pokemonmember[i] != nullptr && m_pokemonmember[i]->GetmHP() > 0)
				TransparentBlt(_dc
					, 624 + 40 * i
					, 352
					, m_pTex->Width(), m_pTex->Height()
					, m_pTex->GetDC()
					, 0, 0
					, m_pTex->Width(), m_pTex->Height()
					, RGB(255, 0, 255));
			else if (m_pokemonmember[i] != nullptr && m_pokemonmember[i]->GetmHP() <= 0)
			{
				TransparentBlt(_dc
					, 624 + 40 * i
					, 352
					, m_pTex2->Width(), m_pTex2->Height()
					, m_pTex2->GetDC()
					, 0, 0
					, m_pTex2->Width(), m_pTex2->Height()
					, RGB(255, 0, 255));
			}
		}
	}
	else
	{
		TransparentBlt(_dc
			, 0
			, 128
			, GetTexture()->Width(), GetTexture()->Height()
			, GetTexture()->GetDC()
			, 0, 0
			, GetTexture()->Width(), GetTexture()->Height()
			, RGB(255, 0, 255));
		for (size_t i = 0; i < m_pokemonmember.size(); i++)
		{
			if (m_pokemonmember[i] != nullptr && m_pokemonmember[i]->GetmHP() > 0)
				TransparentBlt(_dc
					, 304 -40  * i
					, 136
					, m_pTex->Width(), m_pTex->Height()
					, m_pTex->GetDC()
					, 0, 0
					, m_pTex->Width(), m_pTex->Height()
					, RGB(255, 0, 255));
			else if (m_pokemonmember[i] != nullptr && m_pokemonmember[i]->GetmHP() <= 0)
			{
				TransparentBlt(_dc
					, 304 - 40 * i
					, 136
					, m_pTex2->Width(), m_pTex2->Height()
					, m_pTex2->GetDC()
					, 0, 0
					, m_pTex2->Width(), m_pTex2->Height()
					, RGB(255, 0, 255));
			}
		}
	}
}

void CPokemonMemberCount::update()
{
	if (!GetUse())
		return;
}
