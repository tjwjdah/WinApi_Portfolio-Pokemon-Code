#include "stdafx.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CObjectMgr.h"

#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"

#include "CSound.h"
#include "CResMgr.h"

CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_dc(nullptr)
	, m_arrPen{}
{
}

CCore::~CCore()
{
	// Main DC ����
	ReleaseDC(m_hWnd, m_dc);

	// BackBuffer ����
	DeleteObject(m_backbuffer);
	DeleteDC(m_memDC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::ChangeWindowSize(POINT _ptLT, POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	SetWindowPos(m_hWnd, nullptr
		, _ptLT.x, _ptLT.y
		, rt.right - rt.left
		, rt.bottom - rt.top, 0);
}

void CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_dc = GetDC(_hWnd);
	srand((unsigned int)time(NULL));
	m_hWnd = _hWnd;
	ChangeWindowSize(POINT{ 10, 10 }, _ptResolution, false);

	// Backbuffer ����
	m_backbuffer = CreateCompatibleBitmap(m_dc, WIN_X, WIN_Y);
	m_memDC = CreateCompatibleDC(m_dc);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_backbuffer);
	DeleteObject(hOldBitmap);

	//HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_memDC, hBrush);
	//DeleteObject(hPrevBrush);

	// Manager �ʱ�ȭ
	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CObjectMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	

	// Create GDI Object
	CreateGDIObject();

	// Sound �ε� �׽�Ʈ

	
}

void CCore::progress()
{
	// Manager Update
	CKeyMgr::GetInst()->update();
	CTimeMgr::GetInst()->update();

	// Object Update
	update();

	// Render
	render();

	// Event ó��
	CEventMgr::GetInst()->update();
}

void CCore::update()
{
	CCamera::GetInst()->update();

	CUIMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	CCollisionMgr::GetInst()->update();		
}

void CCore::render()
{
	// MemDC �ʱ�ȭ
	Rectangle(m_memDC, -1, -1, WIN_X + 1, WIN_Y + 1);

	// Scene ��ü �׸���
	CSceneMgr::GetInst()->render(m_memDC);

	// ī�޶� ȿ��
	CCamera::GetInst()->render(m_memDC);

	// MemDC -> Window
	BitBlt(m_dc, 0, 0, WIN_X, WIN_Y, m_memDC, 0, 0, SRCCOPY);	

	CTimeMgr::GetInst()->render(m_dc);	
}

void CCore::CreateGDIObject()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 30, 30));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(30, 255, 30));	
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(30, 30, 255));	
}
