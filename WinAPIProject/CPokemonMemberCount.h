#pragma once
#include "CUI.h"
class CPokemon;
class CPokemonMemberCount :
    public CUI
{
public:
    CPokemonMemberCount();
    ~CPokemonMemberCount();

private:
    vector<CPokemon*> m_pokemonmember;


    CTexture* m_pTex;
    CTexture* m_pTex2;


    bool     m_Player;
public:
    virtual void render(HDC _dc);
    virtual void update();

public:
    void SetPokemonMember(vector<CPokemon*>& _pokemonmember) { m_pokemonmember = _pokemonmember; };
    void SetPlayerbool(bool _Player) { m_Player = _Player; }
};

