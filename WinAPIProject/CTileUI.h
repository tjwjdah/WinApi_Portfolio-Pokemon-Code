#pragma once
#include "CUI.h"


class CTileUI :
    public CUI
{
public:
    CTileUI();
    CTileUI(int n);
    ~CTileUI();

private:
    int         m_iImgIdx;

public:
    virtual void update();
    virtual void lateupdate();
    virtual void finalupdate();

    virtual void render(HDC _dc);


public:
    virtual void MouseOn(Vec2 _vMousePos);
    virtual void MouseLBTNDown(Vec2 _vMousePos);
    virtual void MouseLBTNUp(Vec2 _vMousePos);
    virtual void MouseLBTNClicked(Vec2 _vMousePos);

    void SetTileNum(int _Num) { m_iImgIdx = _Num; }
    int GetiImgIdx() { return m_iImgIdx; }

public:
    virtual CTileUI* Clone() { return new CTileUI(*this); }
};
