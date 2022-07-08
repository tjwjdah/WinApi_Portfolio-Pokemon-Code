#include "stdafx.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCamera.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_vDir(Vec2(1.f, -1.f))
	, m_fSpeed(300.f)
{
	m_vDir.normalize();
}

void CMissile::update()
{
	Vec2 vPos = GetPos();	

	vPos.x += m_vDir.x * m_fSpeed * fDT;
	vPos.y += m_vDir.y * m_fSpeed * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Ellipse(_dc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

	if (nullptr != GetCollider())
		GetCollider()->render(_dc);	
}
