#include "stdafx.h"
#include "CTackle.h"
#include "CPokemon.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CBattleScene.h"
#include "CTextBar.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTrainerBattle.h"
#include "CSound.h"
CTackle::CTackle()
{
	m_skillType=POKEMON_TYPE::NORMAL;
	m_skillcategory=SKILL_CATEGORY::PHYSICAL;
	m_skillname=L"몸통박치기";
	m_damage=40;
	m_Accuracy=100;
	m_pp = 35;
	m_ppMax = 35;

	
	m_skilleffect = CResMgr::GetInst()->FindTexture(L"Tackle");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"Tackle", L"Texture//Battle//Skill//Tackle.bmp");
	}
}

CTackle::~CTackle()
{

}

CTackle::CTackle(const CTackle& _origin):CSkill(_origin)
{
	m_skillType = POKEMON_TYPE::NORMAL;
	m_skillcategory = SKILL_CATEGORY::PHYSICAL;
	m_skillname = L"몸통박치기";
	m_damage = 40;
	m_Accuracy = 100;
	m_pp = 35;
	m_ppMax = 35;


	m_skilleffect = CResMgr::GetInst()->FindTexture(L"Tackle");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"Tackle", L"Texture//Battle//Skill//Tackle.bmp");
	}
}

void CTackle::SkillUse()
{
	if (m_pp > 0)
	{
		m_oPokemon->Damage(m_damagecount);
		m_pp--;
		
	}
}

void CTackle::SkillText()
{
	m_damagecount = Damagecount(m_iPokemon, m_oPokemon);
	CScene* scene = CSceneMgr::GetInst()->GetCurScene();
	wstring s;
	if (m_iPokemon->GetPlayerown())
		s = m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
	else
		s = L"야생 " + m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
	if (m_iPokemon->GetPlayerown())
	{
		if (nullptr != dynamic_cast<CBattleScene*>(scene))
		{
			CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
			battlescene->GetTextBar()->pushnexttext(s);
		}
		else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
		{
			CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
			trainerscene->GetTextBar()->pushnexttext(s);
		}
	}
}

