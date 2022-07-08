#pragma once
#include "CUI.h"

class CPokemon;
class CBattleChoice :
    public CUI
{
public:
    CBattleChoice();
    ~CBattleChoice();

private:
    CPokemon* m_pPokemon;
    CPokemon* m_oPokemon;



    CTexture* m_Arrow;

    CTexture* m_skillselect;
    int m_select;
    int m_select2;
    bool m_skillselecton;

    

    bool m_showon;
    bool m_showon2;

public:
    void SetPokemon(CPokemon* _Pokemon, CPokemon* _oPokemon) { m_pPokemon = _Pokemon; m_oPokemon = _oPokemon; }

    void SetShow(bool _show) { m_showon = _show; }
    void SetShow2(bool _show) { m_showon2 = _show; }

    void setskillselecton(bool _on) {  m_skillselecton = _on; }
public:
    virtual void render(HDC _dc);
    virtual void update();


    void Fight();
    void Bag();
    void PokemonChange();
    void Run();
};

