#include "stdafx.h"
#include "CItem.h"

CItem::CItem():
m_pTex(nullptr),
m_amount(0)
{
}

CItem::~CItem()
{
}

CItem::CItem(const CItem& _origin) :CObj(_origin),
m_pTex(_origin.m_pTex),
m_amount(0),
m_Explanation(_origin.m_Explanation)
{
}

void CItem::run()
{
}

void CItem::init()
{


}
