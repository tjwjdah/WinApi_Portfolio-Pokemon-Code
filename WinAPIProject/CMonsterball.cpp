#include "stdafx.h"
#include "CMonsterball.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CThrowPokeball.h"
CMonsterball::CMonsterball()
{
	SetObjtype(OBJ_TYPE::ITEM);
	m_itemname = L"���� ��";
}

CMonsterball::~CMonsterball()
{
}

CMonsterball::CMonsterball(const CMonsterball& _origin):CItem(_origin)
{
	m_itemname = L"���� ��";
}

void CMonsterball::run()
{
	CScene* scenc = CSceneMgr::GetInst()->GetCurScene();
	CObj* obj = new CThrowPokeball();
	obj->SetPos(Vec2(160, 232));
	obj->init();
	scenc->AddObj(obj, OBJ_TYPE::DEFAULT);
	m_amount--;
}

void CMonsterball::init()
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"monsterball");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"monsterball", L"Texture//item//monsterball.bmp");
	}
	m_Explanation = L"�߻� ���ϸ��� ���� �� �ִ� ���� ��\n";
}
