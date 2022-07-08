#include "stdafx.h"
#include "CSwapmain.h"
#include "CTexture.h"
#include "CObjectMgr.h"
#include "CPokemon.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPokemonanim.h"

#include "CResMgr.h"
CSwapmain::CSwapmain():m_focuson(false),
m_PokemonAnim(nullptr),
m_Pokemon(nullptr)
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

CSwapmain::~CSwapmain()
{
	if(m_PokemonAnim !=nullptr)
	delete m_PokemonAnim;
	
}

void CSwapmain::update()
{
	if (m_Pokemon == nullptr)
		return;
	m_PokemonAnim->update();
}

void CSwapmain::SetPokemon(CPokemon* _Pokemon)
{
	if (m_PokemonAnim != nullptr)
		delete m_PokemonAnim;
	 m_Pokemon = _Pokemon; 
	 m_PokemonAnim = new CPokemonanim();
	 m_PokemonAnim->SetName(m_Pokemon->GetpName());
	 m_PokemonAnim->SetPos(Vec2(46.f, 116.f));
	 m_PokemonAnim->init();
}


void CSwapmain::render(HDC _dc)
{

	if (nullptr == GetTexture())
		return;
	if (m_Pokemon == nullptr)
		return;
	int iWidth = GetTexture()->Width();
	int iHeight = GetTexture()->Height();
	
	if (m_focuson)
	{
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y
			, iWidth, 228
			, GetTexture()->GetDC()
			, 0, 220
			, iWidth, 228
			, RGB(255, 0, 255));
	}
	else {
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y+8
			, iWidth, 220
			, GetTexture()->GetDC()
			, 0, 0
			, iWidth, 220
			, RGB(255, 0, 255));

	}
	m_PokemonAnim->render(_dc);

	HFONT myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(104, 88, 112));
	RECT rt = { 55,465,655,630 };
	TextOut(_dc, GetPos().x + 152, GetPos().y + 62, m_Pokemon->GetpName().c_str(), m_Pokemon->GetpName().size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);
	 myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	 oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, GetPos().x+150, GetPos().y+60 , m_Pokemon->GetpName().c_str(), m_Pokemon->GetpName().size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);
	
	
	 myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	 oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(104, 88, 112));
	 rt = { 55,465,655,630 };
	TextOut(_dc, GetPos().x + 193, GetPos().y + 108, std::to_wstring(m_Pokemon->GetLv()).c_str(), std::to_wstring(m_Pokemon->GetLv()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);



	myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, GetPos().x + 190, GetPos().y +105, std::to_wstring(m_Pokemon->GetLv()).c_str(), std::to_wstring(m_Pokemon->GetLv()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);



	myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(104, 88, 112));
	rt = { 55,465,655,630 };
	TextOut(_dc, GetPos().x + 83, GetPos().y + 173, std::to_wstring(m_Pokemon->GetmHP()).c_str(), std::to_wstring(m_Pokemon->GetmHP()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);



	myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, GetPos().x + 80, GetPos().y + 170, std::to_wstring(m_Pokemon->GetmHP()).c_str(), std::to_wstring(m_Pokemon->GetmHP()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(104, 88, 112));
	rt = { 55,465,655,630 };
	TextOut(_dc, GetPos().x + 203, GetPos().y + 173, std::to_wstring(m_Pokemon->Getm_maxhp()).c_str(), std::to_wstring(m_Pokemon->Getm_maxhp()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);



	myFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, GetPos().x + 200, GetPos().y + 170, std::to_wstring(m_Pokemon->Getm_maxhp()).c_str(), std::to_wstring(m_Pokemon->Getm_maxhp()).size());
	SelectObject(_dc, oldFont);
	DeleteObject(myFont);

	int hpbar = (int)(((float)m_Pokemon->GetmHP() / (float)m_Pokemon->Getm_maxhp()) * 64);

	if (hpbar > 32)
	{
		for (int i = 0; i < hpbar; i++)
			
			BitBlt(_dc
				, (int)GetFinalPos().x+  120 + (i * 3)
				, (int)GetFinalPos().y + 164
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
				, (int)GetFinalPos().x  + 120 + (i * 3)
				, (int)GetFinalPos().y + 164
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
				, (int)GetFinalPos().x + 120 + (i * 3)
				, (int)GetFinalPos().y + 164
				, m_pProgressBar3->Width()
				, m_pProgressBar3->Height()
				, m_pProgressBar3->GetDC()
				, 0
				, 0, SRCCOPY);

	}

}

