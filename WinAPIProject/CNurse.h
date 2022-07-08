#pragma once
#include "CObj.h"
class CTexture;
class CNurse :
    public CObj
{
public:
    CNurse();
    ~CNurse();
    CNurse(const CNurse& _origin);

private:
    CTexture* m_pTex;

    int m_ShowPokeball;
    bool m_on;
public:
    virtual CNurse* Clone() { return new CNurse(*this); }

    virtual void update();
    virtual void render(HDC _dc);
    virtual void init();
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    void SetPokeball(int _i);
    bool GetOn() { return m_on; }
    void SetOn(bool _on) { m_on = _on; }
};

