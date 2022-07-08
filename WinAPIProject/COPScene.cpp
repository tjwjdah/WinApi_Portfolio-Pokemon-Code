#include "stdafx.h"
#include "COPScene.h"

#include "CTexture.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

#include "CSound.h"
#include "CSoundMgr.h"
COPScene::COPScene() :m_pTex1(nullptr),
m_pTex2(nullptr),
m_on(false),
m_on2(true)
{


}

COPScene::~COPScene()
{
}

void COPScene::init()
{

	m_pTex1 = CResMgr::GetInst()->FindTexture(L"OP");
	if (nullptr == m_pTex1)
	{
		m_pTex1 = CResMgr::GetInst()->LoadTexture(L"OP", L"Texture//OP.bmp");
	}

	m_pTex2 = CResMgr::GetInst()->FindTexture(L"OP2");
	if (nullptr == m_pTex2)
	{
		m_pTex2 = CResMgr::GetInst()->LoadTexture(L"OP2", L"Texture//OP2.bmp");
	}
	
	
}

void COPScene::update()
{
	if (KEY_TAP(KEY_TYPE::SPACE))
	{
		CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Opening.wav", L"Sound\\Opening.wav");
		pNewSound->PlayToBGM(true);
		pNewSound->SetVolume(100.f);
	}
	if (m_on)
	{
		if (KEY_TAP(KEY_TYPE::KEY_UP))
		{
			m_on2 = true;
		}
		if (KEY_TAP(KEY_TYPE::KEY_DOWN))
		{
			m_on2 = false;
		}
		if (m_on2)
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				ChangeScene(SCENE_TYPE::TOOL);
			}
		}
		else
		{
			if (KEY_TAP(KEY_TYPE::KEY_Z))
			{
				ChangeScene(SCENE_TYPE::START);
			}
		}
	}
	if (!m_on)
	{
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{
			m_on = true;
			CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Opening.wav");
			pNewSound->Stop();
		}
	}
	
}

void COPScene::lateupdate()
{
}

void COPScene::finalupdate()
{
}

void COPScene::render(HDC _dc)
{
	if (!m_on) {
		BitBlt(_dc
			, 0
			, 0
			, m_pTex1->Width()
			, m_pTex1->Height()
			, m_pTex1->GetDC()
			, 0
			, 0, SRCCOPY);  //기본 백그라운드
	}
	else
	{
		if (m_on2) {
			BitBlt(_dc
				, 0
				, 0
				, m_pTex2->Width()
				, m_pTex2->Height() / 2
				, m_pTex2->GetDC()
				, 0
				, 0, SRCCOPY);
		}
		else
		{
			BitBlt(_dc
				, 0
				, 0
				, m_pTex2->Width()
				, m_pTex2->Height() / 2
				, m_pTex2->GetDC()
				, 0
				, m_pTex2->Height() / 2, SRCCOPY);
		}
	}
}


void COPScene::Enter()
{
	init();
}

void COPScene::Exit()
{
}
