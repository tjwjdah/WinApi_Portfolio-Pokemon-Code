#include "stdafx.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llFrequency{}
	, m_llOldCount{}
	, m_llCurCount{}
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llOldCount);
	QueryPerformanceCounter(&m_llPrevCount);
	a = 0;
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_dFPS = 1. / m_dDeltaTime;


	m_llPrevCount = m_llCurCount;


	// 1�ʸ��� Frequency ����
	if (m_llCurCount.QuadPart - m_llOldCount.QuadPart > m_llFrequency.QuadPart)
	{
		QueryPerformanceFrequency(&m_llFrequency);
		m_llOldCount = m_llCurCount;
	}
}

void CTimeMgr::render(HDC _dc)
{
	static double dTime = 0.;

	dTime += m_dDeltaTime;
	a += m_dDeltaTime;
	if (1. < dTime)
	{
		wchar_t szDeltaTime[255] = {};
		
		swprintf(szDeltaTime, 255, L"FPS : %lf, DT : %lf time: %lf ", m_dFPS, m_dDeltaTime, a);
		SetWindowText(CCore::GetInst()->GetHwnd(), szDeltaTime);
		dTime = 0.;
	}	
}