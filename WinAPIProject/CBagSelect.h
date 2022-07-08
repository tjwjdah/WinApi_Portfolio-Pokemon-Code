#pragma once
#include "CUI.h"
class CBagSelect :
    public CUI
{
public:
    CBagSelect();
    ~CBagSelect();

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

