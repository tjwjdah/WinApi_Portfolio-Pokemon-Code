#include "stdafx.h"
#include "CNurse.h"


#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CCollider.h"
CNurse::CNurse() :
	m_ShowPokeball(0),
	m_pTex(nullptr),
	m_on(true)
{
	SetObjtype(OBJ_TYPE::NURSE);
}

CNurse::~CNurse()
{
}

CNurse::CNurse(const CNurse& _origin)
{
}

void CNurse::update()
{
}

void CNurse::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y+32.f
		, m_pTex->Width(), m_pTex->Height()/7 
		, m_pTex->GetDC()
		, 0, 0+ m_pTex->Height() / 7 * m_ShowPokeball
		, m_pTex->Width(), m_pTex->Height()/7
		, RGB(255, 0, 255));


}

void CNurse::init()
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"nurse");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"nurse", L"Texture//nurse.bmp");
	}
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(160.f, 128.f));
	pCollider->SetScale(Vec2(64.f, 128.f));
	AddCollider(pCollider);

}

void CNurse::OnCollisionEnter(CCollider* _pOther)
{
}

void CNurse::SetPokeball(int _i)
{
	 m_ShowPokeball = _i;



}
