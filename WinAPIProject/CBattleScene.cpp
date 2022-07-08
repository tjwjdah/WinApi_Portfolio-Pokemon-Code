#include "stdafx.h"
#include "CBattleScene.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CTimeMgr.h"

#include "CKeyMgr.h"

#include "CEventMgr.h"

#include "CAnimator.h"
#include "CTextBar.h"
#include  "CPlayerBattleState_Bar.h"
#include  "COtherBattleState_Bar.h"

#include "CPlayer_BattleAni.h"
#include "CStartmonterball.h"

#include "CBattleChoice.h"

#include "CPokemon.h"

#include "CSkill.h"
#include "CTackle.h"

#include "CPokemonSwap.h"
#include "CBag.h"
#include "CPlayer.h"
#include "CSoundMgr.h"
#include "CSound.h"

CBattleScene::CBattleScene() :
	m_sBackGround(nullptr),
	m_noinit(false),
	m_starani_y1(0),
	m_startanimation(nullptr),
	m_startanimation2(nullptr),
	m_playerplace(nullptr),
	m_otherplace(nullptr),
	m_battepage(0),
	m_starani_y2(0),
	m_starani_y3(0),
	m_pbattleplayer(nullptr),
	p_opponentpokemon(nullptr),
	m_BattleTextbar(nullptr),
	m_skilltime(0.f),
	m_battlechoice(nullptr),
	m_OtherBattleStatebar(nullptr),
	m_endtime1(0.f),
	m_starani_y4(0),
	m_endtime2(0.f),
	m_Swap(nullptr),
	m_ChangePokemonTime(0.f),
	m_Player(nullptr),
	m_ChangePokemonOn(false)
{
}

CBattleScene::~CBattleScene()
{
	// 차후에 수정
	if (p_opponentpokemon != nullptr)
	delete p_opponentpokemon;
	/*if(m_battlechoice !=nullptr)
	delete m_battlechoice;
	if(m_OtherBattleStatebar!=nullptr)
	delete m_OtherBattleStatebar;
	if(m_BattleTextbar !=nullptr)
	delete m_BattleTextbar;
	if(m_battlechoice != nullptr)
	delete m_battlechoice;*/
}

void CBattleScene::timeEvenadd(CObj* _pNewObj, Vec2 _vPos, OBJ_TYPE _eType, float _dtime)
{
	_pNewObj->SetPos(_vPos);

	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.wParam = (DWORD_PTR)_pNewObj;
	evn.lParam = (DWORD_PTR)_eType;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CBattleScene::timeEvenadd(CObj* _pDeleteObj, float _dtime)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)_pDeleteObj;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CBattleScene::timeEvenadd(SCENE_TYPE _eNextScene, float _dtime)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.wParam = (DWORD_PTR)_eNextScene;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CBattleScene::timeskillpush(CSkill* _skill)
{
	int a = p_opponentpokemon->Getskillamount();
	int b = rand() % a;

	if (_skill == nullptr)
	{
		switch (b)
		{
		case 0:
			p_opponentpokemon->GetSkill1()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill1());
			return;
			break;
		case 1:
			p_opponentpokemon->GetSkill2()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill2());
			return;
			break;
		case 2:
			p_opponentpokemon->GetSkill3()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill3());
			return;
			break;
		case 3:
			p_opponentpokemon->GetSkill4()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill4());
			return;
			break;
		}
	}
	
	if (m_PokemonMember[0]->GetSpeed() >= p_opponentpokemon->GetSpeed())
	{
		m_timebattleplay.push_back(_skill);
		switch (b)
		{
		case 0:
			p_opponentpokemon->GetSkill1()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill1());
			break;
		case 1:
			p_opponentpokemon->GetSkill2()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill2());
			break;
		case 2:
			p_opponentpokemon->GetSkill3()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill3());
			break;
		case 3:
			p_opponentpokemon->GetSkill4()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill4());
			break;
		}
	}
	else
	{
		switch (b)
		{
		case 0:
			p_opponentpokemon->GetSkill1()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill1());
			m_timebattleplay.push_back(_skill);
			break;
		case 1:
			p_opponentpokemon->GetSkill2()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill2());
			m_timebattleplay.push_back(_skill);
			break;
		case 2:
			p_opponentpokemon->GetSkill3()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill3());
			m_timebattleplay.push_back(_skill);
			break;
		case 3:
			p_opponentpokemon->GetSkill4()->Settarget(p_opponentpokemon, m_PokemonMember[0]);
			m_timebattleplay.push_back(p_opponentpokemon->GetSkill4());
			m_timebattleplay.push_back(_skill);
			break;

		}
	}
	
}

