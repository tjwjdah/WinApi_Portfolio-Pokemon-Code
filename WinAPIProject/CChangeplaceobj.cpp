#include "stdafx.h"
#include "CChangeplaceobj.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"
CChangeplaceobj::CChangeplaceobj():
	m_pTex(nullptr)
, m_ChangePos(0.f,0.f)
{
	SetObjtype(OBJ_TYPE::CHANGPLACEOBJ);
}

CChangeplaceobj::~CChangeplaceobj()
{
}

CChangeplaceobj::CChangeplaceobj(const CChangeplaceobj& _origin):
	CObj(_origin)
	,m_pTex(_origin.m_pTex)
, m_ChangePos(_origin.m_ChangePos)
{
}

void CChangeplaceobj::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CChangeplaceobj::update()
{
}

void CChangeplaceobj::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (nullptr != GetCollider())
		//GetCollider()->render(_dc);

	if (m_pTex != nullptr) {
		BLENDFUNCTION ftn = {};

		ftn.BlendOp = AC_SRC_OVER;
		ftn.AlphaFormat = AC_SRC_ALPHA;
		ftn.SourceConstantAlpha = 255;
		AlphaBlend(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, m_pTex->Width()
			, m_pTex->Height()
			, m_pTex->GetDC()
			, 0
			, 0
			, m_pTex->Width()
			, m_pTex->Height()
			, ftn);
	}
}

void CChangeplaceobj::OnCollisionEnter(CCollider* _pOther)
{
}
