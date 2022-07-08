#include "stdafx.h"
#include "CPokemonSwap.h"
#include "CTexture.h"
#include "CPokemon.h"
#include "CResMgr.h"

#include "CSwapmain.h"
#include "CSwapserve.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "CBattleScene.h"
#include "CSceneMgr.h"
#include "CSwapChange.h"
#include "CStartmonterball.h"
#include "CTextBar.h"
#include "CPlayer.h"
#include "CTrainerBattle.h"

#include "CSound.h"

CPokemonSwap::CPokemonSwap():m_sBackGround(nullptr),
m_PokemonChange(nullptr),
m_focusnum(1),
m_focusnumpre(1),
m_pCancel(nullptr),
m_TextBarOn(false)
{
	SetObjtype(OBJ_TYPE::UI);
}

CPokemonSwap::~CPokemonSwap()
{
	/*if (m_PokemonChange != nullptr)
		delete m_PokemonChange;
	for (size_t i = 0; i < m_SwapMember.size(); i++)
	{
		if (m_SwapMember[i] != nullptr)
			delete m_SwapMember[i];
	}*/
}


void CPokemonSwap::init()
{
	m_sBackGround = CResMgr::GetInst()->FindTexture(L"Swapbackground");
	if (nullptr == m_sBackGround)
	{
		m_sBackGround = CResMgr::GetInst()->LoadTexture(L"Swapbackground", L"Texture//PokemonSwap//Swapbackground.bmp");
	}

	m_pCancel= CResMgr::GetInst()->FindTexture(L"Cancel");
	if (nullptr == m_pCancel)
	{
		m_pCancel = CResMgr::GetInst()->LoadTexture(L"Cancel", L"Texture//PokemonSwap//Cancel.bmp");
	}

	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"SwapStatemain");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"SwapStatemain", L"Texture//PokemonSwap//SwapStatemain.bmp");
	}
	CUI* pUI = new CSwapmain;
	CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(pUI);
	SwapMain->SetFocus(true);
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(8, 72));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);

	 m_pTex = CResMgr::GetInst()->FindTexture(L"SwapStateserve");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"SwapStateserve", L"Texture//PokemonSwap//SwapStateserve.bmp");
	}
	 pUI = new CSwapserve;
	 CSwapserve* SwapServe= dynamic_cast<CSwapserve*>(pUI);
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(352,36));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);

	
	pUI = new CSwapserve;
	SwapServe = dynamic_cast<CSwapserve*>(pUI);

	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(352, 132));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);
	
	pUI = new CSwapserve;
	SwapServe = dynamic_cast<CSwapserve*>(pUI);
	
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(352, 228));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);
	pUI = new CSwapserve;
	SwapServe = dynamic_cast<CSwapserve*>(pUI);

	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(352, 324));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);

	pUI = new CSwapserve;
	SwapServe = dynamic_cast<CSwapserve*>(pUI);

	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(352, 420));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	m_SwapMember.push_back(pUI);
	AddChildUI(pUI);
	pUI = new CSwapChange();
	m_PokemonChange= dynamic_cast<CSwapChange*>(pUI);
	pUI->SetUse(false);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	AddChildUI(pUI);
}

