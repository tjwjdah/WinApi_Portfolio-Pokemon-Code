#include "stdafx.h"
#include "CObjectMgr.h"

#include "CObj.h"
#include "CBaseObject.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CHouse.h"
#include "CDoor.h"
#include "CChangeplaceobj.h"
#include "CPokemonSpawnObj.h"
#include "CJumpwallObj.h"
#include "CPokemon.h"
#include "CTackle.h"
#include "CAnimation.h"
#include "CAnimator.h"
CObjectMgr::CObjectMgr()
{


}

CObjectMgr::~CObjectMgr()
{
	for (auto& pair : m_mapObj)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}

	for (auto& pair : m_mapPokemon)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}
}
void CObjectMgr::init()
{
	
	{ //0Ä­Â¥¸® baseobject
		createBaseObj(L"closet", L"Texture//Objects//BaseObject1//closet.bmp",  0, 1, 1);
		createBaseObj(L"desk", L"Texture//Objects//BaseObject1//desk.bmp", 0, 2, 1);
		createBaseObj(L"doctorcomputer3", L"Texture//Objects//BaseObject1//doctorcomputer3.bmp",  0, 1, 1);
		createBaseObj(L"PEncyclopedia", L"Texture//Objects//BaseObject1//PEncyclopedia.bmp", 0, 1, 1);
		createBaseObj(L"pkballdesk", L"Texture//Objects//BaseObject1//pkballdesk.bmp",  0, 3, 1);

		createBaseObj(L"sign", L"Texture//Objects//BaseObject1//sign.bmp", 0, 1, 1);
		createBaseObj(L"sign2", L"Texture//Objects//BaseObject1//sign2.bmp", 0, 1, 1);
		createBaseObj(L"sink", L"Texture//Objects//BaseObject1//sink.bmp",  0, 2, 1);
		createBaseObj(L"SuperFamicom", L"Texture//Objects//BaseObject1//SuperFamicom.bmp",  0, 1, 1);
	}
	{//¾Æ·¡ 1Ä­Â¥¸® baseobject

		createBaseObj(L"fourtilebookshelf", L"Texture//Objects//BaseObject2//fourtilebookshelf.bmp",  1, 2, 1);
		createBaseObj(L"centercomputer", L"Texture//Objects//BaseObject2//centercomputer.bmp",  1, 1, 1);
		createBaseObj(L"deskoncomputer", L"Texture//Objects//BaseObject2//deskoncomputer.bmp",  1, 1, 1);
		createBaseObj(L"doctorcomputer1", L"Texture//Objects//BaseObject2//doctorcomputer1.bmp",  1, 1, 1);
		createBaseObj(L"doctorcomputer2", L"Texture//Objects//BaseObject2//doctorcomputer2.bmp", 1, 2, 1);
		createBaseObj(L"doctormachine", L"Texture//Objects//BaseObject2//doctormachine.bmp",  1, 2, 2);
		createBaseObj(L"Doubledeckershelf", L"Texture//Objects//BaseObject2//Doubledeckershelf.bmp",  1, 2, 1);
		createBaseObj(L"flowerpot", L"Texture//Objects//BaseObject2//flowerpot.bmp",  1, 1, 1);
		createBaseObj(L"greenbookshelf", L"Texture//Objects//BaseObject2//greenbookshelf.bmp",  1, 2, 1);
		createBaseObj(L"gymsing", L"Texture//Objects//BaseObject2//gymsing.bmp",  1, 1, 1);
		createBaseObj(L"mailbox", L"Texture//Objects//BaseObject2//mailbox.bmp",  1, 1, 1);
		createBaseObj(L"map", L"Texture//Objects//BaseObject2//map.bmp",  1, 2, 1);
		createBaseObj(L"memo1", L"Texture//Objects//BaseObject2//memo1.bmp", 1, 1, 1);
		createBaseObj(L"tv", L"Texture//Objects//BaseObject2//tv.bmp",  1, 1, 1);
		createBaseObj(L"wallmemo", L"Texture//Objects//BaseObject2//wallmemo.bmp", 1, 1, 1);

		//tree
		createBaseObj(L"tree", L"Texture//Objects//BaseObject2//tree.bmp", 1, 2,2);
		createBaseObj(L"tree2", L"Texture//Objects//BaseObject2//tree2.bmp", 1, 2, 1);

		//House
		createHouseObj(L"myhome", L"door", L"Texture//Objects//House//myhome.bmp", L"Texture//Objects//House//door.bmp", 6, 5, 4,1,7,Vec2(38*64,18*64));
		createHouseObj(L"doctorlaboratory", L"door2", L"Texture//Objects//House//doctorlaboratory.bmp", L"Texture//Objects//House//door2.bmp", 6,7, 4, 5, 7, Vec2(16 * 64, 42 * 64));
		createHouseObj(L"pokemoncenter", L"centerdoor", L"Texture//Objects//House//pokemoncenter.bmp", L"Texture//Objects//House//centerdoor.bmp", 6, 5, 4, 3, 7, Vec2(67 * 64, 18 * 64));
		createHouseObj(L"store", L"centerdoor", L"Texture//Objects//House//store.bmp", L"Texture//Objects//House//centerdoor.bmp", 5, 4, 3, 3, 5, Vec2(0 * 64, 0 * 64));
		createHouseObj(L"gym", L"gymdoor", L"Texture//Objects//House//gym.bmp", L"Texture//Objects//House//gymdoor.bmp",6, 6, 4, 5, 7, Vec2(41 * 64, 38 * 64));


		//CHANGPLACEOBJ
		createChangeplaceObj(L"homedownstairs", L"Texture//Objects//Changeplaceobj//homedownstairs.bmp", 1,2, 1,Vec2(0.0f,0.0f));
		createChangeplaceObj(L"homeupstairs", L"Texture//Objects//Changeplaceobj//homeupstairs.bmp", 1, 1, 1, Vec2(0.0f, 0.0f));


		//PokemonSpawnObj
		createpokemonspawnobj(L"pokemonspawn", L"Texture//Objects//pokemonspawnobj//pokemonspawn.bmp",0,1, 1);

		//JumpWall
		createjumpwallobj(L"ljumpwall", L"Texture//Objects//Jumpwall//ljumpwall.bmp", 0, 1, 1);
		createjumpwallobj(L"mjumpwall", L"Texture//Objects//Jumpwall//mjumpwall.bmp", 0, 1, 1);
		createjumpwallobj(L"rjumpwall", L"Texture//Objects//Jumpwall//rjumpwall.bmp", 0, 1, 1);


		CSkill* tackle = new CTackle();
		//pokemon
		createpokemon(L"Bulbasaur", L"Texture//Pokemon//Bulbasaur.bmp",
			HABCDS(45, 49, 49, 65, 65, 45), L"ÀÌ»óÇØ¾¾", POKEMON_TYPE::GRASS, POKEMON_TYPE::POISON, tackle->Clone());
		createpokemon(L"Ivysaur", L"Texture//Pokemon//Ivysaur.bmp", 
			HABCDS(60, 62, 63, 80, 80, 60), L"ÀÌ»óÇØÇ®", POKEMON_TYPE::GRASS, POKEMON_TYPE::POISON, tackle->Clone());
		createpokemon(L"Venusaur", L"Texture//Pokemon//Venusaur.bmp", 
			HABCDS(80, 82, 83, 100, 100, 80), L"ÀÌ»óÇØ²É", POKEMON_TYPE::GRASS, POKEMON_TYPE::POISON, tackle->Clone());
		createpokemon(L"Charmander", L"Texture//Pokemon//Charmander.bmp",
			HABCDS(39, 52, 43, 60, 50, 65), L"ÆÄÀÌ¸®", POKEMON_TYPE::FIRE, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Charmeleon", L"Texture//Pokemon//Charmeleon.bmp",
			HABCDS(58, 64, 58, 80, 65, 80), L"¸®ÀÚµå", POKEMON_TYPE::FIRE, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Charizard", L"Texture//Pokemon//Charizard.bmp", 
			HABCDS(78, 84, 78, 109, 85, 100), L"¸®ÀÚ¸ù", POKEMON_TYPE::FIRE, POKEMON_TYPE::FLYING, tackle->Clone());
		createpokemon(L"Squirtle", L"Texture//Pokemon//Squirtle.bmp", 
			HABCDS(44, 48, 65, 50, 64, 43), L"²¿ºÎ±â", POKEMON_TYPE::WATER, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Wartortle", L"Texture//Pokemon//Wartortle.bmp", 
			HABCDS(59, 63, 80, 65, 80, 58), L"¾î´ÏºÎ±â", POKEMON_TYPE::WATER, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Blastoise", L"Texture//Pokemon//Blastoise.bmp", 
			HABCDS(79, 83, 100, 85, 105,78), L"°ÅºÏ¿Õ", POKEMON_TYPE::WATER, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Pidgey", L"Texture//Pokemon//Pidgey.bmp", 
			HABCDS(40, 45, 40, 35, 35, 56), L"±¸±¸", POKEMON_TYPE::NORMAL, POKEMON_TYPE::FLYING, tackle->Clone());
		createpokemon(L"Pidgeotto", L"Texture//Pokemon//Pidgeotto.bmp",
			HABCDS(63,60, 55, 50, 50, 71), L"ÇÇÁÔ", POKEMON_TYPE::NORMAL, POKEMON_TYPE::FLYING, tackle->Clone());
		createpokemon(L"Pidgeot", L"Texture//Pokemon//Pidgeot.bmp",  
			HABCDS(83, 80, 75, 70, 70, 101), L"ÇÇÁÔÅõ", POKEMON_TYPE::NORMAL, POKEMON_TYPE::FLYING, tackle->Clone());
		createpokemon(L"Rattata", L"Texture//Pokemon//Rattata.bmp",  
			HABCDS(30, 56, 35, 25, 35, 72), L"²¿·¿", POKEMON_TYPE::NORMAL, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Pikachu", L"Texture//Pokemon//Pikachu.bmp",  
			HABCDS(45, 80, 50, 75, 60, 120), L"ÇÇÄ«Ãò", POKEMON_TYPE::ELECTRIC, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Alakazam", L"Texture//Pokemon//Alakazam.bmp", 
			HABCDS(55, 50, 45, 135, 95, 120), L"ÈÄµò", POKEMON_TYPE::PSYCHIC, POKEMON_TYPE::NONE, tackle->Clone());
		createpokemon(L"Arcanine", L"Texture//Pokemon//Arcanine.bmp", 
			HABCDS(90, 110, 80, 100, 80, 95), L"À©µð", POKEMON_TYPE::FIRE, POKEMON_TYPE::NONE, tackle->Clone());
		delete tackle;
	}
}

