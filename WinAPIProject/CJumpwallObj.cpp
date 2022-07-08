#include "stdafx.h"
#include "CJumpwallObj.h"


#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"

CJumpwallObj::CJumpwallObj():
	m_pTex(nullptr)
{
	SetObjtype(OBJ_TYPE::JUMPWALL);
}

CJumpwallObj::~CJumpwallObj()
{
}

CJumpwallObj::CJumpwallObj(const CJumpwallObj& _origin) :CObj(_origin),
m_pTex(_origin.m_pTex)
{
}

void CJumpwallObj::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CJumpwallObj::update()
{
}

void CJumpwallObj::render(HDC _dc)
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

void CJumpwallObj::OnCollisionEnter(CCollider* _pOther)
{
}
