#include "stdafx.h"
#include "CSceneMgr.h"

#include "CToolScene.h"
#include "CStartScene.h"
#include "CBattleScene.h"
#include "CTrainerBattle.h"
#include "COPScene.h"
#include "CTimeMgr.h"
#include "CEDScene.h"
CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
	
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CToolScene;
	m_arrScene[(UINT)SCENE_TYPE::START] = new CStartScene;
	m_arrScene[(UINT)SCENE_TYPE::BATTLE] = new CBattleScene;
	m_arrScene[(UINT)SCENE_TYPE::TRAINERBATTLE] = new CTrainerBattle;
	m_arrScene[(UINT)SCENE_TYPE::OP] = new COPScene;
	m_arrScene[(UINT)SCENE_TYPE::ED] = new CEDScene;

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::OP];

	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	if (nullptr != m_pCurScene)
	{
		m_pCurScene->update();
		m_pCurScene->lateupdate();
		m_pCurScene->finalupdate();
	}	
}

void CSceneMgr::render(HDC _dc)
{
	if (nullptr != m_pCurScene)
	{
		m_pCurScene->render(_dc);
	}	
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNextScene,float _Time)
{
	// ������ Scene �̸� ����
	if (m_pCurScene == m_arrScene[(UINT)_eNextScene])
		return;
	
	m_pCurScene->Exit();
	
	
		m_pCurScene = m_arrScene[(UINT)_eNextScene];

		m_pCurScene->Enter();
	
}
