#pragma once
#include "CUI.h"
class CSaveUI :
    public CUI
{
public:
    CSaveUI();
    ~CSaveUI();
public:
    virtual void MouseLBTNDown(Vec2 _vMousePos);
};

