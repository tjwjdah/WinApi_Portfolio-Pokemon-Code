#pragma once
#include "CUI.h"
class CSwapChange :
    public CUI
{
public:
    CSwapChange();
    ~CSwapChange();

private:

    CTexture* m_pTex;
    CTexture* m_pArrowTex;
    int       ArrowPos;
public:
    virtual void render(HDC _dc);
    virtual void update();


public:
    int GetArrowPos() {
        return ArrowPos;
    }
};

