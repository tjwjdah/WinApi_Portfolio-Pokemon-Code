#include "stdafx.h"
#include "CEDScene.h"

#include "CEDAnim.h"
#include "CObj.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"
#include "CSoundMgr.h"
CEDScene::CEDScene():
	m_pTex(nullptr)
{
}

CEDScene::~CEDScene()
{
}

void CEDScene::init()
{
	CObj* pObj = new CEDAnim;

	pObj->SetPos(Vec2(450.f, 250.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	AddObj(pObj, OBJ_TYPE::BASEOBJECT);
	m_pTex = CResMgr::GetInst()->FindTexture(L"ED");
	if (nullptr == m_pTex)
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"ED", L"Texture//ED.bmp");
	}
	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Ending.wav", L"Sound\\Ending.wav");
	pNewSound->SetVolume(100);
	pNewSound->PlayToBGM();
}

void CEDScene::update()
{
	CScene::update();
}

void CEDScene::lateupdate()
{
	CScene::lateupdate();
}

void CEDScene::finalupdate()
{
	CScene::finalupdate();
}

void CEDScene::render(HDC _dc)
{
	BitBlt(_dc
		, 0
		, 0
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0, SRCCOPY);  //기본 백그라운드
	CScene::render(_dc);
	HFONT myFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"PokemonGSC");
	HFONT oldFont = (HFONT)SelectObject(_dc, myFont);
	SetBkMode(_dc, TRANSPARENT);

	SetTextColor(_dc, RGB(0, 0, 0));
	wstring s = L"감사합니다.";
	TextOut(_dc, 100, 280, s.c_str(), s.size());

	SelectObject(_dc, oldFont);
	DeleteObject(myFont);
}

void CEDScene::Enter()
{
	init();
}

void CEDScene::Exit()
{
}
