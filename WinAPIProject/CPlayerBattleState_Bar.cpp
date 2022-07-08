#include "stdafx.h"
#include "CPlayerBattleState_Bar.h"

#include "CTimeMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CPokemon.h"

CPlayerBattleState_Bar::CPlayerBattleState_Bar() :m_starani_y1(500),
m_pPokemon(nullptr),
a(0),
hpbar(0),
hpbar2(0),
expbar(0),
expbar2(0)
{

	m_pProgressBar_exp = CResMgr::GetInst()->FindTexture(L"exp_progress");
	if (nullptr == m_pProgressBar_exp)
	{
		m_pProgressBar_exp = CResMgr::GetInst()->LoadTexture(L"exp_progress", L"Texture//Battle//exp_progress.bmp");
	}
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

CPlayerBattleState_Bar::~CPlayerBattleState_Bar()
{
}

void CPlayerBattleState_Bar::SetPokemon(CPokemon* _Pokemon)
{  
	m_pPokemon = _Pokemon; 
	hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
	hpbar = hpbar2;
	expbar2 = (int)(((float)m_pPokemon->Getexp() / (float)m_pPokemon->Getexpmax()) * 64);
	expbar = expbar2;
}

void CPlayerBattleState_Bar::render(HDC _dc)
{
	if (!GetUse())
		return;
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
	TextOut(_dc, GetPos().x +70+ m_starani_y1, GetPos().y + 3, m_pPokemon->GetpName().c_str(), m_pPokemon->GetpName().size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);
	wstring Lv = std::to_wstring(m_pPokemon->GetLv());

	myFont = CreateFont(52, 15, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(0	, 0, 0));
	TextOut(_dc, GetPos().x+360+ m_starani_y1, GetPos().y+3, Lv.c_str(), Lv.size());

	wstring hp = std::to_wstring(m_pPokemon->GetmHP()) + L"/                " + std::to_wstring(m_pPokemon->Getm_maxhp());
	
	TextOut(_dc, GetPos().x + 200 + m_starani_y1, GetPos().y + 75, hp.c_str(), hp.size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);

	hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
	if (hpbar > 64)
		hpbar = 64;
	if (hpbar2 < hpbar)
	{
		hpbar--;
	}
	else if(hpbar2>hpbar)
	{
		hpbar++;
	}

	if (hpbar > 32)
	{
		for (int i = 0; i < hpbar; i++)
			BitBlt(_dc
				, (int)GetFinalPos().x + m_starani_y1 + 192 + (i * 3)
				, (int)GetFinalPos().y + 68
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
				, (int)GetFinalPos().x + m_starani_y1 + 192 + (i * 3)
				, (int)GetFinalPos().y + 68
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
				, (int)GetFinalPos().x + m_starani_y1 + 192 + (i * 3)
				, (int)GetFinalPos().y + 68
				, m_pProgressBar3->Width()
				, m_pProgressBar3->Height()
				, m_pProgressBar3->GetDC()
				, 0
				, 0, SRCCOPY);
	
	}
	expbar2 = (int)(((float)m_pPokemon->Getexp() / (float)m_pPokemon->Getexpmax()) * 64);
	if (expbar2 < expbar)
	{
		expbar= expbar2;
	}
	else if (expbar2 > expbar)
	{
		expbar++;
		if (expbar == 64)
			m_pPokemon->LvUp();
	}
	for (int i = 0; i < expbar; i++)
	{
		BitBlt(_dc
			, (int)GetFinalPos().x + m_starani_y1 + 128 + (i * 4)
			, (int)GetFinalPos().y + 132
			, m_pProgressBar_exp->Width()
			, m_pProgressBar_exp->Height()
			, m_pProgressBar_exp->GetDC()
			, 0
			, 0, SRCCOPY);
	}
		/*if (m_starani_y2 > 10 && m_starani_y1<=0 && a>0)
	{
		a--;
		m_starani_y2 = 0;
	}*/
}

void CPlayerBattleState_Bar::update()
{
	if (!GetUse())
		return;
	if (m_starani_y1 > 0)
	{
		m_starani_y1 -= fDT * 500;
		hpbar2 = (int)(((float)m_pPokemon->GetmHP() / (float)m_pPokemon->Getm_maxhp()) * 64);
		hpbar = hpbar2;
		expbar2 = (int)(((float)m_pPokemon->Getexp() / (float)m_pPokemon->Getexpmax()) * 64);
		expbar = expbar2;
	}

	//m_starani_y2 += fDT * 500;
}
