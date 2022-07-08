#include "stdafx.h"
#include "CUIButtonUI.h"
#include "CTilePanelUI.h"


CUIButtonUI::CUIButtonUI() :
	m_ConnectPanel(nullptr),
	m_changeUiType(UI_TYPE::DEFAULT)
{
}

CUIButtonUI::~CUIButtonUI()
{
}

void CUIButtonUI::MouseLBTNDown(Vec2 _vMousePos)
{
	m_ConnectPanel->ChangeShowUIType(m_changeUiType);
}

void CUIButtonUI::SetConnectPanel(CUI* PanelUI)
{
	m_ConnectPanel = dynamic_cast<CTilePanelUI*>(PanelUI);
}
