#pragma once
#include "CScene.h"

class CAnimator;
class CPokemon;
class CTextBar;
class CSkill;
class CBattleChoice;
class COtherBattleState_Bar;
class CPokemonSwap;
class CPlayerBattleState_Bar;
class CStartmonterball;
class CPlayer;
class CBag;
class CBattleScene :
    public CScene
{

private:

	CTexture* m_sBackGround;
	CTexture* m_startanimation;
	CTexture* m_startanimation2;
	CTexture* m_playerplace;
	CTexture* m_otherplace;
	CTexture* m_pbattleplayer;



	

	list<tEvent> m_timeEventplay;
	list<CSkill*> m_timebattleplay;

	

	bool	m_noinit;


	int		m_starani_y1;
	int		m_starani_y2;
	int     m_starani_y3;
	int		m_starani_y4;
	int     m_battepage;

	float     m_endtime1;
	float     m_endtime2;
	float     m_skilltime;

	float     m_ChangePokemonTime;
	bool    m_ChangePokemonOn;
	
	CPlayer* m_Player;
	CBag*	m_Player_Bag;
	vector<CPokemon*> m_PokemonMember;
	CPokemon* p_opponentpokemon;

	CBattleChoice*			m_battlechoice;
	COtherBattleState_Bar*	m_OtherBattleStatebar;
	CPlayerBattleState_Bar* m_PlayerBattleStateber;
	CPokemonSwap*			m_Swap;
	CStartmonterball* m_ThrowMonterball;
	CTextBar* m_BattleTextbar;

public:
	virtual void update();

	virtual void Enter();
	virtual void Exit();

	virtual void render(HDC _dc);
	virtual void init();

public:
	CBattleScene();
	~CBattleScene();

public:
	void timeEvenadd(CObj* _pNewObj, Vec2 _vPos, OBJ_TYPE _eType, float _dtime = 0.f);
	void timeEvenadd(CObj* _pDeleteObj, float _dtime = 0.f);
	void timeEvenadd(SCENE_TYPE _eNextScene, float _dtime = 0.f);

	void timeskillpush(CSkill* _skill);
	


	void SetPokemon(vector<CPokemon*>& _pokemonmember, CPokemon* _oPokemon) { m_PokemonMember = _pokemonmember; p_opponentpokemon = _oPokemon; }
	void SetPokemonMember(vector<CPokemon*>& _pokemonmember) { m_PokemonMember = _pokemonmember; }
	CTextBar* GetTextBar() { return m_BattleTextbar; }
	CBattleChoice* Getbattlechoice() { return m_battlechoice; }

	CPokemon* GetoPokemon() { return p_opponentpokemon; }
	CPokemonSwap* GetPokemonSwap() { return m_Swap; }

	vector<CPokemon*>& GetPokemonMember() { return m_PokemonMember; }
	CStartmonterball* GetStartmonterball() { return m_ThrowMonterball; }
	void SetPlayer(CPlayer* _player);
	CPlayer* GetPlayer() { return m_Player; }
	CBag* GetPlayerBag() { return m_Player_Bag; }
public:
	void battepage_event(int _page);

	
	void UIOnOff(bool _onoff);
	void PokemonChange();

};

