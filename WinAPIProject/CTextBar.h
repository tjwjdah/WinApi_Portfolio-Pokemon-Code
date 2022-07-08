#pragma once
#include "CUI.h"


class CTextBar :
    public CUI
{

public:
    CTextBar();
    ~CTextBar();
private:
    wstring m_text;
    wstring m_showtext;
    size_t  m_textn;

    int m_startText;
    
    bool    m_battleOn;

    bool    m_Textend;
public:
    virtual void render(HDC _dc);
    virtual void update();
    void pushtext(const wstring& _text);
    void pushnexttext(const wstring& _text);
    void Set_battleOn(bool _on) { m_battleOn = _on; }
    bool Textend();
};