void CObjectMgr::createBaseObj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}
	
		CObj* Object = new CBaseObject;
		CBaseObject* BaseObject = dynamic_cast<CBaseObject*>(Object);
		BaseObject->SetTexture(pTex);
		CCollider* pCollider = new CCollider;
		if(_strKey==L"tree" || _strKey==L"doctormachine")
		{
			pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), 64.f + (float)(SetColliderPos * 64)));
		}
		else
		{
			pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), 32.f + (float)(SetColliderPos * 64))); 
		}
		pCollider->SetScale(Vec2((float)(64 * _ColliderX), (float)(64 * _ColliderY)));
		Object->AddCollider(pCollider);
		m_mapObj.insert(make_pair(_strKey, Object));

	
}

void CObjectMgr::createHouseObj(const wstring& _strKey, const wstring& _strdoorKey, const wstring& _strRelativePath, const wstring& _strdoorRelativePath,
	int SetColliderPos, int _ColliderX, int _ColliderY,int _DoorX,int _DoorY,Vec2 _TelpoPos)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}

	CTexture* pdoorTex = CResMgr::GetInst()->FindTexture(_strdoorKey);
	if (nullptr == pdoorTex)
	{
		pdoorTex = CResMgr::GetInst()->LoadTexture(_strdoorKey, _strdoorRelativePath);
	}

	CObj* Object = new CHouse;
	CDoor* Door = new CDoor;
	CHouse* HouseObject = dynamic_cast<CHouse*>(Object);
	HouseObject->SetTexture(pTex);
	Door->SetTexture(pdoorTex);
	Door->SetTelpoPos(_TelpoPos);
	Door->init();
	HouseObject->SetDoor(Door);
	HouseObject->SetDoorPos(Vec2(32.f+(float)(32 * _DoorX),32.f+ (float)(32 * _DoorY)));
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), (float)(SetColliderPos * 32)));
	pCollider->SetScale(Vec2((float)(64 * _ColliderX), (float)(64 * _ColliderY)));
	Object->AddCollider(pCollider);
	m_mapObj.insert(make_pair(_strKey, Object));
}

