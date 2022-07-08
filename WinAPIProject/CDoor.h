#pragma once
#include "CObj.h"

class CTexture;
class CAnimator;
class CDoor :
    public CObj
{


public:
    CDoor();
    ~CDoor();

    CDoor(const CDoor& _origin);
private:
    CTexture* m_pTex;
    Vec2      m_TelpoPos;
public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };
    void SetTelpoPos(Vec2 _Pos) { m_TelpoPos = _Pos; }
    void init();

public:
    virtual void update();
   
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual CDoor* Clone() { return new CDoor(*this); }
    
};

