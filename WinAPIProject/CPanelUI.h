#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
public:
    CPanelUI();
    ~CPanelUI();

private:
    Vec2    m_vStartPos;

public:
    virtual void finalupdate();
    virtual void render(HDC _dc);

public:
    virtual void MouseOn(Vec2 _vMousePos);
    virtual void MouseLBTNDown(Vec2 _vMousePos);
    virtual void MouseLBTNUp(Vec2 _vMousePos);
    virtual void MouseLBTNClicked(Vec2 _vMousePos);

public:
    virtual void PageNumUp();
    virtual void PageNumDawn();

public:
    CPanelUI* Clone() { return new CPanelUI(*this); }
};

