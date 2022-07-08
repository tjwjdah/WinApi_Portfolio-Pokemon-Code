#include "stdafx.h"
#include "CBattleChoice.h"


#include "CTimeMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CKeyMgr.h"

#include "CPokemon.h"
#include "CSkill.h"
#include "CTextBar.h"
#include "CThrowPokeball.h"

#include "CBattleScene.h"
#include "CSceneMgr.h"
#include "CPokemonSwap.h"
#include "CBag.h"
#include "CPlayer.h"
#include "CTrainerBattle.h"

#include "CSound.h"
#include "CSoundMgr.h"
CBattleChoice::CBattleChoice() :m_select(1), m_select2(1),
m_pPokemon(nullptr)
, m_oPokemon(nullptr)
, m_skillselecton(false)
, m_showon(true)
, m_showon2(true)
{
	
	m_Arrow = CResMgr::GetInst()->FindTexture(L"BatteArrow");
	if (nullptr == m_Arrow)
	{
		m_Arrow = CResMgr::GetInst()->LoadTexture(L"BatteArrow", L"Texture//Battle//BatteArrow.bmp");
	}
	m_skillselect = CResMgr::GetInst()->FindTexture(L"SkillChoice");
	if (nullptr == m_skillselect)
	{
		m_skillselect = CResMgr::GetInst()->LoadTexture(L"SkillChoice", L"Texture//Battle//SkillChoice.bmp");
	}
	SetObjtype(OBJ_TYPE::UI);
}

CBattleChoice::~CBattleChoice()
{
}

