#pragma once
#include "CPanelUI.h"
class CTilePanelUI :
    public CPanelUI
{
public:
    CTilePanelUI();
    ~CTilePanelUI();

private:
    int PageNum;
    int PageMax;
    UI_TYPE m_ShowUIType;

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

    void ChangeShowUIType(UI_TYPE UIType);

public:
    CTilePanelUI* Clone() { return new CTilePanelUI(*this); }
};

