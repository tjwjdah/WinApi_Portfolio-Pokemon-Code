#pragma once

class CAnimator;


class CAnimation
{
private:
	CAnimator*			m_pAnimator;
	wstring				m_strName;
	vector<tAnimFrame>	m_vecFrm;
	int					m_iCurFrmIdx;
	float				m_fAccTime;
	bool				m_bFinish;

public:
	void finalupdate();
	void render(HDC _dc);

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void AddFrameInfo(const tAnimFrame& _frm){m_vecFrm.push_back(_frm);}


public:
	wstring GetName() { return m_strName; };
	tAnimFrame& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	bool IsFinish() { return m_bFinish; }
	void SetFrameIdx(int _iFrmIdx)
	{
		assert(!(_iFrmIdx >= m_vecFrm.size()));

		m_bFinish = false;
		m_iCurFrmIdx = _iFrmIdx;
		m_fAccTime = 0.f;
	}

	int GetCurFrmldx() { return m_iCurFrmIdx; }
	int GetCurMaxFrmIdx() { return (int)m_vecFrm.size(); }
	CAnimation* Clone() { return new CAnimation(*this); }



public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

