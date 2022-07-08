#pragma once
#include "CRes.h"

union tColor
{
	struct
	{
		BYTE b, g, r, a;
	};
	COLORREF ref;	
};

class CTexture :
	public CRes
{
private:
	HBITMAP		m_hBit;
	HDC			m_hDC;
	BITMAP		m_tInfo;

private:
	void Load(const wstring& _strPath);

public:
	HDC GetDC() { return m_hDC; }
	int Width() { return m_tInfo.bmWidth; }
	int Height() { return m_tInfo.bmHeight; }

	void SetPixel(UINT _x, UINT _y, BYTE r, BYTE g, BYTE b);
	tColor GetPixel(UINT _x, UINT _y);

public:
	CTexture();
	~CTexture();

	friend class CResMgr;
};

