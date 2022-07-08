#include "stdafx.h"
#include "CBaseObject.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"

CBaseObject::CBaseObject():m_pTex(nullptr)
{
	SetObjtype(OBJ_TYPE::BASEOBJECT);
}

CBaseObject::~CBaseObject()
{
}

CBaseObject::CBaseObject(const CBaseObject& _origin):
	 CObj(_origin)
	, m_pTex(_origin.m_pTex)
{
	
}

void CBaseObject::SetTexture(CTexture* _pTex)
{
	m_pTex = _pTex;
}

void CBaseObject::update()
{
}

void CBaseObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	if (nullptr != GetCollider())
	//	GetCollider()->render(_dc);

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

void CBaseObject::OnCollisionEnter(CCollider* _pOther)
{
}