void CTackle::render(HDC _dc)
{
	if (m_skillon)
	{

		if (m_iPokemon->GetPlayerown())
		{
			m_time += fDT * 1.f;
			if (m_time < 0.4)
			{

				Vec2 a = Vec2(m_iPokemon->GetPos().x + m_time * 3, m_iPokemon->GetPos().y);
				m_iPokemon->SetPos(a);
				if (m_textpush)
				{
					
					m_damagecount = Damagecount(m_iPokemon, m_oPokemon);
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();
			
					wstring s;
					if (m_iPokemon->GetPlayerown())
						s = m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
					else
						s = L"야생 " + m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
					if (nullptr != dynamic_cast<CBattleScene*>(scene))
					{
						CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						battlescene->GetTextBar()->pushnexttext(s);
					}
					else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
					{
						CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
						trainerscene->GetTextBar()->pushnexttext(s);
					}
					m_textpush = false;
				}
			}
			if (m_time >= 0.4 && m_time <= 0.7f)
			{
				TransparentBlt(_dc
					, 588 + 50
					, 88 + 50
					, m_skilleffect->Width(), m_skilleffect->Height()
					, m_skilleffect->GetDC()
					, 0, 0
					, m_skilleffect->Width(), m_skilleffect->Height()
					, RGB(255, 0, 255));
				Vec2 a = Vec2(m_iPokemon->GetPos().x - m_time * 1, m_iPokemon->GetPos().y);
				m_iPokemon->SetPos(a);
				a = Vec2(m_oPokemon->GetPos().x + m_time * 1, m_oPokemon->GetPos().y);
				m_oPokemon->SetPos(a);
				if (m_textpush2)
				{
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();
					
					wstring s;
					if (nullptr != dynamic_cast<CBattleScene*>(scene))
					{
						CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						if (m_effect_text > 0)
						{
							s += L"효과는 굉장했다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < 0 && m_effect_text >= -3)
						{
							s += L"효과가 별로인 듯하다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < -3)
						{
							s += L"효과가 없다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
					}
					else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
					{
						CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
						if (m_effect_text > 0)
						{
							s += L"효과는 굉장했다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < 0 && m_effect_text >= -3)
						{
							s += L"효과가 별로인 듯하다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < -3)
						{
							s += L"효과가 없다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
					}
				
					m_textpush2 = false;
				}
			}
			else if (m_time > 0.7f && m_time <= 0.8f) {
				Vec2 a = Vec2(m_oPokemon->GetPos().x - m_time * 1, m_oPokemon->GetPos().y);
				m_oPokemon->SetPos(a);
			}
			else if (m_time > 1.f)
			{
				m_iPokemon->SetPos(Vec2(160, 232));
				m_skillon = false;
				m_time = 0;
				m_textpush = true;
				m_textpush2 = true;
			}
		}
		else
		{
			m_time += fDT * 1.f;
			if (m_time < 0.4)
			{


				Vec2 a = Vec2(m_iPokemon->GetPos().x - m_time * 4, m_iPokemon->GetPos().y);
				m_iPokemon->SetPos(a);
				if (m_textpush)
				{


				


					m_damagecount = Damagecount(m_iPokemon, m_oPokemon);
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();
					
					
					wstring s;
					if (m_iPokemon->GetPlayerown())
						s = m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
					else
						s = L"야생 " + m_iPokemon->GetpName() + L"의 " + m_skillname + L"!\n";
					if (nullptr != dynamic_cast<CBattleScene*>(scene))
					{
						CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						battlescene->GetTextBar()->pushnexttext(s);
					}
					else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
					{
						CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
						trainerscene->GetTextBar()->pushnexttext(s);
					}

					
					m_textpush = false;
				}
			}
			if (m_time >= 0.4 && m_time <= 0.7f)
			{
				TransparentBlt(_dc
					, 160 + 50
					, 232 + 50
					, m_skilleffect->Width(), m_skilleffect->Height()
					, m_skilleffect->GetDC()
					, 0, 0
					, m_skilleffect->Width(), m_skilleffect->Height()
					, RGB(255, 0, 255));
				Vec2 a = Vec2(m_iPokemon->GetPos().x + m_time * 1, m_iPokemon->GetPos().y);
				m_iPokemon->SetPos(a);
				a = Vec2(m_oPokemon->GetPos().x - m_time * 1, m_oPokemon->GetPos().y);
				m_oPokemon->SetPos(a);
				if (m_textpush2)
				{
					CScene* scene = CSceneMgr::GetInst()->GetCurScene();
					if (nullptr != dynamic_cast<CBattleScene*>(scene))
					{
						CBattleScene* battlescene = dynamic_cast<CBattleScene*>(scene);
						wstring s;
						if (m_effect_text > 0)
						{
							s += L"효과는 굉장했다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < 0 && m_effect_text >= -3)
						{
							s += L"효과가 별로인 듯하다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < -3)
						{
							s += L"효과가 없다!\n";
							battlescene->GetTextBar()->pushnexttext(s);
						}
					}
					else if (nullptr != dynamic_cast<CTrainerBattle*>(scene))
					{
						CTrainerBattle* trainerscene = dynamic_cast<CTrainerBattle*>(scene);
						wstring s;
						if (m_effect_text > 0)
						{
							s += L"효과는 굉장했다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < 0 && m_effect_text >= -3)
						{
							s += L"효과가 별로인 듯하다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
						else if (m_effect_text < -3)
						{
							s += L"효과가 없다!\n";
							trainerscene->GetTextBar()->pushnexttext(s);
						}
					}

					
					m_textpush2 = false;
				}
			}
			else if (m_time > 0.7f && m_time <= 0.8f) {
				Vec2 a = Vec2(m_oPokemon->GetPos().x + m_time * 1, m_oPokemon->GetPos().y);
				m_oPokemon->SetPos(a);
			}
			else if (m_time > 1.f)
			{
				m_iPokemon->SetPos(Vec2(588, 48));
				m_skillon = false;
				m_time = 0;
				m_textpush = true;
				m_textpush2 = true;
			}
		}
	}
}