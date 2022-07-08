#pragma once




class CObj;
class CPokemon;
class CSkill;
class CObjectMgr
{
	SINGLE(CObjectMgr);

private:
	map<wstring, CObj*>	m_mapObj;
	map<wstring, CPokemon*>	m_mapPokemon;

public:
	void init();
	
	void createBaseObj(const wstring& _strKey, const wstring& _strRelativePath,int SetColliderPos, int _ColliderX, int _ColliderY);
	
	void createHouseObj(const wstring& _strKey, const wstring& _strdoorKey, const wstring& _strRelativePath, const wstring& _strdoorRelativePath,
		int SetColliderPos, int _ColliderX, int _ColliderY, int _DoorX, int _DoorY, Vec2 _TelpoPos);
	
	
	void createChangeplaceObj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY, Vec2 _ChangePos);

	void createpokemonspawnobj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY);

	void createjumpwallobj(const wstring& _strKey, const wstring& _strRelativePath, int SetColliderPos, int _ColliderX, int _ColliderY);


	void createpokemon(const wstring& _strKey, const wstring& _strRelativePath, HABCDS _habcds, const wstring& _name, POKEMON_TYPE _type, POKEMON_TYPE _type2,
		CSkill* _skill1 = nullptr, CSkill* _skill2 = nullptr, CSkill* _skill3 = nullptr, CSkill* _skill4 = nullptr);

	CObj* FindObj(const wstring& _strKey);
	CPokemon* FindPokemon(const wstring& _strKey);
	CObj* objectspawn(OBJECTSNAME _namenumber);
	CPokemon* pokemonspawn(POKEMONNAME _namenumber);
};

