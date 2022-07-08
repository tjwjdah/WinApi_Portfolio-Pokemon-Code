#pragma once
#include "CUI.h"
class CLoadUI :
    public CUI
{
public:
    CLoadUI();
    ~CLoadUI();

public:
    virtual void MouseLBTNDown(Vec2 _vMousePos);
};