void CBattleScene::PokemonChange()
{
	GetStartmonterball()->Run();
	m_PlayerBattleStateber->SetPokemon(m_PokemonMember[0]);
	wstring s = L"이젠 됐어! 돌아와!       가랏!" + m_PokemonMember[0]->GetpName() + L"!\n";
	m_BattleTextbar->pushnexttext(s);
	m_OtherBattleStatebar->SetUse(true);
	m_PlayerBattleStateber->SetUse(true);
	m_ChangePokemonOn = true;
	m_BattleTextbar->SetUse(true);
	m_battlechoice->SetPokemon(m_PokemonMember[0], p_opponentpokemon);
}






void CBattleScene::init()
{

	m_sBackGround = CResMgr::GetInst()->FindTexture(L"battlebackground");
	if (nullptr == m_sBackGround)
	{
		m_sBackGround = CResMgr::GetInst()->LoadTexture(L"battlebackground", L"Texture//Battle//battlebackground.bmp");
	}

	m_startanimation = CResMgr::GetInst()->FindTexture(L"startanimation");
	if (nullptr == m_startanimation)
	{
		m_startanimation = CResMgr::GetInst()->LoadTexture(L"startanimation", L"Texture//Battle//startanimation.bmp");
	}

	m_startanimation2 = CResMgr::GetInst()->FindTexture(L"startanimation3");
	if (nullptr == m_startanimation2)
	{
		m_startanimation2 = CResMgr::GetInst()->LoadTexture(L"startanimation3", L"Texture//Battle//startanimation3.bmp");
	}

	m_playerplace = CResMgr::GetInst()->FindTexture(L"playerplace");
	if (nullptr == m_playerplace)
	{
		m_playerplace = CResMgr::GetInst()->LoadTexture(L"playerplace", L"Texture//Battle//playerplace.bmp");
	}

	m_otherplace = CResMgr::GetInst()->FindTexture(L"otherplace");
	if (nullptr == m_otherplace)
	{
		m_otherplace = CResMgr::GetInst()->LoadTexture(L"otherplace", L"Texture//Battle//otherplace.bmp");
	}
	

	
	m_pbattleplayer = CResMgr::GetInst()->FindTexture(L"battleplayer");
	if (nullptr == m_pbattleplayer)
	{
		m_pbattleplayer = CResMgr::GetInst()->LoadTexture(L"battleplayer", L"Texture//Battle//battleplayer.bmp");
	}

	

	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"Charmander");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Charmander", L"Texture//Pokemon//Charmander.bmp");
	}
	
	/*CObj* pObj = new CPokemon;
	CPokemon* pokemon = dynamic_cast<CPokemon*>(pObj);
	pokemon->SetTex1(m_pTex);
	pokemon->SetLv(5);
	pokemon->SetPos(Vec2(160, 232));
	pokemon->SetHABCDS(HABCDS(39, 52, 43, 60, 50, 65));
	pokemon->SetName(L"파이리");
	pokemon->SetType(POKEMON_TYPE::FIRE);
	pokemon->init();
	CSkill* skill1 = new CTackle();
	CSkill* skill2 = new CTackle();
	CSkill* skill3 = new CTackle();
	CSkill* skill4 = new CTackle();
	pokemon->SetSkill(skill1, skill2, skill3, skill4);
	p_opponentpokemon = pokemon->Clone();
	p_playerpokemon = pokemon;
	pokemon->SetPlayerown(true);*/

	
	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Battle(VSWildPokemon).wav", L"Sound\\Battle(VSWildPokemon).wav");


	

	/*CObj* pObj = new CPlayer_BattleAni;
	pObj->SetPos(Vec2(192.f, 192.f));
	pObj->init();
	pObj->SetScale(Vec2(50.f, 50.f));
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	AddObj(pObj, OBJ_TYPE::PLAYER);
	*/
	srand((unsigned int)time(0));
	m_noinit = true;
	CCamera::GetInst()->init();
}

