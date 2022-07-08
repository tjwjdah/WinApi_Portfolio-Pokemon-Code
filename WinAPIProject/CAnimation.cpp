#include "stdafx.h"
#include "CAnimation.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CCamera.h"
#include "CTexture.h"

#include "CTimeMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_iCurFrmIdx(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}


void CAnimation::finalupdate()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	while (true)
	{
		if (m_fAccTime >= m_vecFrm[m_iCurFrmIdx].fDuration)
		{
			float fOverTime = m_fAccTime - m_vecFrm[m_iCurFrmIdx].fDuration;
			++m_iCurFrmIdx;

			if (m_vecFrm.size() <= m_iCurFrmIdx)
			{
				m_bFinish = true;
				break;
			}

			m_fAccTime = fOverTime;
		}
		else
			break;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObj* pObject = m_pAnimator->GetObj();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(pObject->GetPos());	 
	
	vRenderPos += m_vecFrm[m_iCurFrmIdx].vOffset;





	/*TransparentBlt(_dc
		, (int)(vRenderPos.x - m_vecFrm[m_iCurFrmIdx].vSliceSize.x / 2.f)
		, (int)(vRenderPos.y - m_vecFrm[m_iCurFrmIdx].vSliceSize.y / 2.f)
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.x
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.y
		, m_vecFrm[m_iCurFrmIdx].pTargetTex->GetDC()
		, (int)m_vecFrm[m_iCurFrmIdx].vLT.x
		, (int)m_vecFrm[m_iCurFrmIdx].vLT.y
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.x
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.y
		, RGB(255, 0, 255));*/

	BLENDFUNCTION ftn = {};

	ftn.BlendOp = AC_SRC_OVER;
	ftn.AlphaFormat = AC_SRC_ALPHA;
	ftn.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.x
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.y
		, m_vecFrm[m_iCurFrmIdx].pTargetTex->GetDC()
		, (int)m_vecFrm[m_iCurFrmIdx].vLT.x
		, (int)m_vecFrm[m_iCurFrmIdx].vLT.y
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.x
		, (int)m_vecFrm[m_iCurFrmIdx].vSliceSize.y
		, ftn);
}
