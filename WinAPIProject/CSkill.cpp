#include "stdafx.h"
#include "CSkill.h"

#include "CPokemon.h"
CSkill::CSkill() :m_effect_text(0),
m_iPokemon(nullptr),
m_oPokemon(nullptr),
m_skillType(POKEMON_TYPE::NONE),
m_skillcategory(SKILL_CATEGORY::DEFAULT),
m_damage(0),
m_Accuracy(0),
m_pp(0),
m_ppMax(0),
m_time(0.f),
m_skillon(false),
m_skilleffect(nullptr),
m_textpush(true),
m_textpush2(true),
m_damagecount(0)
{
}

CSkill::~CSkill()
{
}

CSkill::CSkill(const CSkill& _origin):CObj(_origin),
	m_iPokemon(nullptr),
	m_oPokemon(nullptr),
	m_skillType(_origin.m_skillType),
	m_skillcategory(_origin.m_skillcategory),
	m_damage(_origin.m_damage),
	m_Accuracy(_origin.m_Accuracy),
	m_ppMax(_origin.m_ppMax),
	m_pp(_origin.m_ppMax),
	m_time(0.f),
	m_skillon(false),
	m_skilleffect(nullptr),
	m_textpush(true),
	m_textpush2(true),
	m_damagecount(0)
{
}

int CSkill::Damagecount(CPokemon* _iPokemon, CPokemon* _oPokemon)
{
	int damage = 0;
	if (m_skillcategory == SKILL_CATEGORY::PHYSICAL)
		damage = ((((float)_iPokemon->GetLv() * 2.f / 5.f) + 2.f) * (float)m_damage * (float)_iPokemon->GetAttack() * (2.f + (float)_iPokemon->Getbattlerank() / 2.f) / 50.f) / ((float)_oPokemon->Getblock() * (2.f + (float)_oPokemon->Getbattlerank() / 2.f));
	if (m_skillcategory == SKILL_CATEGORY::SPECIAL)
		damage = ((((float)_iPokemon->GetLv() * 2.f / 5.f) + 2.f) * (float)m_damage * (float)_iPokemon->Getcontact() * (2.f + (float)_iPokemon->Getbattlerank() / 2.f) / 50.f) / ((float)_oPokemon->Getdefence() * (2.f + (float)_oPokemon->Getbattlerank() / 2.f));
	if (damage == 0)
		damage = 1;
	if (_iPokemon->GetPokemonType1() == m_skillType || _iPokemon->GetPokemonType2() == m_skillType)
		damage = damage * 1.5f;
	m_effect_text = 0;
	switch (m_skillType)
	{
	case POKEMON_TYPE::NORMAL:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GHOST:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::FIRE:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage =damage * 2;
			m_effect_text++;
			break;
		}
	}
		break;
	case POKEMON_TYPE::WATER:
	{
		switch (_oPokemon->GetPokemonType1())
		{
	
		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::WATER:
			damage =damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = (float)damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::GRASS:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::ELECTRIC:
	{
		switch (_oPokemon->GetPokemonType1())
		{
	
		case POKEMON_TYPE::WATER:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::ICE:
	{
		switch (_oPokemon->GetPokemonType1())
		{
	
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::FIGHTING:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::NORMAL:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;

		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::POISON:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage * 2;
			m_effect_text++;
			break;
		}
	}
		break;
	case POKEMON_TYPE::GROUND:
	{
		switch (_oPokemon->GetPokemonType1())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::FLYING:
			damage = 0;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage * 2;
			break;
		}
	}
		break;
	case POKEMON_TYPE::FLYING:
	{
		switch (_oPokemon->GetPokemonType1())
		{
	
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::PSYCHIC:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DARK:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::BUG:
	{
		switch (_oPokemon->GetPokemonType1())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage *2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::ROCK:
	{
		switch (_oPokemon->GetPokemonType1())
		{
	
		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::GHOST:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::NORMAL:
			damage = 0;
			m_effect_text = -10;
			break;
		
		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	case POKEMON_TYPE::DRAGON:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = 0;
			m_effect_text = -10;
			break;
		}
	}
		break;
	case POKEMON_TYPE::DARK:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;

		}
	}
		break;
	case POKEMON_TYPE::STEEL:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage * 2;
			m_effect_text++;
			break;
		}
	}
		break;
	case POKEMON_TYPE::FAIRY:
	{
		switch (_oPokemon->GetPokemonType1())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
		break;
	}


	switch (m_skillType)
	{
	case POKEMON_TYPE::NORMAL:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GHOST:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::FIRE:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage * 2;
			m_effect_text++;
			break;
		}
	}
	break;
	case POKEMON_TYPE::WATER:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::GRASS:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::ELECTRIC:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::WATER:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::ICE:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::FIGHTING:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::NORMAL:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;

		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::POISON:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage * 2;
			m_effect_text++;
			break;
		}
	}
	break;
	case POKEMON_TYPE::GROUND:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage / 2;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::FLYING:
			damage = 0;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage / 2;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage * 2;
			break;
		}
	}
	break;
	case POKEMON_TYPE::FLYING:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::PSYCHIC:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DARK:
			damage = 0;
			m_effect_text = -10;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::BUG:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GRASS:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::POISON:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::ROCK:
	{
		switch (_oPokemon->GetPokemonType2())
		{

		case POKEMON_TYPE::FIRE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::GROUND:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FLYING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::BUG:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::GHOST:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::NORMAL:
			damage = 0;
			m_effect_text = -10;
			break;

		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	case POKEMON_TYPE::DRAGON:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = 0;
			m_effect_text = -10;
			break;
		}
	}
	break;
	case POKEMON_TYPE::DARK:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIGHTING:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::PSYCHIC:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::GHOST:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage / 2;
			m_effect_text--;
			break;

		}
	}
	break;
	case POKEMON_TYPE::STEEL:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::WATER:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ELECTRIC:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::ICE:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::ROCK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FAIRY:
			damage = damage * 2;
			m_effect_text++;
			break;
		}
	}
	break;
	case POKEMON_TYPE::FAIRY:
	{
		switch (_oPokemon->GetPokemonType2())
		{
		case POKEMON_TYPE::FIRE:
			damage = damage / 2;
			m_effect_text--;
			break;
		case POKEMON_TYPE::FIGHTING:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DRAGON:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::DARK:
			damage = damage * 2;
			m_effect_text++;
			break;
		case POKEMON_TYPE::STEEL:
			damage = damage / 2;
			m_effect_text--;
			break;
		}
	}
	break;
	}
	if (damage == 0)
		damage = 1;
	return damage;
}

