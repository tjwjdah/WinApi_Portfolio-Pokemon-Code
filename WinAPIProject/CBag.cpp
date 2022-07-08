#include "stdafx.h"
#include "CBag.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CItem.h"

#include "CBagSelect.h"
#include "CBattleScene.h"
#include "CSceneMgr.h"
#include "CTrainerBattle.h"

#include "CSound.h"
CBag::CBag() :m_pTex(nullptr), m_SetItemNum(0),
m_pSelect(nullptr),
m_pTexPre(nullptr),
m_bagarrow(nullptr),
m_on(false)
{
	SetObjtype(OBJ_TYPE::UI);
}

CBag::~CBag()
{
	for (size_t i = 0; i < m_itemlist.size(); i++)
	{
		delete m_itemlist[i];
	}
}

void CBag::update()
{
	if (!GetUse())
		return;

	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->update();
	}

	vector<CItem*>::iterator iter = m_itemlist.begin();

	for (; iter != m_itemlist.end(); )
	{
		if ((*iter)->Getamount()<=0)
		{
			delete* iter;
			iter = m_itemlist.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	if (m_on == false)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			m_on = true;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(100.f);
			pNewSound->Play(false);
			return;
		}
	}
	if (!m_pSelect->GetUse())
	{
		if (KEY_TAP(KEY_TYPE::KEY_UP))
		{
			if (m_SetItemNum > 0)
			{
				m_SetItemNum--;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		if (KEY_TAP(KEY_TYPE::KEY_DOWN))
		{
			if (m_SetItemNum < m_itemlist.size())
			{
				m_SetItemNum++;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		if (m_SetItemNum < m_itemlist.size())
		{
		
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
					m_pSelect->SetUse(true);
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(100.f);
					pNewSound->Play(false);
					return;

			}
			
		}
		else if (m_SetItemNum == m_itemlist.size())
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				CScene* scene = CSceneMgr::GetInst()->GetCurScene();

				if (nullptr != dynamic_cast<CBattleScene*>(scene))
				{
					CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
					battlescene->UIOnOff(true);
				}
				else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
				{
					CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
					trainerscene->UIOnOff(true);
				}
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
				SetUse(false);
				m_pSelect->SetUse(false);
			}
		}

		if (KEY_TAP(KEY_TYPE::KEY_X))
		{
			CScene* scene = CSceneMgr::GetInst()->GetCurScene();

			if (nullptr != dynamic_cast<CBattleScene*>(scene))
			{
				CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
				battlescene->UIOnOff(true);
			}
			else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
			{
				CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
				trainerscene->UIOnOff(true);
			}
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(100.f);
			pNewSound->Play(false);
			SetUse(false);
			m_pSelect->SetUse(false);
		}
	}
	else
	{
		if (m_pSelect->GetArrowPos() == 1)
		{
				if (KEY_TAP(KEY_TYPE::KEY_Z))
				{
					if (m_SetItemNum < m_itemlist.size())
					{

						CScene* scene = CSceneMgr::GetInst()->GetCurScene();

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->UIOnOff(true);
						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->UIOnOff(true);
						}

					
						SetUse(false);
						m_pSelect->SetUse(false);
						m_itemlist[m_SetItemNum]->run();

					}
					else if(m_SetItemNum == m_itemlist.size())
					{
						CScene* scene = CSceneMgr::GetInst()->GetCurScene();

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->UIOnOff(true);
						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->UIOnOff(true);
						}
						
						SetUse(false);
						m_pSelect->SetUse(false);
					}
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(100.f);
					pNewSound->Play(false);
				}
		}
		else if (m_pSelect->GetArrowPos() == 2)
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				m_pSelect->SetUse(false);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		if (KEY_TAP(KEY_TYPE::KEY_X))
		{

			m_pSelect->SetUse(false);
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(100.f);
			pNewSound->Play(false);
		}
	}
}

