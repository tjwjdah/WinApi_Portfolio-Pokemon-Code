#include "stdafx.h"
#include "CVineWhip.h"

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

CVineWhip::CVineWhip()
{
	m_skillType = POKEMON_TYPE::GRASS;
	m_skillcategory = SKILL_CATEGORY::PHYSICAL;
	m_skillname = L"덩굴채찍";
	m_damage = 60;
	m_Accuracy = 100;
	m_pp = 20;
	m_ppMax = 20;


	m_skilleffect = CResMgr::GetInst()->FindTexture(L"VineWhip");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"VineWhip", L"Texture//Battle//Skill//VineWhip.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"VineWhip_Anim", m_skilleffect, Vec2(0.f, 0.f), Vec2(128.f, 128.f), 5, 0.1f);
	pAnimator->AddAnimation(L"VineWhip_Anim2", m_skilleffect, Vec2(0.f, 128.f), Vec2(128.f, 128.f), 5, 0.1f);
	
	AddAnimator(pAnimator);

}

CVineWhip::~CVineWhip()
{
}

CVineWhip::CVineWhip(const CVineWhip& _origin)
{
	m_skillType = POKEMON_TYPE::GRASS;
	m_skillcategory = SKILL_CATEGORY::PHYSICAL;
	m_skillname = L"덩굴채찍";
	m_damage = 60;
	m_Accuracy = 100;
	m_pp = 20;
	m_ppMax = 20;


	m_skilleffect = CResMgr::GetInst()->FindTexture(L"VineWhip");
	if (nullptr == m_skilleffect)
	{
		m_skilleffect = CResMgr::GetInst()->LoadTexture(L"VineWhip", L"Texture//Battle//Skill//VineWhip.bmp");
	}
	CAnimator* pAnimator = new CAnimator;
	pAnimator->AddAnimation(L"VineWhip_Anim", m_skilleffect, Vec2(0.f, 0.f), Vec2(128.f, 128.f), 5, 0.1f);
	pAnimator->AddAnimation(L"VineWhip_Anim2", m_skilleffect, Vec2(0.f, 128.f), Vec2(128.f, 128.f), 5, 0.1f);

	AddAnimator(pAnimator);
}

void CVineWhip::SkillUse()
{

	if (m_pp > 0)
	{
		m_oPokemon->Damage(m_damagecount);
		m_pp--;

	}
}

void CVineWhip::SkillText()
{
}


void CVineWhip::render(HDC _dc)
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
					


					SetPos(Vec2(576.f, 42.f));
					GetAnimator()->Play(L"VineWhip_Anim", false);
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

					SetPos(Vec2(320.f, 200.f));
					GetAnimator()->Play(L"VineWhip_Anim2", false);
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