void CObjectMgr::createChangeplaceObj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY,Vec2 _ChangePos)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}

	CObj* Object = new CChangeplaceobj;
	CChangeplaceobj* ChangeObject = dynamic_cast<CChangeplaceobj*>(Object);
	ChangeObject->SetTexture(pTex);
	ChangeObject->SetChangePos(_ChangePos);
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), 32.f + (float)(SetColliderPos * 64)));
	pCollider->SetScale(Vec2((float)(64 * _ColliderX), (float)(64 * _ColliderY)));
	Object->AddCollider(pCollider);
	m_mapObj.insert(make_pair(_strKey, Object));
}

void CObjectMgr::createpokemonspawnobj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}

	CObj* Object = new CPokemonSpawnObj;
	CPokemonSpawnObj*PokemonSpawnObject = dynamic_cast<CPokemonSpawnObj*>(Object);
	PokemonSpawnObject->SetTexture(pTex);
	CCollider* pCollider = new CCollider;
	
	pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), 32.f + (float)(SetColliderPos * 64)));
	pCollider->SetScale(Vec2((float)(32 * _ColliderX), (float)(32 * _ColliderY)));
	Object->AddCollider(pCollider);
	m_mapObj.insert(make_pair(_strKey, Object));
}

void CObjectMgr::createjumpwallobj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}

	CObj* Object = new CJumpwallObj;
	CJumpwallObj* JumpwallObject = dynamic_cast<CJumpwallObj*>(Object);
	JumpwallObject->SetTexture(pTex);
	CCollider* pCollider = new CCollider;

	pCollider->SetOffsetPos(Vec2(32.f * (float)(_ColliderX), 32.f + (float)(SetColliderPos * 64)));
	pCollider->SetScale(Vec2((float)(64 * _ColliderX), (float)(64 * _ColliderY)));
	Object->AddCollider(pCollider);
	m_mapObj.insert(make_pair(_strKey, Object));
}

