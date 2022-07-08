#pragma once
#include "CUI.h"

class CPokemon;
class COtherBattleState_Bar :
    public CUI
{
public:
    COtherBattleState_Bar();
    ~COtherBattleState_Bar();

private:
    CPokemon* m_pPokemon;
  

    CTexture* m_pProgressBar;
    CTexture* m_pProgressBar2;
    CTexture* m_pProgressBar3;


    int		m_starani_y1;
    int		m_starani_y2;
   
    int     hpbar;
    int     hpbar2;
public:
    void SetPokemon(CPokemon* _Pokemon);

public:
    virtual void render(HDC _dc);
    virtual void update();


};
