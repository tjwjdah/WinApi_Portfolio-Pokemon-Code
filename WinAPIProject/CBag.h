#pragma once
#include "CUI.h"


class CTexture;
class CItem;
class CBagSelect;
class CBag :
    public CUI
{
public:
    CBag();
    ~CBag();

public:
    CTexture* m_pTex;
    CTexture* m_pTexPre;
    CTexture* m_bagarrow;
    vector<CItem*> m_itemlist;

    CBagSelect* m_pSelect;

    int      m_SetItemNum;


    bool     m_on;

public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    void init();
    void Enter();
    void itemadd(CItem* _item) { m_itemlist.push_back(_item); }
};