void CBattleChoice::render(HDC _dc)
{
	if (!GetUse())
		return;
	if (!m_showon)
		return;
	if (!m_showon2)
		return;
	if (nullptr == GetTexture())
		return;
	if (!m_skillselecton)
	{
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

		int iWidth2 = 0;
		int iHeight2 = 0;
		switch (m_select)
		{
		case 1:
			iWidth2 = 516;
			iHeight2 = 496;
			break;
		case 2:
			iWidth2 = 712;
			iHeight2 = 496;
			break;
		case 3:
			iWidth2 = 516;
			iHeight2 = 560;
			break;
		case 4:
			iWidth2 = 712;
			iHeight2 = 560;
			break;
		}
		TransparentBlt(_dc
			, iWidth2
			, iHeight2
			, m_Arrow->Width(), m_Arrow->Height()
			, m_Arrow->GetDC()
			, 0, 0
			, m_Arrow->Width(), m_Arrow->Height()
			, RGB(255, 0, 255));
	}
	else
	{
		int iWidth = m_skillselect->Width();
		int iHeight = m_skillselect->Height();
		TransparentBlt(_dc
			, 0
			, 448
			, iWidth, iHeight
			, m_skillselect->GetDC()
			, 0, 0
			, iWidth, iHeight
			, RGB(255, 0, 255));



		int iWidth2 = 0;
		int iHeight2 = 0;
		HFONT myFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
		HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
		SetBkMode(_dc, TRANSPARENT);
		switch (m_select2)
		{
		case 1:
			iWidth2 = 36;
			iHeight2 = 496;
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc,793, 485 + 3, std::to_wstring(m_pPokemon->GetSkill1()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill1()->GetSkillpp()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 790, 485, std::to_wstring(m_pPokemon->GetSkill1()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill1()->GetSkillpp()).size());
		


			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 878, 485 + 3, std::to_wstring(m_pPokemon->GetSkill1()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill1()->GetSkillppMax()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 875, 485, std::to_wstring(m_pPokemon->GetSkill1()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill1()->GetSkillppMax()).size());

			SelectObject(_dc, oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 808, 545 + 3, m_pPokemon->GetSkill1()->GetSkillType_ToString().c_str(),(int) m_pPokemon->GetSkill1()->GetSkillType_ToString().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 805, 545, m_pPokemon->GetSkill1()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill1()->GetSkillType_ToString().size());

			break;
		case 2:
			iWidth2 = 322;
			iHeight2 = 496;
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 793, 485 + 3, std::to_wstring(m_pPokemon->GetSkill2()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill2()->GetSkillpp()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 790, 485, std::to_wstring(m_pPokemon->GetSkill2()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill2()->GetSkillpp()).size());

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 878, 485 + 3, std::to_wstring(m_pPokemon->GetSkill2()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill2()->GetSkillppMax()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 875, 485, std::to_wstring(m_pPokemon->GetSkill2()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill2()->GetSkillppMax()).size());

			SelectObject(_dc, oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 808, 545 + 3, m_pPokemon->GetSkill2()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill2()->GetSkillType_ToString().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 805, 545, m_pPokemon->GetSkill2()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill2()->GetSkillType_ToString().size());
		
			break;
		case 3:
			iWidth2 = 36;
			iHeight2 = 560;
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 793, 485 + 3, std::to_wstring(m_pPokemon->GetSkill3()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill3()->GetSkillpp()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 790, 485, std::to_wstring(m_pPokemon->GetSkill3()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill3()->GetSkillpp()).size());

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 878, 485 + 3, std::to_wstring(m_pPokemon->GetSkill3()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill3()->GetSkillppMax()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 875, 485, std::to_wstring(m_pPokemon->GetSkill3()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill3()->GetSkillppMax()).size());
			
			SelectObject(_dc, oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 808, 545 + 3, m_pPokemon->GetSkill3()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill3()->GetSkillType_ToString().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 805, 545, m_pPokemon->GetSkill3()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill3()->GetSkillType_ToString().size());
			
			break;
		case 4:
			iWidth2 = 322;
			iHeight2 = 560;
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 793, 485 + 3, std::to_wstring(m_pPokemon->GetSkill4()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill4()->GetSkillpp()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 790, 485, std::to_wstring(m_pPokemon->GetSkill4()->GetSkillpp()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill4()->GetSkillpp()).size());

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 878, 485 + 3, std::to_wstring(m_pPokemon->GetSkill4()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill4()->GetSkillppMax()).size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 875, 485, std::to_wstring(m_pPokemon->GetSkill4()->GetSkillppMax()).c_str(), (int)std::to_wstring(m_pPokemon->GetSkill4()->GetSkillppMax()).size());

			SelectObject(_dc, oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(55, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
			oldFont = (HFONT)SelectObject(_dc, myFont);
			SetBkMode(_dc, TRANSPARENT);

			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 808, 545 + 3, m_pPokemon->GetSkill4()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill4()->GetSkillType_ToString().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 805, 545, m_pPokemon->GetSkill4()->GetSkillType_ToString().c_str(), (int)m_pPokemon->GetSkill4()->GetSkillType_ToString().size());
			break;
		}

		TransparentBlt(_dc
			, iWidth2
			, iHeight2
			, m_Arrow->Width(), m_Arrow->Height()
			, m_Arrow->GetDC()
			, 0, 0
			, m_Arrow->Width(), m_Arrow->Height()
			, RGB(255, 0, 255));



	
		
		SetTextColor(_dc, RGB(104, 88, 112));
		TextOut(_dc,63, 480 +3, m_pPokemon->GetSkill1()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill1()->GetSkillname().size());
		SetTextColor(_dc, RGB(32, 32, 32));
		TextOut(_dc, 60, 480,m_pPokemon->GetSkill1()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill1()->GetSkillname().size());
		
		if (m_pPokemon->GetSkill2() != nullptr)
		{
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 353, 480 + 3, m_pPokemon->GetSkill2()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill2()->GetSkillname().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 350, 480, m_pPokemon->GetSkill2()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill2()->GetSkillname().size());
		}
		if (m_pPokemon->GetSkill3() != nullptr)
		{
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 63, 545 + 3, m_pPokemon->GetSkill3()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill3()->GetSkillname().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 60, 545, m_pPokemon->GetSkill3()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill3()->GetSkillname().size());
		}
		if (m_pPokemon->GetSkill4() != nullptr)
		{
			SetTextColor(_dc, RGB(104, 88, 112));
			TextOut(_dc, 353, 545 + 3, m_pPokemon->GetSkill4()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill4()->GetSkillname().size());
			SetTextColor(_dc, RGB(32, 32, 32));
			TextOut(_dc, 350, 545, m_pPokemon->GetSkill4()->GetSkillname().c_str(), (int)m_pPokemon->GetSkill4()->GetSkillname().size());
		}

		SelectObject(_dc, oldFont);
		DeleteObject(myFont);



	}
}