void CObjectMgr::createpokemon(const wstring& _strKey, const wstring& _strRelativePath, HABCDS _habcds, const wstring& _name, POKEMON_TYPE _type, POKEMON_TYPE _type2,
	CSkill* _skill1, CSkill* _skill2, CSkill* _skill3, CSkill* _skill4)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(_strKey);
	if (nullptr == pTex)
	{
		pTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);
	}
	CPokemon* pokemon = new CPokemon;
	pokemon->SetTex1(pTex);
	pokemon->SetLv(1);
	pokemon->SetPos(Vec2(588, 88));
	pokemon->SetHABCDS(_habcds);
	pokemon->SetName(_name);
	pokemon->SetType(_type, _type2);
	pokemon->init();
	pokemon->SetSkill(_skill1, _skill2, _skill3, _skill4);
	
	
	m_mapPokemon.insert(make_pair(_strKey, pokemon));
}

CObj* CObjectMgr::FindObj(const wstring& _strKey)
{
	map<wstring, CObj*>::iterator iter = m_mapObj.find(_strKey);

	if (iter == m_mapObj.end())
		return nullptr;

	return iter->second->Clone();
}

CPokemon* CObjectMgr::FindPokemon(const wstring& _strKey)
{
	map<wstring, CPokemon*>::iterator iter = m_mapPokemon.find(_strKey);

	if (iter == m_mapPokemon.end())
		return nullptr;

	return iter->second->Clone();
}

