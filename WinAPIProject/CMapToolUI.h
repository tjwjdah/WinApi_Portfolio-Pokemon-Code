#pragma once
#include "CPanelUI.h"
class CMapToolUI :
    public CPanelUI
{
public:
    CMapToolUI();
    ~CMapToolUI();


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
    CMapToolUI* Clone() { return new CMapToolUI(*this); }
};

