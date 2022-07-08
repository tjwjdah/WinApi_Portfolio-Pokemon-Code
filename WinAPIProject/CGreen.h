#pragma once
#include "CObj.h"
class CTexture;
class CPokemon;
class CGreen :
    public CObj
{
public:
    CGreen();
    ~CGreen();

public:
private:
    CTexture* m_pTex;
    CTexture* m_BattleTex;
    vector<CPokemon*> m_PokemonMember;
    wstring   m_script;
    wstring   m_name;

    bool      m_on;
public:

    virtual void init();
    virtual void update();
    virtual void render(HDC _dc);
    virtual CGreen* Clone() { return new CGreen(*this); }
   
public:
    wstring Getscript() { return m_script; }
    wstring GetName() { return m_name; }

    CTexture* GetBattleTex() { return m_BattleTex; }
    vector<CPokemon*>& GetPokemonMember() { return m_PokemonMember; }

    bool  GetOn() { return m_on; }
    void  SetOn(bool _on) { m_on = _on; }
};

