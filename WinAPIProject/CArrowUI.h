#pragma once
#include "CUI.h"
class CArrowUI :
    public CUI
{
public:
    CArrowUI();
    CArrowUI(bool _RaL);

    ~CArrowUI();
private:
    bool RaL;
public:
    virtual void render(HDC _dc);



public:

    virtual void MouseLBTNDown(Vec2 _vMousePos);

    virtual CArrowUI* Clone() { return new CArrowUI(*this); }
};

