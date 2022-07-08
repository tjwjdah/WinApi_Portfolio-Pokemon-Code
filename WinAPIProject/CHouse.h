#pragma once
#include "CObj.h"


class  CTexture;
class  CDoor;
class CHouse :
    public CObj
{
public:
    CHouse();
    ~CHouse();

    CHouse(const CHouse& _origin);
private:
    CTexture* m_pTex;
    CDoor*    m_pDoor;
    Vec2      m_pDoorPos;
public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };
   
    void SetDoor(CDoor* _Door);
    void SetDoorPos(Vec2 _pos);

    CDoor* GetDoor() { return m_pDoor; }
public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual CHouse* Clone() { return new CHouse(*this); }
};

