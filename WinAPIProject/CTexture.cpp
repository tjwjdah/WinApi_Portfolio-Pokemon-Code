#include "stdafx.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_tInfo{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

void CTexture::Load(const wstring& _strPath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strPath.c_str()
		, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);			

	m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	HBITMAP hPrev = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrev);	

	GetObject(m_hBit, sizeof(BITMAP), &m_tInfo);
}


void CTexture::SetPixel(UINT _x, UINT _y, BYTE r, BYTE g, BYTE b)
{
	if (nullptr == m_tInfo.bmBits)
		::SetPixel(m_hDC, _x, _y, RGB(r, g, b));
	else
	{
		tColor* pColor = (tColor*)m_tInfo.bmBits;
		pColor[_y * m_tInfo.bmWidth + _x].b = b;
		pColor[_y * m_tInfo.bmWidth + _x].g = g;
		pColor[_y * m_tInfo.bmWidth + _x].r = r;		
	}
}

tColor CTexture::GetPixel(UINT _x, UINT _y)
{
	_y = Height() - _y - 1;

	tColor color = {};

	if (_x < 0 || Width() <= _x
		|| _y < 0 || Height() <= _y)
		return color;

	if (nullptr == m_tInfo.bmBits)
	{
		COLORREF col = ::GetPixel(m_hDC, _x, _y);
		color.r = col & 0xff;
		color.g = (col >> 8) & 0xff;
		color.b = (col >> 16) & 0xff;
		color.a = (col >> 24) & 0xff;
	}
	else
	{
		tColor* pColor = (tColor*)m_tInfo.bmBits;
		color = pColor[_y * m_tInfo.bmWidth + _x];
	}
	return color;
}
