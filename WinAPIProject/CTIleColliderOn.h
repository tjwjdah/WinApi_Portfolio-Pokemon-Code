#pragma once
#include "CUI.h"
class CTIleColliderOn :
    public CUI
{
public:

    CTIleColliderOn();
    ~CTIleColliderOn();
private:
    bool m_On;
public:
    virtual void render(HDC _dc);
public:

public:
    virtual void MouseLBTNDown(Vec2 _vMousePos);

};

