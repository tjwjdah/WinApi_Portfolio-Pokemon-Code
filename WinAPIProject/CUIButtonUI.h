#pragma once
#include "CUI.h"


class CTilePanelUI;
class CUIButtonUI :
    public CUI
{
public:
    CUIButtonUI();
    ~CUIButtonUI();
    
private:
    CTilePanelUI* m_ConnectPanel;
    UI_TYPE m_changeUiType;

public:
    virtual void MouseLBTNDown(Vec2 _vMousePos);


public:
    void SetConnectPanel(CUI* PanelUI);
    void SetchangeUiType(UI_TYPE Type) { m_changeUiType = Type;}


};

