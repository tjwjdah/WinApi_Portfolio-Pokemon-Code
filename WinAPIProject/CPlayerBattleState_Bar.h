#pragma once
#include "CUI.h"

class CPokemon;
class CPlayerBattleState_Bar :
    public CUI
{
public:
    CPlayerBattleState_Bar();
    ~CPlayerBattleState_Bar();

private:
    CPokemon* m_pPokemon;
   

 
    CTexture* m_pProgressBar_exp;
    CTexture* m_pProgressBar;
    CTexture* m_pProgressBar2;
    CTexture* m_pProgressBar3;


    int		m_starani_y1;
    int		m_starani_y2;
    int     a;
    int     hpbar;
    int     hpbar2;
    int     expbar;
    int     expbar2;
public:
    void SetPokemon(CPokemon* _Pokemon);

public:
    virtual void render(HDC _dc);
    virtual void update();

    
};

