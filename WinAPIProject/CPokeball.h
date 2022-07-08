#pragma once
#include "CObj.h"
class CTexture;
class CPokemon;
class CPokeball :
    public CObj
{

public:
    CPokeball();
    ~CPokeball();
    CPokeball(const CPokeball& _origin);

private:
    CTexture* m_pTex;

    CTexture* m_pTex2;
    CTexture* m_pTex3;
    CTexture* m_pTex4;
    CTexture* m_pTex5;

    CPokemon* m_Pokemon;

    bool      m_Yes;

    bool      m_on;
    
public:
    virtual CPokeball* Clone() { return new CPokeball(*this); }

    virtual void update();
    virtual void render(HDC _dc);
    virtual void init();
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:

    void SetPokeTexture(CTexture* _Text) { m_pTex3 = _Text; }
    void SetOn(bool _on) { m_on = _on; }
    void SetPokemon(CPokemon* _pokemon) { m_Pokemon = _pokemon; }
    void SetYes(bool _on) { m_Yes = _on; }
    CPokemon* GetPokemon() { return m_Pokemon; }
    bool GetYes() { return m_Yes; }
    bool GetOn() { return m_on; }
};