void CBattleScene::Enter()
{
	if(!m_noinit)
	init();
	CUI* pUI = new CPokemonSwap;
	m_Swap = dynamic_cast<CPokemonSwap*>(pUI);
	m_Swap->SetPokemonMember(m_PokemonMember);
	m_Swap->init();
	pUI->SetUse(false);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	AddObj(pUI, OBJ_TYPE::UI);

	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"textbar");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"textbar", L"Texture//Battle//textbar.bmp");
	}
	 pUI = new CTextBar;
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(0, 448));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	AddObj(pUI, OBJ_TYPE::UI);


	m_BattleTextbar = dynamic_cast<CTextBar*>(pUI);
	m_BattleTextbar->Set_battleOn(true);
	wstring text = L"앗! 야생의 " + p_opponentpokemon->GetpName() + L"(이)가\n튀어나왔다!\n가랏! " + m_PokemonMember[0]->GetpName() + L"!\n" + m_PokemonMember[0]->GetpName() + L"는(은) \t무엇을 할까?\n";
	
	m_pTex = CResMgr::GetInst()->FindTexture(L"otherHp_bar");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"otherHp_bar", L"Texture//Battle//otherHp_bar.bmp");
	}

	pUI = new COtherBattleState_Bar;
	m_OtherBattleStatebar = dynamic_cast<COtherBattleState_Bar*>(pUI);
	m_OtherBattleStatebar->SetPokemon(p_opponentpokemon);
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(52, 64));
	pUI->SetUse(true);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	timeEvenadd(pUI, pUI->GetPos(), OBJ_TYPE::UI);

	


	m_BattleTextbar->pushnexttext(text);
	m_starani_y1 = 0;
	m_starani_y2 = 0;
	m_starani_y3 = 0;
	m_starani_y4 = 0;
	m_battepage = 0;
	m_endtime1 = 0.f;
	m_endtime2 = 0.f;
	m_OtherBattleStatebar->SetPokemon(p_opponentpokemon);

	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Battle(VSWildPokemon).wav");
	pNewSound->PlayToBGM(true);
	pNewSound->SetVolume(100.f);
	CCamera::GetInst()->Setcamera(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f));
}





void CBattleScene::Exit()
{

	delete p_opponentpokemon;
	p_opponentpokemon = nullptr;
	
	DeleteAllObject();
	
}





