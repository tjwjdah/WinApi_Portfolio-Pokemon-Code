#include "stdafx.h"
#include "CPsybeam.h"

#include "CPokemon.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CBattleScene.h"
#include "CTextBar.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTrainerBattle.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"
CPsybeam::CPsybeam()
{
	m_skillType = POKEMON_TYPE::PSYCHIC;
	m_skillcategory = SKILL_CATEGORY::SPECIAL;
	m_skillname = L"환상빔";
	m_damage = 65;
	m_Accuracy = 100;
	m_pp = 20;
	m_ppMax = 20;


	m_skilleffect = CResMgr::GetInst()->FindTexture(L"Psybeam2");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"Psybeam2", L"Texture//Battle//Skill//Psybeam2.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"Psybeam_Anim", m_skilleffect, Vec2(0.f, 0.f), Vec2(388.f, 256.f), 8, 0.1f);
	pAnimator->AddAnimation(L"Psybeam_Anim2", m_skilleffect, Vec2(0.f, 256.f), Vec2(388.f, 256.f), 8, 0.1f);
	SetPos(Vec2(336.f, 112.f));
	AddAnimator(pAnimator);
}

CPsybeam::~CPsybeam()
{
}

CPsybeam::CPsybeam(const CPsybeam& _origin)
{
	m_skillType = POKEMON_TYPE::PSYCHIC;
	m_skillcategory = SKILL_CATEGORY::SPECIAL;
	m_skillname = L"환상빔";
	m_damage = 65;
	m_Accuracy = 100;
	m_pp = 20;
	m_ppMax = 20;


	m_skilleffect = CResMgr::GetInst()->FindTexture(L"Psybeam2");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"Psybeam2", L"Texture//Battle//Skill//Psybeam2.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"Psybeam_Anim", m_skilleffect, Vec2(0.f, 0.f), Vec2(388.f, 256.f), 8, 0.1f);
	pAnimator->AddAnimation(L"Psybeam_Anim2", m_skilleffect, Vec2(0.f, 256.f), Vec2(388.f, 256.f), 8, 0.1f);

	AddAnimator(pAnimator);
	SetPos(Vec2(336.f, 112.f));
}

void CPsybeam::SkillUse()
{
	if (m_pp > 0)
	{
		m_oPokemon->Damage(m_damagecount);
	
		m_pp--;

	}
}

void CPsybeam::SkillText()
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

void CPsybeam::render(HDC _dc)
{
	if (nullptr != GetAnimator())
	{
		GetAnimator()->finalupdate();

		GetAnimator()->render(_dc);

	}

	if (m_skillon)
	{

		if (m_iPokemon->GetPlayerown())
		{
			
			m_time += fDT * 1.f;

			if (m_time < 0.4)
			{

				
				if (m_textpush)
				{
					

					GetAnimator()->Play(L"Psybeam_Anim1", false);
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
			
			
				Vec2 a = Vec2(m_oPokemon->GetPos().x + m_time * 1, m_oPokemon->GetPos().y);
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
			
				if (m_textpush)
				{
					

					GetAnimator()->Play(L"Psybeam_Anim2", false);
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
			
				
				Vec2 a = Vec2(m_oPokemon->GetPos().x - m_time * 1, m_oPokemon->GetPos().y);
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
