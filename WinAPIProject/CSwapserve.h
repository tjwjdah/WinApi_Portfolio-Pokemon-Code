#pragma once
#include "CUI.h"

class CPokemon;
class CPokemonanim;
class CTexture;
class CSwapserve :
    public CUI
{
public:
    CSwapserve();
    ~CSwapserve();

private:
    CPokemon* m_Pokemon;
    bool             m_focuson;
    CPokemonanim* m_PokemonAnim;


    CTexture* m_pProgressBar;
    CTexture* m_pProgressBar2;
    CTexture* m_pProgressBar3;

public:
    virtual void render(HDC _dc);
    virtual void update();

public:
    void SetPokemonAnimPos(Vec2 _Pos);
    void SetFocus(bool _focus) { m_focuson = _focus; }
    void SetPokemon(CPokemon* _Pokemon);
};