void CBattleScene::update()
{
	CScene::update();
	if (m_PokemonMember[0] != nullptr)
		m_PokemonMember[0]->update();
	if (p_opponentpokemon != nullptr)
		p_opponentpokemon->update();

	battepage_event(m_battepage);

	if (KEY_TAP(KEY_TYPE::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}

	if (m_starani_y1 >= 500.f)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			m_starani_y2++;
			if (m_starani_y2 == 2)
				m_battepage++;
		}
	}
	if (!(m_timeEventplay.empty()))
	{
		m_timeEventplay.front().cTime += fDT;
		if (m_timeEventplay.front().dTime < m_timeEventplay.front().cTime)
		{

			CEventMgr::GetInst()->AddEvent(m_timeEventplay.front());
			m_timeEventplay.pop_front();
		}
	}
	if (m_ChangePokemonOn)
	{
		m_ChangePokemonTime += fDT;
		if (m_ChangePokemonTime > 1.f)
		{
			m_ChangePokemonTime = 0;
			m_ChangePokemonOn = false;
			m_battlechoice->SetUse(true);
			m_battlechoice->SetShow(false);
			timeskillpush(nullptr);
			
		}
	}
	if (m_Player_Bag->GetUse())
		m_Player_Bag->update();

}
void CBattleScene::render(HDC _dc)
{
	if (m_starani_y1 <= 500.f)
	{	
		m_starani_y1 += fDT * 300;
	}
	BitBlt(_dc
		, 0
		, 0
		, m_sBackGround->Width()
		, m_sBackGround->Height()
		, m_sBackGround->GetDC()
		, 0
		, 0, SRCCOPY);  //기본 백그라운드

	
	
		TransparentBlt(_dc
			, 960+ 540 -(m_starani_y1*3)
			, 360
			, m_playerplace->Width(), m_playerplace->Height()
			, m_playerplace->GetDC()
			, 0, 0
			, m_playerplace->Width(), m_playerplace->Height()
			, RGB(255, 0, 255));

	

		TransparentBlt(_dc
			, -(512+540 - (m_starani_y1 * 3))
			, 128
			, m_otherplace->Width(), m_otherplace->Height()
			, m_otherplace->GetDC()
			, 0, 0
			, m_otherplace->Width(), m_otherplace->Height()
			, RGB(255, 0, 255));

		

		if (m_battepage < 1)
		{
			TransparentBlt(_dc
				, 960 + 732 - (m_starani_y1 * 3)
				, 192
				, m_pbattleplayer->Width(), m_pbattleplayer->Height()
				, m_pbattleplayer->GetDC()
				, 0, 0
				, m_pbattleplayer->Width(), m_pbattleplayer->Height()
				, RGB(255, 0, 255));
			p_opponentpokemon->SetPos(Vec2(-(512 + 400 - (m_starani_y1 * 3)), 88.f));
		}

	if (m_starani_y1 <= 500.f) {
		TransparentBlt(_dc
			, 0
			, 48+ m_starani_y1/3+15
			, 960, m_startanimation2->Height()
			, m_startanimation2->GetDC()
			, m_starani_y1 * 4, 0
			, 960, m_startanimation2->Height()

			, RGB(255, 0, 255));
	}
	
	
	if (m_battepage >= 4 && m_ThrowMonterball->Getend())
	{
		if (nullptr != m_PokemonMember[0])
			m_PokemonMember[0]->render(_dc);

	}
	if (p_opponentpokemon != nullptr)
		p_opponentpokemon->render(_dc);

	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{

		vector<CObj*>& vecObj = GetObjects2((OBJ_TYPE)i);
		vector<CObj*>::iterator iter = vecObj.begin();

		for (; iter != vecObj.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = vecObj.erase(iter);
			}
			else
			{
				(*iter)->render(_dc);
				++iter;
			}
		}
	}
	if (m_starani_y1 <= 360.f) {
		
		BitBlt(_dc
			, 0
			, 0
			, m_startanimation->Width()
			, m_startanimation->Height()- m_starani_y1
			, m_startanimation->GetDC()
			, 0
			, 0, SRCCOPY);
		BitBlt(_dc
			, 0
			, 320 + m_starani_y1
			, m_startanimation->Width()
			, m_startanimation->Height()- m_starani_y1
			, m_startanimation->GetDC()
			, 0
			, 0, SRCCOPY);
	}




	if (!m_timebattleplay.empty())
	{
	
	
		
		m_timebattleplay.front()->skillon(true);
		m_timebattleplay.front()->render(_dc);
		m_skilltime += fDT*1.f;
		if (m_skilltime > 1)
		{
			
			m_timebattleplay.front()->SkillUse();
			m_skilltime = 0.f;
			m_timebattleplay.pop_front();
			if (m_PokemonMember[0]->GetmHP() <= 0 || p_opponentpokemon->GetmHP() <= 0)
			{
				m_timebattleplay.clear();
				m_battepage++;
				wstring s;
				if (p_opponentpokemon->GetmHP() <= 0)
				{
					s = L"야생 " + p_opponentpokemon->GetpName() + L"는(은)           쓰러졌다!.\n";
					m_BattleTextbar->pushnexttext(s);
					s = m_PokemonMember[0]->GetpName() + L"는(은)           " + std::to_wstring(p_opponentpokemon->GetDropexp()) + L" 경험치를 얻었다!.";
					m_BattleTextbar->pushtext(s);
				
					
				}
				
			}
		}
	}
	else
	{
		if (m_PokemonMember[0]->GetmHP() >0 && p_opponentpokemon->GetmHP() > 0)
		if (m_battlechoice != nullptr) {
			m_battlechoice->SetShow(true);
			
		}
	}

	if (m_Player_Bag->GetUse())
		m_Player_Bag->render(_dc);
}