void CPokemonSwap::update()
{
	if (!GetUse())
		return;
	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->update();
	}
	if (!m_PokemonChange->GetUse()) {
		if (KEY_TAP(KEY_TYPE::KEY_UP))
		{
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(80.f);
			pNewSound->Play(false);
			if (m_focusnum == 0)
			{
				m_focusnum = m_PokemonMember.size();
				m_focusnumpre = m_PokemonMember.size();
				if (m_focusnum == 1)
				{
					CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
					SwapMain->SetFocus(true);

				}
				else {
					CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
					Swapserve->SetFocus(true);
				}
			}
			else if (m_focusnum == 1)
			{
				CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				SwapMain->SetFocus(false);
				m_focusnum = 0;
				m_focusnumpre = 0;
			}
			else {
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapserve->SetFocus(false);
				m_focusnum--;
				m_focusnumpre--;
				if (m_focusnum == 1)
				{
					CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
					SwapMain->SetFocus(true);
				}
				else {
					CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
					Swapserve->SetFocus(true);
				}
			}
		}
		if (KEY_TAP(KEY_TYPE::KEY_DOWN))
		{
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(80.f);
			pNewSound->Play(false);
			if (m_focusnum == 0)
			{
				m_focusnum = 1;
				m_focusnumpre = 1;
				CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				SwapMain->SetFocus(true);

			}
			else if (m_focusnum == 1)
			{
				CSwapmain* SwapMain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				SwapMain->SetFocus(false);
				if (m_PokemonMember.size() < 2)
				{

					m_focusnum = 0;
					m_focusnumpre = 0;
				}
				else {

					m_focusnum++;
					m_focusnumpre++;
					CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
					Swapserve->SetFocus(true);
				}
			}
			else {
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapserve->SetFocus(false);
				m_focusnum++;
				m_focusnumpre++;
				if (m_focusnum > m_PokemonMember.size())
				{
					m_focusnum = 0;
					m_focusnumpre = 0;

				}
				else {
					CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
					Swapserve->SetFocus(true);
				}
			}

		}
		if (KEY_TAP(KEY_TYPE::KEY_LEFT))
		{

			if (m_focusnum != 1 && m_focusnum != 0)
			{
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapserve->SetFocus(false);
				m_focusnum = 1;
				CSwapmain* Swapmain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapmain->SetFocus(true);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
			}
		}
		if (KEY_TAP(KEY_TYPE::KEY_RIGHT))
		{
			if (m_focusnum == 1)
			{
				CSwapmain* Swapmain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapmain->SetFocus(false);
				if (m_focusnumpre == 1)
					m_focusnumpre = 2;
				m_focusnum = m_focusnumpre;
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapserve->SetFocus(true);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
			}
		}
		if (KEY_TAP(KEY_TYPE::KEY_X))
		{
			if (m_focusnum == 1 || m_focusnum == 0)
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
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
				SetUse(false);

			}
			else
			{
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapserve->SetFocus(false);
				m_focusnum = 1;
				m_focusnumpre = 1;
				CSwapmain* Swapmain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
				Swapmain->SetFocus(true);
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
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
				SetUse(false);

			}
		}
	}
	if (m_PokemonChange->GetUse())
	{

		if (m_PokemonChange->GetArrowPos() == 1)
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				if (m_TextBarOn)
				{
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();

					if (nullptr != dynamic_cast<CBattleScene*>(scene))
					{
						CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						battlescene->GetTextBar()->SetUse(false);
					}
					else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
					{
						CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
						trainerscene->GetTextBar()->SetUse(false);
					}
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(80.f);
					pNewSound->Play(false);
					m_PokemonChange->SetUse(false);
					m_TextBarOn = false;
				}
				else if (m_focusnum != 0 && m_focusnum != 1)
				{
					if(m_PokemonMember[m_focusnum - 1]->GetmHP()<=0)
					{ 
						CScene* scene = CSceneMgr::GetInst()->GetCurScene();

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[m_focusnum - 1]->GetpName() + L"는(은) 싸울 기력이 없다!\n";
							battlescene->GetTextBar()->pushnexttext(s);

						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[m_focusnum - 1]->GetpName() + L"는(은) 싸울 기력이 없다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
						pNewSound->SetVolume(80.f);
						pNewSound->Play(false);
						m_TextBarOn = true;
						return;
					}
					else {

						CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[(size_t)m_focusnum - 1]);
						Swapserve->SetFocus(false);



						CPokemon* swap = m_PokemonMember[0];
						m_PokemonMember[0] = m_PokemonMember[m_focusnum - 1];
						m_PokemonMember[m_focusnum - 1] = swap;

						m_focusnum = 1;
						m_focusnumpre = 1;

						CSwapmain* Swapmain = dynamic_cast<CSwapmain*>(m_SwapMember[(size_t)m_focusnum - 1]);
						Swapmain->SetFocus(true);
						Enter();
						m_PokemonChange->SetUse(false);
						CScene* scene = CSceneMgr::GetInst()->GetCurScene();

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->SetPokemonMember(m_PokemonMember);
							battlescene->GetPlayer()->SetPokemonMember(m_PokemonMember);

							battlescene->PokemonChange();
						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->SetPokemonMember(m_PokemonMember);
							trainerscene->GetPlayer()->SetPokemonMember(m_PokemonMember);

							trainerscene->PokemonChange();
						}
					}
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(80.f);
					pNewSound->Play(false);
				
					SetUse(false);

					return;
				}
				else if (m_focusnum == 1)
				{
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();

					if (m_PokemonMember[0]->GetmHP() <= 0)
					{
						CScene* scene = CSceneMgr::GetInst()->GetCurScene();

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[0]->GetpName() + L"는(은) 싸울 기력이 없다!\n";
							battlescene->GetTextBar()->pushnexttext(s);

						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[0]->GetpName() + L"는(은) 싸울 기력이 없다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
						pNewSound->SetVolume(80.f);
						pNewSound->Play(false);
						m_TextBarOn = true;
						return;
					}
					else {

						if (nullptr != dynamic_cast<CBattleScene*>(scene))
						{
							CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
							battlescene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[0]->GetpName() + L"는(은) 이미 나가 있습니다!\n";
							battlescene->GetTextBar()->pushnexttext(s);

						}
						else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
						{
							CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
							trainerscene->GetTextBar()->SetUse(true);
							wstring s = m_PokemonMember[0]->GetpName() + L"는(은) 이미 나가 있습니다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
						pNewSound->SetVolume(80.f);
						pNewSound->Play(false);
						m_TextBarOn = true;
						return;
					}
				}
			}
		}
		else if (m_PokemonChange->GetArrowPos() == 2)
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				m_PokemonChange->SetUse(false);
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(80.f);
				pNewSound->Play(false);
				return;
			}
		}
			

		if (KEY_TAP(KEY_TYPE::KEY_X))
		{
			m_PokemonChange->SetUse(false);
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(80.f);
			pNewSound->Play(false);

		}
	}
	if(KEY_TAP(KEY_TYPE::KEY_Z))
	{
		m_PokemonChange->SetUse(true);
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
		pNewSound->SetVolume(80.f);
		pNewSound->Play(false);
	}

	
}

