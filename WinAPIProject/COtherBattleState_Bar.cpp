#include "stdafx.h"
#include "COtherBattleState_Bar.h"

#include "CTimeMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CPokemon.h"

COtherBattleState_Bar::COtherBattleState_Bar():
	m_starani_y1(-1400),
	m_pPokemon(nullptr),
	hpbar(1),
	hpbar2(1)
{

	m_pProgressBar = CResMgr::GetInst()->FindTexture(L"hp_progress");
	if (nullptr == m_pProgressBar)
	{
		m_pProgressBar = CResMgr::GetInst()->LoadTexture(L"hp_progress", L"Texture//Battle//hp_progress.bmp");
	}
	m_pProgressBar2 = CResMgr::GetInst()->FindTexture(L"hp_progress2");
	if (nullptr == m_pProgressBar2)
	{
		m_pProgressBar2 = CResMgr::GetInst()->LoadTexture(L"hp_progress2", L"Texture//Battle//hp_progress2.bmp");
	}
	m_pProgressBar3 = CResMgr::GetInst()->FindTexture(L"hp_progress3");
	if (nullptr == m_pProgressBar3)
	{
		m_pProgressBar3 = CResMgr::GetInst()->LoadTexture(L"hp_progress3", L"Texture//Battle//hp_progress3.bmp");
	}


	SetObjtype(OBJ_TYPE::UI);
}

COtherBattleState_Bar::~COtherBattleState_Bar()
{


}

void COtherBattleState_Bar::SetPokemon(CPokemon* _Pokemon)
{

	m_pPokemon = _Pokemon;
	hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
	hpbar = hpbar2;
	
}

void COtherBattleState_Bar::render(HDC _dc)
{

	if (GetUse())
	{
		if (nullptr == GetTexture())
			return;

		int iWidth = GetTexture()->Width();
		int iHeight = GetTexture()->Height();
		TransparentBlt(_dc
			, (int)GetFinalPos().x + m_starani_y1
			, (int)GetFinalPos().y
			, iWidth, iHeight
			, GetTexture()->GetDC()
			, 0, 0
			, iWidth, iHeight
			, RGB(255, 0, 255));

		HFONT myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
		HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
		SetBkMode(_dc, TRANSPARENT);
		SetTextColor(_dc, RGB(0, 0, 0));
		TextOut(_dc, GetPos().x + 50 + m_starani_y1, GetPos().y + 16, m_pPokemon->GetpName().c_str(), m_pPokemon->GetpName().size());
		SelectObject(_dc, oldFont);
		DeleteObject(myFont);

		wstring Lv = std::to_wstring(m_pPokemon->GetLv());

		myFont = CreateFont(52, 15, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
		oldFont = (HFONT)SelectObject(_dc, myFont);
		SetBkMode(_dc, TRANSPARENT);
		SetTextColor(_dc, RGB(0, 0, 0));
		TextOut(_dc, GetPos().x + 340 + m_starani_y1, GetPos().y + 14, Lv.c_str(), Lv.size());
		SelectObject(_dc, oldFont);
		DeleteObject(myFont);

		hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
		if (hpbar > 64)
			hpbar = 64;
		if (hpbar2 < hpbar)
		{
			hpbar--;
		}
		else if (hpbar2 > hpbar)
		{
			hpbar++;
		}

		if (hpbar > 32)
		{
			for (int i = 0; i < hpbar; i++)
				BitBlt(_dc
					, (int)GetFinalPos().x + m_starani_y1 + 168 + (i * 3)
					, (int)GetFinalPos().y + 80
					, m_pProgressBar->Width()
					, m_pProgressBar->Height()
					, m_pProgressBar->GetDC()
					, 0
					, 0, SRCCOPY);
		}
		else if (hpbar > 13)
		{
			for (int i = 0; i < hpbar; i++)
				BitBlt(_dc
					, (int)GetFinalPos().x + m_starani_y1 + 168 + (i * 3)
					, (int)GetFinalPos().y + 80
					, m_pProgressBar2->Width()
					, m_pProgressBar2->Height()
					, m_pProgressBar2->GetDC()
					, 0
					, 0, SRCCOPY);
		}
		else
		{
			for (int i = 0; i < hpbar; i++)
				BitBlt(_dc
					, (int)GetFinalPos().x + m_starani_y1 + 168 + (i * 3)
					, (int)GetFinalPos().y + 80
					, m_pProgressBar3->Width()
					, m_pProgressBar3->Height()
					, m_pProgressBar3->GetDC()
					, 0
					, 0, SRCCOPY);
		}
	}
}

void COtherBattleState_Bar::update()
{
	if (GetUse())
	{
		if (m_starani_y1 < 0)
		{
			m_starani_y1 += fDT * 500;
			hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
			hpbar = hpbar2;
			
		}
	}
	//` += fDT * 500;
}
