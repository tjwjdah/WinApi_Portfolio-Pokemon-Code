#include "stdafx.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CCamera.h"

#include "CPlayer.h"
#include "CEventMgr.h"

#include "CTexture.h"
#include "CResMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}


void CMonster::init()
{
	CCollider* pCollider = new CCollider;
	pCollider->SetScale(Vec2(50.f, 50.f));
	AddCollider(pCollider);
}

void CMonster::update()
{
}

void CMonster::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
		
	BLENDFUNCTION ftn = {};

	ftn.BlendOp = AC_SRC_OVER;
	ftn.AlphaFormat = AC_SRC_ALPHA;
	ftn.BlendFlags = 0;
	ftn.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)m_pTex->Width()
		, (int)m_pTex->Height()
		, m_pTex->GetDC()
		, (int)0
		, (int)0
		, (int)m_pTex->Width()
		, (int)m_pTex->Height()
		, ftn);
	//Rectangle(_dc, (int)vPos.x, (int)vPos.y, (int)vPos.x + TILE_SIZE, (int)vPos.y + TILE_SIZE);

	if (nullptr != GetCollider())
		GetCollider()->render(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	if (nullptr != dynamic_cast<CPlayer*>(_pOther->GetObj()))
	{
		DeleteObject(this);
	}
}