void CPokemonSwap::Enter()
{
	SetUse(true);
	for (size_t i = 0; i < m_PokemonMember.size(); i++) {
		if (m_PokemonMember[i] != nullptr)
		{
			if (i == 0)
			{
				CSwapmain* Swapmain = dynamic_cast<CSwapmain*>(m_SwapMember[i]);
				Swapmain->SetPokemon(m_PokemonMember[i]);
			}
			else
			{
				CSwapserve* Swapserve = dynamic_cast<CSwapserve*>(m_SwapMember[i]);
				Swapserve->SetPokemon(m_PokemonMember[i]);
				Swapserve->SetPokemonAnimPos(Vec2(380.f, 40.f + 96*(i-1)));
			}
		}
	}
	CCamera::GetInst()->Setcamera(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f));


}



void CPokemonSwap::render(HDC _dc)
{
	if (!GetUse())
		return;
	BitBlt(_dc
		, 0
		, 0
		, m_sBackGround->Width()
		, m_sBackGround->Height()
		, m_sBackGround->GetDC()
		, 0
		, 0, SRCCOPY);  //기본 백그라운드
	

	if (m_focusnum == 0) {
		TransparentBlt(_dc
			, 736
			, 528
			, m_pCancel->Width(), 96
			, m_pCancel->GetDC()
			, 0, 80
			, m_pCancel->Width(),96
			, RGB(255, 0, 255));
	}
	else {
		TransparentBlt(_dc
			, 736
			, 536
			, m_pCancel->Width(), 80
			, m_pCancel->GetDC()
			, 0, 0
			, m_pCancel->Width(), 80
			, RGB(255, 0, 255));
	}
	const vector<CUI*>& vecChild = GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		if (vecChild[i]->GetUse())
			vecChild[i]->render(_dc);
	}

}


