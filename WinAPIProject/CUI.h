#pragma once

#include "CObj.h"

class CTexture;

class CUI :
    public CObj
{
private:
    CUI*            m_pParent;
    vector<CUI*>    m_vecChildUI;

    Vec2            m_vFinalPos;

    CTexture*       m_pTex;     

    bool            m_bMouseOn;
    bool            m_bLBTNDown;
    UI_TYPE         m_UType;
    bool            m_Use;

public:
    virtual void update();
    virtual void lateupdate();
    virtual void finalupdate();

    virtual void render(HDC _dc);

public:
    const vector<CUI*>& GetChild() { return m_vecChildUI; }
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CTexture* GetTex() { return m_pTex; }
    void AddChildUI(CUI* _pChildUI);
    CUI* GetParent() { return m_pParent; }
    void SetUse(bool _Use) { m_Use = _Use; }
    bool GetUse() { return m_Use; }
    void SetUIType(UI_TYPE _Type) { m_UType = _Type; }
    UI_TYPE GetUIType() { return m_UType; }




public:
    virtual void MouseOn(Vec2 _vMousePos);
    virtual void MouseLBTNDown(Vec2 _vMousePos);
    virtual void MouseLBTNUp(Vec2 _vMousePos);
    virtual void MouseLBTNClicked(Vec2 _vMousePos);

public:
    virtual bool IsMouseOn() {return m_bMouseOn; }
    bool IsLBTNDown() { return m_bLBTNDown; }

public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };

private:
    void MonseOnCheck();

public:
    virtual CUI* Clone() { return new CUI(*this); }

public:
    CUI();
    ~CUI();

protected:
    CUI(const CUI& _origin);

    friend class CUIMgr;
};

