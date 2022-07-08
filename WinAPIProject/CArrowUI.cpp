#include "stdafx.h"
#include "CArrowUI.h"
#include "CUI.h"
#include "CKeyMgr.h"
#include "CTexture.h"

#include "resource.h"
#include "CPanelUI.h"


CArrowUI::CArrowUI() :
	RaL(true)
{

}

CArrowUI::CArrowUI(bool _RaL) :
	RaL(_RaL)
{
}

CArrowUI::~CArrowUI()
{
}

void CArrowUI::render(HDC _dc)
{
	if (nullptr == GetTexture())
		return;

	int iWidth = GetTexture()->Width();
	int iHeight = GetTexture()->Height();



	if (RaL)
	{
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y
			, iWidth, iHeight / 2
			, GetTexture()->GetDC()
			, 0, 0
			, iWidth, iHeight / 2
			, RGB(255, 0, 255));

	}
	else
	{
		TransparentBlt(_dc
			, (int)GetFinalPos().x
			, (int)GetFinalPos().y
			, iWidth, iHeight / 2
			, GetTexture()->GetDC()
			, 0, (iHeight / 2)
			, iWidth, iHeight / 2
			, RGB(255, 0, 255));
	}

}


void CArrowUI::MouseLBTNDown(Vec2 _vMousePos)
{
	CUI::MouseLBTNDown(_vMousePos);
	CPanelUI* PanelUI = dynamic_cast<CPanelUI*>(GetParent());
	if (RaL)
	{
		PanelUI->PageNumUp();
	}
	else
	{
		PanelUI->PageNumDawn();
	}
}