void CBag::render(HDC _dc)
{
	if (!GetUse())
		return;

	BitBlt(_dc
		, 0
		, 0
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0, SRCCOPY);  //기본 백그라운드



	for (size_t i = 0; i <= m_itemlist.size(); i++)
	{
		if (i < m_itemlist.size())
		{
			HFONT myFont = CreateFont(64, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);
			SetTextColor(_dc, RGB(208, 208, 200));
			RECT rt = { 389 ,32 + (64 * (LONG)i), 932 , 97 + (64 * (LONG)i) };
			wstring s = m_itemlist[i]->GetName() +L"x "+ std::to_wstring(m_itemlist[i]->Getamount()) +L"\n";
			DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
			rt = { 389 ,28 + (64 * (LONG)i), 932 , 92 + (64 * (LONG)i) };
			SetTextColor(_dc, RGB(96, 96, 96));
			DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
			SelectObject(_dc, oldFont);
			DeleteObject(myFont);
			

		}
		else if (i == m_itemlist.size())
		{
			HFONT myFont = CreateFont(64, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);
			SetTextColor(_dc, RGB(208, 208, 200));
			RECT rt = { 389 ,32 + (64 * (LONG)i), 932 , 97 + (64 * (LONG)i) };
			wstring s = L"닫기";
			DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
			rt = { 389 ,28 + (64 * (LONG)i), 932 , 92 + (64 * (LONG)i) };
			SetTextColor(_dc, RGB(96, 96, 96));
			DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
			//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
			SelectObject(_dc, oldFont);
			DeleteObject(myFont);

		
		}
	}


	TransparentBlt(_dc
		, 352
		, 32 + (m_SetItemNum * 64)
		, m_bagarrow->Width(), m_bagarrow->Height()
		, m_bagarrow->GetDC()
		, 0, 0
		, m_bagarrow->Width(), m_bagarrow->Height()
		, RGB(255, 0, 255));

	if (m_SetItemNum <m_itemlist.size() )
	{
		CTexture* itemTex = m_itemlist[m_SetItemNum]->GetTex();
		TransparentBlt(_dc
			, 48	
			, 512
			, itemTex->Width(), itemTex->Height()
			, itemTex->GetDC()
			, 0, 0
			, itemTex->Width(), itemTex->Height()
			, RGB(255, 0, 255));

		
		HFONT myFont = CreateFont(75, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
		HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
		SetBkMode(_dc, TRANSPARENT);
		SetTextColor(_dc, RGB(104, 88, 112));
		RECT rt = { 261,465,949,630 };
		DrawText(_dc, m_itemlist[m_SetItemNum]->GetExp().c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
		//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
		rt = { 256,460,944,625 };
		SetTextColor(_dc, RGB(255, 255, 255));
		DrawText(_dc, m_itemlist[m_SetItemNum]->GetExp().c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
		//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
		SelectObject(_dc, oldFont);
		DeleteObject(myFont);

	}
	if (m_SetItemNum == m_itemlist.size())
	{
		TransparentBlt(_dc
			, 24
			, 488
			, m_pTexPre->Width(), m_pTexPre->Height()
			, m_pTexPre->GetDC()
			, 0, 0
			, m_pTexPre->Width(), m_pTexPre->Height()
			, RGB(255, 0, 255));


		HFONT myFont = CreateFont(75, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
		HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
		SetBkMode(_dc, TRANSPARENT);
		SetTextColor(_dc, RGB(104, 88, 112));
		RECT rt = { 261,465,949,630 };
		wstring s = L"가방을 닫습니다\n";
		DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
		//TextOut(_dc, GetPos().x+69, GetPos().y+5, m_showtext.c_str(), m_showtext.size());
		rt = { 256,460,944,625 };
		SetTextColor(_dc, RGB(255, 255, 255));
		DrawText(_dc, s.c_str(), -1, &rt, DT_LEFT | DT_WORDBREAK);
		//TextOut(_dc, GetPos().x+64, GetPos().y, m_showtext.c_str(), m_showtext.size());
		SelectObject(_dc, oldFont);
		DeleteObject(myFont);
	}
	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->render(_dc);
	}
}

void CBag::init()
{

		
	m_pTex= CResMgr::GetInst()->FindTexture(L"bag");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"bag", L"Texture//Bag//bag.bmp");
	}
	m_pTexPre = CResMgr::GetInst()->FindTexture(L"Previous");
	if (nullptr == m_pTexPre)
	{
		m_pTexPre = CResMgr::GetInst()->LoadTexture(L"Previous", L"Texture//Bag//Previous.bmp");
	}
	m_bagarrow = CResMgr::GetInst()->FindTexture(L"bagarrow");
	if (nullptr == m_bagarrow)
	{
		m_bagarrow = CResMgr::GetInst()->LoadTexture(L"bagarrow", L"Texture//Bag//bagarrow.bmp");
	}
	for (size_t i = 0; i < m_itemlist.size(); i++)
	{
		m_itemlist[i]->init();
	}
	CUI* pUI = new CBagSelect();
	m_pSelect = dynamic_cast<CBagSelect*>(pUI);
	pUI->SetUse(false);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	AddChildUI(pUI);
}

void CBag::Enter()
{
	for (size_t i = 0; i < m_itemlist.size(); i++)
	{
		m_itemlist[i]->init();
	}
	m_on = false;
}
