#pragma once
#include "CObj.h"
class CDocter :
    public CObj
{

public:
    CDocter();
    ~CDocter();
    CDocter(const CDocter& _origin);

private:
    CTexture* m_pTex;

    int  m_vecter;

    bool m_on;
public:
    virtual CDocter* Clone() { return new CDocter(*this); }

    virtual void update();
    virtual void render(HDC _dc);
    virtual void init();
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
public:
    void SetPokeball(int _i);
    bool GetOn() { return m_on; }
    void SetOn(bool _on) { m_on = _on; }
};