void CSkill::SkillText()
{
}

void CSkill::SkillUse()
{
}


wstring CSkill::GetSkillType_ToString()
{
	switch (m_skillType)
	{
	case POKEMON_TYPE::NORMAL:
		return L"노말";
		break;
	case POKEMON_TYPE::FIRE:
		return L"불";
		break;
	case POKEMON_TYPE::WATER:
		return L"물";
		break;
	case POKEMON_TYPE::GRASS:
		return L"풀";
		break;
	case POKEMON_TYPE::ELECTRIC:
		return L"전기";
		break;
	case POKEMON_TYPE::ICE:
		return L"얼음";
		break;
	case POKEMON_TYPE::FIGHTING:
		return L"격투";
		break;
	case POKEMON_TYPE::POISON:
		return L"독";
		break;
	case POKEMON_TYPE::GROUND:
		return L"땅";
		break;
	case POKEMON_TYPE::FLYING:
		return L"비행";
		break;
	case POKEMON_TYPE::PSYCHIC:
		return L"에스퍼";
		break;
	case POKEMON_TYPE::BUG:
		return L"벌레";
		break;
	case POKEMON_TYPE::ROCK:
		return L"바위";
		break;
	case POKEMON_TYPE::GHOST:
		return L"고스트";
		break;
	case POKEMON_TYPE::DRAGON:
		return L"드래곤";
		break;
	case POKEMON_TYPE::DARK:
		return L"악";
		break;
	case POKEMON_TYPE::STEEL:
		return L"강철";
		break;
	case POKEMON_TYPE::FAIRY:
		return L"페어리";
		break;
	case POKEMON_TYPE::NONE:
		return L"";
		break;
	}
 
}
