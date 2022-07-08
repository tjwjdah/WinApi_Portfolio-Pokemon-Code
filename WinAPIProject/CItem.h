#pragma once
#include "CObj.h"
class CItem :
    public CObj
{
public:
    CItem();
    ~CItem();
    CItem(const CItem& _origin);
protected:
    CTexture* m_pTex;
    wstring   m_Explanation;
    wstring   m_itemname;
    
    int       m_amount;

public:
  
    virtual void run();
    virtual void init();
    
public:
    CTexture* GetTex() { return m_pTex; }
    wstring   GetExp() { return m_Explanation; }
    wstring   GetName() { return m_itemname; }
    int       Getamount() { return m_amount; }

    void      Setamount(int _amount) {  m_amount=_amount;}

    virtual CItem* Clone() { return new CItem(*this); };
};

