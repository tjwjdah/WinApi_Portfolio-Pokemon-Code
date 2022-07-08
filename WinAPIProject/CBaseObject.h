#pragma once
#include "CObj.h"

class  CTexture;
class CBaseObject :
    public CObj
{
public:
    CBaseObject();
    ~CBaseObject();


    CBaseObject(const CBaseObject& _origin);
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
    virtual CBaseObject* Clone() { return new CBaseObject(*this); }
};