void CBattleChoice::update()
{
	if (!GetUse())
		return;
	if (!m_showon)
		return;
	if (!m_showon2)
		return;
	if (!m_skillselecton)
	{
		switch (m_select)
		{
		case 1:
		{
			if (KEY_TAP(KEY_TYPE::KEY_DOWN))
			{
				m_select = 3;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);

			}
			if (KEY_TAP(KEY_TYPE::KEY_RIGHT))

			{
				m_select = 2;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 2:
		{
			if (KEY_TAP(KEY_TYPE::KEY_DOWN))
			{
				m_select = 4;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
			if (KEY_TAP(KEY_TYPE::KEY_LEFT))
			{
				m_select = 1;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 3:
		{
			if (KEY_TAP(KEY_TYPE::KEY_UP))
			{
				m_select = 1;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
			if (KEY_TAP(KEY_TYPE::KEY_RIGHT))
			{
				m_select = 4;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 4:
		{
			if (KEY_TAP(KEY_TYPE::KEY_UP))
			{
				m_select = 2;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
			if (KEY_TAP(KEY_TYPE::KEY_LEFT))
			{
				m_select = 3;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		}
	}
	
	if (m_skillselecton)
	{
		switch (m_select2)
		{
		case 1:
		{
			if (KEY_TAP(KEY_TYPE::KEY_DOWN))
			{	
				if (m_pPokemon->GetSkill3() != nullptr)
				{
					m_select2 = 3;
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(100.f);
					pNewSound->Play(false);
				}
			}
			if (KEY_TAP(KEY_TYPE::KEY_RIGHT))
				if (m_pPokemon->GetSkill2() != nullptr) {
					m_select2 = 2;
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(100.f);
					pNewSound->Play(false);
				}
			if (KEY_TAP(KEY_TYPE::KEY_Z)) {
				CScene* scene = CSceneMgr::GetInst()->GetCurScene();
				if (nullptr != dynamic_cast<CBattleScene*>(scene))
				{
					CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						m_pPokemon->GetSkill1()->Settarget(m_pPokemon, m_oPokemon);
						battlescene->timeskillpush(m_pPokemon->GetSkill1());
				}
				else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
				{
					CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
					m_pPokemon->GetSkill1()->Settarget(m_pPokemon, m_oPokemon);
					trainerscene->timeskillpush(m_pPokemon->GetSkill1());
				}
				m_showon = false;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 2:
		{
			if (KEY_TAP(KEY_TYPE::KEY_DOWN))
				if (m_pPokemon->GetSkill4() != nullptr) {
					m_select2 = 4;
					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
					pNewSound->SetVolume(100.f);
					pNewSound->Play(false);
				}
			if (KEY_TAP(KEY_TYPE::KEY_LEFT))
			{
				m_select2 = 1;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);

			}
			if (KEY_TAP(KEY_TYPE::KEY_Z)) {
				CScene* scene = CSceneMgr::GetInst()->GetCurScene();
				if (nullptr != dynamic_cast<CBattleScene*>(scene))
				{
					CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
					m_pPokemon->GetSkill2()->Settarget(m_pPokemon, m_oPokemon);
					battlescene->timeskillpush(m_pPokemon->GetSkill2());
				}
				else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
				{
					CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
					m_pPokemon->GetSkill2()->Settarget(m_pPokemon, m_oPokemon);
					trainerscene->timeskillpush(m_pPokemon->GetSkill2());
				}
				m_showon = false;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 3:
		{
			if (KEY_TAP(KEY_TYPE::KEY_UP))
			{
				m_select2 = 1;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);

			}
			if (KEY_TAP(KEY_TYPE::KEY_RIGHT))
			{
				m_select2 = 4;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
			if (KEY_TAP(KEY_TYPE::KEY_Z)) {
				CScene* scene = CSceneMgr::GetInst()->GetCurScene();
				if (nullptr != dynamic_cast<CBattleScene*>(scene))
				{
					CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
					m_pPokemon->GetSkill3()->Settarget(m_pPokemon, m_oPokemon);
					battlescene->timeskillpush(m_pPokemon->GetSkill3());
				}
				else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
				{
					CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
					m_pPokemon->GetSkill3()->Settarget(m_pPokemon, m_oPokemon);
					trainerscene->timeskillpush(m_pPokemon->GetSkill3());
				}
				m_showon = false;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		case 4:
		{
			if (KEY_TAP(KEY_TYPE::KEY_UP))
			{
				m_select2 = 2;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);

			}
			if (KEY_TAP(KEY_TYPE::KEY_LEFT))
			{
				m_select2 = 3;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				CScene* scene = CSceneMgr::GetInst()->GetCurScene();
				if (nullptr != dynamic_cast<CBattleScene*>(scene))
				{
					CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
					m_pPokemon->GetSkill4()->Settarget(m_pPokemon, m_oPokemon);
					battlescene->timeskillpush(m_pPokemon->GetSkill4());
				}
				else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
				{
					CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
					m_pPokemon->GetSkill4()->Settarget(m_pPokemon, m_oPokemon);
					trainerscene->timeskillpush(m_pPokemon->GetSkill4());
				}
				m_showon = false;
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
				pNewSound->SetVolume(100.f);
				pNewSound->Play(false);
			}
		}
		break;
		}
		if (KEY_TAP(KEY_TYPE::KEY_X))
		{
			m_skillselecton = false;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
			pNewSound->SetVolume(100.f);
			pNewSound->Play(false);
		}
	}
	if (!m_skillselecton && m_select == 1)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			Fight();
		}
	}
	if (!m_skillselecton && m_select == 2)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z)) {
			Bag();
		}
	}
	if (!m_skillselecton && m_select == 3)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z)) {
			PokemonChange();
		}
	}
	if (!m_skillselecton && m_select == 4)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z)) {
			Run();
		}
	}
}

void CBattleChoice::Fight()
{
	m_skillselecton = true;
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
	pNewSound->SetVolume(100.f);
	pNewSound->Play(false);
}

void CBattleChoice::Bag()
{
	CScene* scene = CSceneMgr::GetInst()->GetCurScene();

	if (nullptr != dynamic_cast<CBattleScene*>(scene))
	{
		CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
		CUI* CUI = battlescene->GetPlayer()->GetBag();
		CBag* bag = dynamic_cast<CBag*>(CUI);
		bag->Enter();
		bag->SetUse(true);
		battlescene->Getbattlechoice()->SetUse(false);
		battlescene->UIOnOff(false);
	}
	else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
	{
		CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
		CUI* CUI = trainerscene->GetPlayer()->GetBag();
		CBag* bag = dynamic_cast<CBag*>(CUI);
		bag->Enter();
		bag->SetUse(true);
		trainerscene->Getbattlechoice()->SetUse(false);
		trainerscene->UIOnOff(false);
	}
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
	pNewSound->SetVolume(100.f);
	pNewSound->Play(false);
}

void CBattleChoice::PokemonChange()
{
	CScene* scene = CSceneMgr::GetInst()->GetCurScene();

	if (nullptr != dynamic_cast<CBattleScene*>(scene))
	{
		CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
		CPokemonSwap* swap = battlescene->GetPokemonSwap();
		swap->SetUse(true);
		swap->SetPokemonMember(battlescene->GetPokemonMember());
		swap->Enter();
		battlescene->Getbattlechoice()->SetUse(false);
		battlescene->UIOnOff(false);
	}
	else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
	{
		CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
		CPokemonSwap* swap = trainerscene->GetPokemonSwap();
		swap->SetUse(true);
		swap->SetPokemonMember(trainerscene->GetPokemonMember());
		swap->Enter();
		trainerscene->Getbattlechoice()->SetUse(false);
		trainerscene->UIOnOff(false);
	}
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
	pNewSound->SetVolume(100.f);
	pNewSound->Play(false);

	//m_SceneChangeOn = false;

}

void CBattleChoice::Run()
{
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\select.wav");
	pNewSound->SetVolume(100.f);
	pNewSound->Play(false);
	ChangeScene(SCENE_TYPE::START);
}
