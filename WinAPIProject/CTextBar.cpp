#include "stdafx.h"
#include "CTextBar.h"


#include "CKeyMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"


#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#define m_starani1 1000

CTextBar::CTextBar():m_textn(0)
, m_startText(0)
, m_battleOn(false)
, m_Textend(false)
{
	SetObjtype(OBJ_TYPE::UI);
	SetUIType(UI_TYPE::TEXT);
}

CTextBar::~CTextBar()
{
}

void CTextBar::render(HDC _dc)
{
	if (!GetUse())
		return;

	if (m_Textend)
		return;
	if (nullptr == GetTexture())
		return;


	int iWidth = GetTexture()->Width();
	int iHeight = GetTexture()->Height();
	TransparentBlt(_dc
		, (int)GetFinalPos().x
		, (int)GetFinalPos().y
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));


	if (m_battleOn) {
		if (m_startText >= m_starani1)
		{

			HFONT myFont = CreateFont(75, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);
			SetTextColor(_dc, RGB(104, 88, 112));
			RECT rt = { 55,465,655,630 };
			DrawText(_dc, m_showtext.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
			rt = { 50,460,650,625 };
			SetTextColor(_dc, RGB(255, 255, 255));
			DrawText(_dc, m_showtext.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
			SelectObject(_dc, oldFont);
			DeleteObject(myFont);
		}
	}
	else
	{
		
			HFONT myFont = CreateFont(70, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);
			SetTextColor(_dc, RGB(208, 208, 208));
			RECT rt = { 55,465,915,620 };
			DrawText(_dc, m_showtext.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
			rt = { 50,460,910,615 };
			SetTextColor(_dc, RGB(96, 96, 96));
			DrawText(_dc, m_showtext.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
			SelectObject(_dc, oldFont);
			DeleteObject(myFont);
		
	}
}

void CTextBar::update()
{
	if (!GetUse() || m_Textend)
		return;
	if(m_startText < m_starani1)
		m_startText += fDT * 500.f;
	//일정 시간이 지난후 키눌렀을때 다음 텍스트로 넘어가게

	if (m_startText >= m_starani1)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{

			if (m_textn < m_text.size())
			{
				m_showtext.clear();
				for (; m_text[m_textn] != '\n'; m_textn++)
				{
					if ((size_t)m_textn >= m_text.size())
						break;
					m_showtext += m_text[m_textn];
				}
				m_textn++;
				CSound* pNewSound = CResMgr::GetInst()
					->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
				
			}
		}
		else if(m_textn == m_text.size())
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				if (m_battleOn == false)
				{
					m_Textend = true;
					SetUse(false);
				}
			}
		}

	}

	
}

void CTextBar::pushtext(const wstring& _text)
{
	//텍스트 추가
	 m_text += _text; 

	 if (m_showtext.size() == 0)
	 {
		 for (; m_text[m_textn] != '\n'; m_textn++)
		 {
			 m_showtext += m_text[m_textn];
		 }
		 m_textn++;

	 }
	 m_Textend = false;
}

void CTextBar::pushnexttext(const wstring& _text)
{
	//텍스트바 초기화 후 텍스트 추가
	m_showtext.clear();
	m_text += _text;
	
		for (; m_text[m_textn] != '\n'; m_textn++)
		{
			m_showtext += m_text[m_textn];
		}
	m_textn++;
	m_Textend = false;
}

bool CTextBar::Textend()
{
	return m_Textend;
}
