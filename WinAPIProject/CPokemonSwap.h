#pragma once
#include "CUI.h"

class CPokemon;
class CTexture;
class CSwapmain;
class CSwapserve;
class CSwapChange;
class CPokemonSwap :
    public CUI
{

private:
	int       m_focusnum;
	int		  m_focusnumpre;
	
	
	CTexture* m_sBackGround;
	CTexture* m_pCancel;
	
	vector<CUI*> m_SwapMember;
	

	vector<CPokemon*> m_PokemonMember;

	CSwapChange* m_PokemonChange;


	bool	m_TextBarOn;
	
public:

	virtual void update();


	virtual void render(HDC _dc);
public:
	CPokemonSwap();
	~CPokemonSwap();


public:
	void init();
	void Enter();

public:
	void SetPokemonMember(vector<CPokemon*>& _pokemonmember) { m_PokemonMember = _pokemonmember; }
};