void CBattleScene::SetPlayer(CPlayer* _player)
{
	m_Player = _player; 
	m_Player_Bag = _player->GetBag();
}

void CBattleScene::battepage_event(int _page)
{
	switch (_page)
	{
	case 1:
	{
		CObj* pObj = new CPlayer_BattleAni;
		pObj->SetPos(Vec2(188.f, 192.f));
		pObj->init();
		pObj->SetScale(Vec2(50.f, 50.f));
		//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
		timeEvenadd(pObj, Vec2(pObj->GetPos()), OBJ_TYPE::DEFAULT);
		CObj* pObj2 = new CStartmonterball;
		m_ThrowMonterball = dynamic_cast<CStartmonterball*>(pObj2);
		pObj2->SetPos(Vec2(110.f, 250.f));
		pObj2->init();
		//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
		timeEvenadd(pObj2, Vec2(pObj2->GetPos()), OBJ_TYPE::DEFAULT, 1.0f);
		m_battepage++;
	}
	break;
	case 2:
	{
		CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"Hp_bar");
		if (nullptr == m_pTex)
		{
			m_pTex = CResMgr::GetInst()->LoadTexture(L"Hp_bar", L"Texture//Battle//Hp_bar.bmp");
		}
		CUI* pUI = new CPlayerBattleState_Bar;
		m_PlayerBattleStateber = dynamic_cast<CPlayerBattleState_Bar*>(pUI);
		m_PlayerBattleStateber->SetPokemon(m_PokemonMember[0]);
		pUI->SetTexture(m_pTex);
		pUI->SetScale(Vec2(m_pTex->Width(), m_pTex->Height()));
		pUI->SetPos(Vec2(514, 300));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::DEFAULT);
		timeEvenadd(pUI, Vec2(514, 300), OBJ_TYPE::UI, 1.0f);
		m_battepage++;
	}
	break;
	case 3:
	{
		m_starani_y3 += fDT * 300;
		if (m_starani_y3 > 400)
			m_battepage++;
	}
	break;
	case 4:
	{
		CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"BatteChoice");
		if (nullptr == m_pTex)
		{
			m_pTex = CResMgr::GetInst()->LoadTexture(L"BatteChoice", L"Texture//Battle//BatteChoice.bmp");
		}

		CUI* pUI = new CBattleChoice;
		m_battlechoice = dynamic_cast<CBattleChoice*>(pUI);
		pUI->SetTexture(m_pTex);
		pUI->SetScale(Vec2(m_pTex->Width(), m_pTex->Height()));
		pUI->SetPos(Vec2(480, 448));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::DEFAULT);
		m_battlechoice->SetPokemon(m_PokemonMember[0], p_opponentpokemon);
		AddObj(pUI, OBJ_TYPE::UI);
		m_battepage++;
	}
	case 5:
	{
		break;
	}
	case 6:
	{
		m_endtime1 += fDT;
		if (m_endtime1 > 1.5f)
		{
			m_battepage++;
			
		}
	}
	break;
	case 7: {
		if (p_opponentpokemon->GetmHP() <= 0)
		{
			m_OtherBattleStatebar->SetUse(false);
			Vec2 v = Vec2(p_opponentpokemon->GetPos().x, p_opponentpokemon->GetPos().y+fDT*200);
			p_opponentpokemon->SetPos(v);
			if (p_opponentpokemon->GetPos().y >= 280)
			{
				m_PokemonMember[0]->expup(p_opponentpokemon->GetDropexp());
				m_battepage++;
			}
		}
		
	}
		  break;
	case 8:
	{
		if (m_starani_y1 >= 500.f)
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				m_starani_y4++;
				if (m_starani_y4 == 2)
					m_battepage++;
			}
		}
	}
	break;
	case 9:
		m_endtime2 += fDT;
		if (m_endtime2 > 1.0f) {
			ChangeScene(SCENE_TYPE::START);
		}
		break;
	}
}

void CBattleScene::UIOnOff(bool _onoff)
{
	m_battlechoice->SetUse(_onoff);
	m_OtherBattleStatebar->SetUse(_onoff);
	m_PlayerBattleStateber->SetUse(_onoff);
	m_BattleTextbar->SetUse(_onoff);
}
