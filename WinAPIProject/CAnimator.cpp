#include "stdafx.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pObject(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	for (; iter != m_mapAnim.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
}

CAnimator::CAnimator(const CAnimator& _origin)
	: m_pObject(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(_origin.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _origin.m_mapAnim.begin();

	for (; iter != _origin.m_mapAnim.end(); ++iter)
	{		
		CAnimation* pCopyAnim = iter->second->Clone();

		m_mapAnim.insert(make_pair(iter->first, pCopyAnim));
		pCopyAnim->SetName(iter->first);
		pCopyAnim->m_pAnimator = this;
	}

	// 원본 Animator 가 재생중인 Animation 이 있었다면
	if (_origin.m_pCurAnim)
	{		
		// 같은걸 찾아서 지정
		m_pCurAnim = GetAnimation(_origin.m_pCurAnim->GetName());
	}	
}

void CAnimator::finalupdate()
{
	
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->finalupdate();

		if (m_pCurAnim->IsFinish() && m_bRepeat)
		{
			m_pCurAnim->SetFrameIdx(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}

void CAnimator::AddAnimation(const wstring& _strAnimName, CTexture* _pTargetTex
	, Vec2 _vLT, Vec2 _vSliceSize, UINT _iFrameCount, float _fDuration)
{
	CAnimation* pAnimation = new CAnimation;

	if (GetAnimation(_strAnimName) != nullptr)
	{
		int a = 0;
		return;
	}
		


	tAnimFrame tFrm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		tFrm.pTargetTex = _pTargetTex;
		tFrm.vLT = Vec2(_vLT.x + ((float)i * _vSliceSize.x), _vLT.y);
		tFrm.fDuration = _fDuration;
		tFrm.vSliceSize = _vSliceSize;

		pAnimation->AddFrameInfo(tFrm);
	}
	
	pAnimation->m_pAnimator = this;
	pAnimation->SetName(_strAnimName);	
	m_mapAnim.insert(make_pair(_strAnimName, pAnimation));	
}

CAnimation* CAnimator::GetAnimation(const wstring& _strAnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strAnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat, int _iFrmIdx)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);	
	assert(iter != m_mapAnim.end());

	m_pCurAnim = iter->second;
	m_pCurAnim->SetFrameIdx(_iFrmIdx);

	m_bRepeat = _bRepeat;
}
