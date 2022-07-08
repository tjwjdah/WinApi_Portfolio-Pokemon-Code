#include "stdafx.h"
#include "CPokemon.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CSkill.h"
#include "CTackle.h"

CPokemon::CPokemon() :m_pType(POKEMON_TYPE::DEFAULT)
, m_pType2(POKEMON_TYPE::DEFAULT)
, m_pHABCDS()
, m_pTex(nullptr)
, m_pTex2(nullptr)
, m_pLv(1)
, mHp(0)
, m_exp(0),
m_maxexp(0),
m_dropexp(0),
mMax_hp(0),
m_attack(0),
m_block(0),
m_contact(0),
m_defence(0),
m_speed(0),
m_Playerown(false),
m_posx(-924),
m_battlerank(0),
m_skillamount(0),
m_pSkill1(nullptr),
m_pSkill2(nullptr),
m_pSkill3(nullptr),
m_pSkill4(nullptr),
m_showon(true)
{
	
	SetObjtype(OBJ_TYPE::POKEMON);
}

CPokemon::~CPokemon()
{

	if (m_pSkill1 != nullptr)
		delete m_pSkill1;
	if (m_pSkill2 != nullptr)
		delete m_pSkill2;
	if (m_pSkill3 != nullptr)
		delete m_pSkill3;
	if (m_pSkill4 != nullptr)
		delete m_pSkill4;

	
}

CPokemon::CPokemon(const CPokemon& _origin) :CObj(_origin),
m_pName(_origin.m_pName),
m_pType(_origin.m_pType)
, m_pType2(_origin.m_pType2)
, m_pHABCDS(_origin.m_pHABCDS)
, m_pTex(_origin.m_pTex)
, m_pTex2(_origin.m_pTex2)
, m_pLv(_origin.m_pLv)
, mHp(_origin.mHp)
, m_exp(_origin.m_exp)
, m_maxexp(_origin.m_maxexp)
, m_dropexp(_origin.m_dropexp),
mMax_hp(_origin.mMax_hp),
m_attack(_origin.m_attack),
m_block(_origin.m_block),
m_contact(_origin.m_contact),
m_defence(_origin.m_defence),
m_speed(_origin.m_speed),
m_Playerown(false),
m_posx(-924),
m_skillamount(_origin.m_skillamount),
m_battlerank(0),
m_showon(true)
{
	if(_origin.m_pSkill1 !=nullptr)
	m_pSkill1 = dynamic_cast<CSkill*>(_origin.m_pSkill1->Clone());
	if (_origin.m_pSkill2 != nullptr)
	m_pSkill2 = dynamic_cast<CSkill*>(_origin.m_pSkill2->Clone());
	if (_origin.m_pSkill3 != nullptr)
	m_pSkill3 = dynamic_cast<CSkill*>(_origin.m_pSkill3->Clone());
	if (_origin.m_pSkill4 != nullptr)
	m_pSkill4 = dynamic_cast<CSkill*>(_origin.m_pSkill4->Clone());
}


void CPokemon::LvUp()
{
	m_pLv++;
	
	mMax_hp = (int)(((float)(m_pHABCDS.Hp * 2) + (float)100) * (float)((float)m_pLv / (float)100) + 10);
	m_attack = (int)(((float)m_pHABCDS.Attack * (float)2) * (float)m_pLv / (float)100 + 10);
	m_block= (int)(((float)m_pHABCDS.Block * (float)2) * (float)m_pLv / (float)100 + 10);
	m_contact= (int)((float)(m_pHABCDS.Contact * (float)2) * (float)m_pLv / (float)100 + 10);
	m_defence= (int)(((float)m_pHABCDS.Defence * 2) * (float)m_pLv / (float)100 + 10);
	m_speed= (int)(((float)m_pHABCDS.Speed * 2) * (float)m_pLv / (float)100 + 10);
	//m_maxexp = (m_pLv ) * (m_pLv ) * (m_pLv );
	m_maxexp = 500;
	m_dropexp = 500;
	m_exp -= m_maxexp;;
}

void CPokemon::SetLv(int _Lv)
{
	m_pLv = _Lv;
	mMax_hp = (int)(((float)(m_pHABCDS.Hp * 2) + (float)100) * (float)((float)m_pLv / (float)100) + 10);
	m_attack = (int)(((float)m_pHABCDS.Attack * (float)2) * (float)m_pLv / (float)100 + 10);
	m_block = (int)(((float)m_pHABCDS.Block * (float)2) * (float)m_pLv / (float)100 + 10);
	m_contact = (int)((float)(m_pHABCDS.Contact * (float)2) * (float)m_pLv / (float)100 + 10);
	m_defence = (int)(((float)m_pHABCDS.Defence * 2) * (float)m_pLv / (float)100 + 10);
	m_speed = (int)(((float)m_pHABCDS.Speed * 2) * (float)m_pLv / (float)100 + 10);
	//m_maxexp = (m_pLv ) * (m_pLv ) * (m_pLv );
	m_maxexp = 500;
	m_dropexp = 500;
}

int CPokemon::Getskillamount()
{
	m_skillamount = 0;
	if (m_pSkill1 != nullptr)
		m_skillamount++;
	if (m_pSkill2 != nullptr)
		m_skillamount++;
	if (m_pSkill3 != nullptr)
		m_skillamount++;
	if (m_pSkill4 != nullptr)
		m_skillamount++;
	return m_skillamount;
}

void CPokemon::init()
{
	mMax_hp = (int)(((float)(m_pHABCDS.Hp * 2) + (float)100) * (float)((float)m_pLv / (float)100) + 10);
	mHp = mMax_hp;
	m_attack = (int)(((float)m_pHABCDS.Attack * (float)2) * (float)m_pLv / (float)100 + 10);
	m_block = (int)(((float)m_pHABCDS.Block * (float)2) * (float)m_pLv / (float)100 + 10);
	m_contact = (int)((float)(m_pHABCDS.Contact * (float)2) * (float)m_pLv / (float)100 + 10);
	m_defence = (int)(((float)m_pHABCDS.Defence * 2) * (float)m_pLv / (float)100 + 10);
	m_speed = (int)(((float)m_pHABCDS.Speed * 2) * (float)m_pLv / (float)100 + 10);
	//m_maxexp = (m_pLv ) * (m_pLv ) * (m_pLv );
	m_maxexp = 500;
	m_dropexp = 500;



}

void CPokemon::update()
{




}

void CPokemon::render(HDC _dc)
{
	if (m_showon)
	{
		if (m_Playerown == true)
		{
			TransparentBlt(_dc
				, GetPos().x
				, GetPos().y
				, m_pTex->Width(), m_pTex->Height() / 2
				, m_pTex->GetDC()
				, 0, (m_pTex->Height() / 2)
				, m_pTex->Width(), m_pTex->Height() / 2
				, RGB(255, 0, 255));
		}
		else
		{
			TransparentBlt(_dc
				, GetPos().x
				, GetPos().y
				, m_pTex->Width(), m_pTex->Height() / 2
				, m_pTex->GetDC()
				, 0, 0
				, m_pTex->Width(), m_pTex->Height() / 2
				, RGB(255, 0, 255));
		}
	}
}