CObj* CObjectMgr::objectspawn(OBJECTSNAME _namenumber)
{
	switch (_namenumber)
	{
	case OBJECTSNAME::closet:
		return FindObj(L"closet");
		break;
	case OBJECTSNAME::desk:
		return FindObj(L"desk");
		break;
	case OBJECTSNAME::doctorcomputer3:
		return FindObj(L"doctorcomputer3");
		break;
	case OBJECTSNAME::PEncyclopedia:
		return FindObj(L"PEncyclopedia");
		break;
	case OBJECTSNAME::pkballdesk:
		return FindObj(L"pkballdesk");
		break;
	case OBJECTSNAME::pokeball:
		return FindObj(L"pokeball");
		break;
	case OBJECTSNAME::sign:
		return FindObj(L"sign");
		break;
	case OBJECTSNAME::sign2:
		return FindObj(L"sign2");
		break;
	case OBJECTSNAME::sink:
		return FindObj(L"sink");
		break;
	case OBJECTSNAME::SuperFamicom:
		return FindObj(L"SuperFamicom");
		break;
	case OBJECTSNAME::fourtilebookshelf:
		return FindObj(L"fourtilebookshelf");
		break;
	case OBJECTSNAME::deskoncomputer:
		return FindObj(L"deskoncomputer");
		break;
	case OBJECTSNAME::centercomputer:
		return FindObj(L"centercomputer");
		break;
	case OBJECTSNAME::doctorcomputer1:
		return FindObj(L"doctorcomputer1");
		break;
	case OBJECTSNAME::wallmemo:
		return FindObj(L"wallmemo");
		break;
	case OBJECTSNAME::tv:
		return FindObj(L"tv");
		break;
	case OBJECTSNAME::memo1:
		return FindObj(L"memo1");
		break;
	case OBJECTSNAME::map:
		return FindObj(L"map");
		break;
	case OBJECTSNAME::mailbox:
		return FindObj(L"mailbox");
		break;
	case OBJECTSNAME::gymsing:
		return FindObj(L"gymsing");
		break;
	case OBJECTSNAME::greenbookshelf:
		return FindObj(L"greenbookshelf");
		break;
	case OBJECTSNAME::flowerpot:
		return FindObj(L"flowerpot");
		break;
	case OBJECTSNAME::Doubledeckershelf:
		return FindObj(L"Doubledeckershelf");
		break;
	case OBJECTSNAME::doctormachine:
		return FindObj(L"doctormachine");
		break;
	case OBJECTSNAME::doctorcomputer2:
		return FindObj(L"doctorcomputer2");
		break;
	case OBJECTSNAME::wallmountedtv:
		return FindObj(L"wallmountedtv");
		break;
	case OBJECTSNAME::tree:
		return FindObj(L"tree");
		break;
	case OBJECTSNAME::myhome:
		return FindObj(L"myhome");
		break;
	case OBJECTSNAME::doctorlaboratory:
		return FindObj(L"doctorlaboratory");
		break;
	case OBJECTSNAME::gym:
		return FindObj(L"gym");
		break;
	case OBJECTSNAME::pokemoncenter:
		return FindObj(L"pokemoncenter");
		break;
	case OBJECTSNAME::store:
		return FindObj(L"store");
		break;
	case OBJECTSNAME::homeupstairs:
		return FindObj(L"homeupstairs");
		break;
	case OBJECTSNAME::homedownstairs:
		return FindObj(L"homedownstairs");
		break;
	case OBJECTSNAME::pokemonspawn:
		return FindObj(L"pokemonspawn");
		break;
	case OBJECTSNAME::ljumpwall:
		return FindObj(L"ljumpwall");
		break;
	case OBJECTSNAME::mjumpwall:
		return FindObj(L"mjumpwall");
		break;
	case OBJECTSNAME::rjumpwall:
		return FindObj(L"rjumpwall");
	case OBJECTSNAME::tree2:
		return FindObj(L"tree2");
		break;
	}
	return nullptr;
}

CPokemon* CObjectMgr::pokemonspawn(POKEMONNAME _namenumber)
{
	switch (_namenumber)
	{
	case POKEMONNAME::Bulbasaur:
		return FindPokemon(L"Bulbasaur");
		break;
	case POKEMONNAME::Ivysaur:
		return FindPokemon(L"Ivysaur");
		break;
	case POKEMONNAME::Venusaur:
		return FindPokemon(L"Venusaur");
		break;
	case POKEMONNAME::Charmander:
		return FindPokemon(L"Charmander");
		break;
	case POKEMONNAME::Charmeleon:
		return FindPokemon(L"Charmeleon");
		break;
	case POKEMONNAME::Charizard:
		return FindPokemon(L"Charizard");
		break;
	case POKEMONNAME::Squirtle:
		return FindPokemon(L"Squirtle");
		break;
	case POKEMONNAME::Wartortle:
		return FindPokemon(L"Wartortle");
		break;
	case POKEMONNAME::Blastoise:
		return FindPokemon(L"Blastoise");
		break;
	case POKEMONNAME::Pidgey:
		return FindPokemon(L"Pidgey");
		break;
	case POKEMONNAME::Pidgeotto:
		return FindPokemon(L"Pidgeotto");
		break;
	case POKEMONNAME::Pidgeot:
		return FindPokemon(L"Pidgeot");
		break;
	case POKEMONNAME::Rattata:
		return FindPokemon(L"Rattata");
		break;
	case POKEMONNAME::Pikachu:
		return FindPokemon(L"Pikachu");
		break;
	case POKEMONNAME::Alakazam:
		return FindPokemon(L"Alakazam");
		break;
	case POKEMONNAME::Arcanine:
		return FindPokemon(L"Arcanine");
		break;
	}
	return nullptr;
}
