#pragma once

class CObj;
class CAnimation;


class CAnimator
{
private:
	CObj*						m_pObject;
	map<wstring, CAnimation*>	m_mapAnim;
	CAnimation*					m_pCurAnim;
	bool						m_bRepeat;

public:
	void finalupdate();
	void render(HDC _dc);


public:
	void AddAnimation(const wstring& _strAnimName, CTexture* _pTargetTex, Vec2 _vLT, Vec2 _vSliceSize, UINT _iFrameCount, float _fDuration);
	CAnimation* GetAnimation(const wstring& _strAnimName);
	CAnimation* GetCurAnimation() { return m_pCurAnim; }


	void Play(const wstring& _strName, bool _bRepeat, int _iFrmIdx = 0);

	CObj* GetObj() { return m_pObject; }

	CAnimator* Clone() { return new CAnimator(*this); }

public:
	CAnimator();
	~CAnimator();

private:
	CAnimator(const CAnimator& _origin);

	friend class CObj;
};

