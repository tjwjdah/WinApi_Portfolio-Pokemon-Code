#include "stdafx.h"
#include "CDocter.h"


#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CCollider.h"
CDocter::CDocter() :m_pTex(nullptr),
m_on(true),
m_vecter(0)
{
	SetObjtype(OBJ_TYPE::NPC);

}

CDocter::~CDocter()
{
}

CDocter::CDocter(const CDocter& _origin)
{
}

void CDocter::update()
{
}

void CDocter::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y -16.f
		, m_pTex->Width(), m_pTex->Height() / 4
		, m_pTex->GetDC()
		, 0, 0 + m_pTex->Height() / 4 * m_vecter
		, m_pTex->Width(), m_pTex->Height() / 4
		, RGB(255, 0, 255));
}

void CDocter::init()
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"docter");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"docter", L"Texture//docter.bmp");
	}
	CCollider* pCollider = new CCollider;
	pCollider->SetOffsetPos(Vec2(32.f, 32.f));
	pCollider->SetScale(Vec2(64.f, 64.f));
	AddCollider(pCollider);
}

void CDocter::OnCollisionEnter(CCollider* _pOther)
{
}

void CDocter::OnCollision(CCollider* _pOther)
{
}

void CDocter::OnCollisionExit(CCollider* _pOther)
{
}

void CDocter::SetPokeball(int _i)
{
}
