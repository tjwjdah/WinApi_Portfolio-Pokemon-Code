#pragma once
#include "CUI.h"
class C2Tilebutton :
    public CUI
{
public:
    C2Tilebutton();
    ~C2Tilebutton();
private:
    bool m_On;
public:
    virtual void render(HDC _dc);
public:

public:
    virtual void MouseLBTNDown(Vec2 _vMousePos);


};

