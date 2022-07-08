#pragma once
#include "CObj.h"

class CTexture;
class CPokemon;
class CBag;
enum class PLAYER_STATE
{
	IDLE,
	MOVE,	
	JUMP,
	ATTACK,
	DEAD,
};


class CPlayer :
	public CObj
{
private:
	CTexture*		m_pTex;	
	UINT			m_iHP;

	DIR				m_eDir;
	
	PLAYER_STATE	m_eState;

	DIR				m_ePrevDir;
	PLAYER_STATE	m_ePrevState;


	Vec2			m_ePrePos;
	

	float			m_fMoveSpeed;


	bool			m_pMovebool;

	bool			m_pbattleon;

	bool			m_pokemonspawnon;


	float			m_pMoveTime;
	float			m_pMoveTime2;

	vector<CPokemon*> m_PokemonMember;

	CBag*			m_pBag;
public:
	virtual void init();
	virtual void update();	
	virtual void render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	
	
	virtual CPlayer* Clone() { return new CPlayer(*this); }


private:
	void CheckState();
	void CheckAnimation();
	void Move();


public:
	CPlayer();
	~CPlayer();

public:
	void Setbattle(bool _battleon) { m_pbattleon = _battleon; }
	void SetPokemonMember(vector<CPokemon*>& _PokemonMember) { m_PokemonMember = _PokemonMember; }
	vector<CPokemon*>& GetPokemonMember() { return m_PokemonMember; }
	CBag* GetBag() { return m_pBag; }

	void SetPlayerPos(Vec2 _Pos) { SetPos(_Pos); m_ePrePos = _Pos; }
};

