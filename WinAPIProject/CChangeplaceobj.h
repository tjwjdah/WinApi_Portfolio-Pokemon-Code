#pragma once
#include "CObj.h"
class CChangeplaceobj :
    public CObj
{
public:
    CChangeplaceobj();
    ~CChangeplaceobj();


    CChangeplaceobj(const CChangeplaceobj& _origin);
private:
    CTexture* m_pTex;
    Vec2 m_ChangePos;
public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };

    void SetChangePos(Vec2 _Pos) {m_ChangePos = _Pos;}
   
public:
    virtual void update();
    virtual void render(HDC _dc);


    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual CChangeplaceobj* Clone() { return new CChangeplaceobj(*this); }
};

