#pragma once
#include "CObj.h"
class CJumpwallObj :
    public CObj
{
public:

    CJumpwallObj();
    ~CJumpwallObj();


    CJumpwallObj(const CJumpwallObj& _origin);
private:
    CTexture* m_pTex;
public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual CJumpwallObj* Clone() { return new CJumpwallObj(*this); }

};

