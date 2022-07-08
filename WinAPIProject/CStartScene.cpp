#include "stdafx.h"
#include "CStartScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "CCore.h"

#include "CKeyMgr.h"

#include "CSound.h"
#include "CResMgr.h"
#include "CTile.h"
#include "CPanelUI.h"
#include "CUI.h"
#include "CTileUI.h"
#include "CArrowUI.h"
#include "CTilePanelUI.h"
#include "CMapToolUI.h"
#include "CUIButtonUI.h"
#include "C2Tilebutton.h"
#include "CTIleColliderOn.h"
#include "CObjectMgr.h"
#include "CSaveUI.h"
#include "CLoadUI.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CTextBar.h"

#include "CPlayer.h"
#include "CTexture.h"
#include "CGreen.h"
#include "CNurse.h"
#include "CPokeball.h"

#include "CCollisionMgr.h"
#include "CTeleportMgr.h"
#include "CEvolutionMgr.h"

#include "CDocter.h"
#include "CPokemon.h"

#include "CPsybeam.h"

#include "CSound.h"
#include "CSoundMgr.h"

CStartScene::CStartScene() :m_PlayerPos(Vec2(0.f, 0.f)),
m_noinit(false),
m_Player(nullptr),
m_TextBar(nullptr),
m_preCamera(Vec2(960, 1088)),
m_p1(nullptr),
m_p2(nullptr),
m_p3(nullptr),
m_CoShow(false),
soundon(0)
{
}
CStartScene::~CStartScene()
{
	delete m_p1;
	delete	m_p2;
	delete	m_p3;
}
void CStartScene::init()
{
	
	wstring strMapFilePath = CPathMgr::GetResPath();
	strMapFilePath += L"Tile\\map_complete_a4.tile";
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strMapFilePath.c_str(), L"rb");

	

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	assert(pCurScene);

	// 타일 가로 세로 개수 읽기
	UINT xcount = 0;
	UINT ycount = 0;

	fread(&xcount, sizeof(UINT), 1, pFile);
	fread(&ycount, sizeof(UINT), 1, pFile);

	pCurScene->CreateTile(xcount, ycount);

	// 생성된 타일 정보 복구
	const vector<CObj*>& vecTile = pCurScene->GetObjects(OBJ_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	CObj* pObj = new CPlayer;
	m_Player =dynamic_cast<CPlayer*>(pObj);
	pObj->SetPos(Vec2(960, 1088));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	pObj->SetScale(Vec2(50.f, 50.f));
	AddObj(pObj, OBJ_TYPE::PLAYER);
	m_PlayerPos = pObj->GetPos();

	pObj = new CGreen;
	//pObj->SetPos(Vec2(6528.f, 14656.f));
	pObj->SetPos(Vec2(2880.f, 2240.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	pObj->SetScale(Vec2(50.f, 50.f));
	AddObj(pObj, OBJ_TYPE::TRAINER);

	pObj = new CNurse;
	m_Nurse = dynamic_cast<CNurse*>(pObj);
	pObj->SetPos(Vec2(4160.f, 704.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	pObj->SetScale(Vec2(50.f, 50.f));
	AddObj(pObj, OBJ_TYPE::BASEOBJECT);
	
	
	m_p1 = CObjectMgr::GetInst()->FindPokemon(L"Bulbasaur");
	m_p1->SetLv(5);
	m_p1->init();
	m_p1->SetPlayerown(true);
	m_p1->SetPos(Vec2(160.f, 256.f));
	
	CTexture* m_pTex = CResMgr::GetInst()->FindTexture(L"Bulbasaur");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Bulbasaur", L"Texture\Pokemon\Bulbasaur.bmp");

	pObj = new CPokeball;
	CPokeball* Pokeball = dynamic_cast<CPokeball*>(pObj);
	Pokeball->SetPokeTexture(m_pTex);
    Pokeball->SetPokemon(m_p1);
	pObj->SetPos(Vec2(1152.f, 2180.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));

	AddObj(pObj, OBJ_TYPE::BASEOBJECT);
	


	m_p2 = CObjectMgr::GetInst()->FindPokemon(L"Squirtle");
	m_p2->SetLv(5);
	m_p2->init();
	m_p2->SetPlayerown(true);
	m_p2->SetPos(Vec2(160.f, 256.f));
	
	 m_pTex = CResMgr::GetInst()->FindTexture(L"Squirtle");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Squirtle", L"Texture\Pokemon\Squirtle.bmp");


	pObj = new CPokeball;
	pObj->SetPos(Vec2(1216.f, 2180.f));
	Pokeball = dynamic_cast<CPokeball*>(pObj);
	Pokeball->SetPokeTexture(m_pTex);
	Pokeball->SetPokemon(m_p2);
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));

	AddObj(pObj, OBJ_TYPE::BASEOBJECT);



	m_p3 = CObjectMgr::GetInst()->FindPokemon(L"Charmander");
	m_p3->SetLv(5);
	m_p3->init();
	m_p3->SetPlayerown(true);
	m_p3->SetPos(Vec2(160.f, 256.f));
	

	m_pTex = CResMgr::GetInst()->FindTexture(L"Charmander");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Charmander", L"Texture\Pokemon\Charmander.bmp");
	pObj = new CPokeball;
	Pokeball = dynamic_cast<CPokeball*>(pObj);
	Pokeball->SetPokeTexture(m_pTex);
	Pokeball->SetPokemon(m_p3);
	pObj->SetPos(Vec2(1280.f , 2180.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	
	AddObj(pObj, OBJ_TYPE::BASEOBJECT);




	pObj = new CDocter;

	pObj->SetPos(Vec2(1024.f,2112.f));
	pObj->init();
	//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
	AddObj(pObj, OBJ_TYPE::NPC);
	


	 m_pTex = CResMgr::GetInst()->FindTexture(L"Textbar2");
	if (nullptr == m_pTex)
		m_pTex = CResMgr::GetInst()->LoadTexture(L"Textbar2", L"Texture\\Textbar2.bmp");


	CUI* pUI = new CTextBar;
	pUI->SetTexture(m_pTex);
	pUI->SetScale(Vec2((float)m_pTex->Width(), (float)m_pTex->Height()));
	pUI->SetPos(Vec2(10, 448));
	pUI->SetUse(false);
	pUI->SetUIType(UI_TYPE::DEFAULT);
	//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
	// 부모 UI 에 자식 UI 추가
	AddObj(pUI, OBJ_TYPE::UI);


	m_TextBar = dynamic_cast<CTextBar*>(pUI);
	m_TextBar->Set_battleOn(false);


	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Pallet-Town-Theme.wav", L"Sound\\Pallet-Town-Theme.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\select.wav", L"Sound\\select.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Fanfare-TM-&-HM-Get-(RS).wav", L"Sound\\Fanfare-TM-&-HM-Get-(RS).wav");


	// 충돌 그룹 지정
	CCollisionMgr::GetInst()->CollisionCheckClear();


	// 카메라 초기화
	CCamera::GetInst()->init();
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);

	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::BASEOBJECT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::HOUSE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::JUMPWALL);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::POKEMONSPAWNOBJ);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::TRAINER);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	m_noinit = true;

	CTeleportMgr::GetInst()->init();
	CEvolutionMgr::GetInst()->init();
}


bool compare3(CObj* a, CObj* b)
{
	if (a->GetPos().y == b->GetPos().y)
	{
		if (a->GetObjtype() == OBJ_TYPE::PLAYER)
			return  true;

	}
	return a->GetPos().y < b->GetPos().y;
}

void CStartScene::update()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (i == (UINT)OBJ_TYPE::TILE)
		{
			TileUpdate(0);
		}
		else
		{
			const vector<CObj*>& vecObj = GetObjects((OBJ_TYPE)i);

			for (size_t j = 0; j < vecObj.size(); ++j)
			{
				if (!vecObj[j]->IsDead())
				{
					if (i == (UINT)OBJ_TYPE::PLAYER)
					{
						if (m_PlayerPos != vecObj[j]->GetPos())
						{
							m_PlayerPos = vecObj[j]->GetPos();
							vector<CObj*>::iterator begin = m_arrObjRender.begin();
							vector<CObj*>::iterator end = m_arrObjRender.end();
							std::sort(begin, end, compare3);
						}
					}
					vecObj[j]->update();

				}
			}
		}
	
	}

	if (KEY_TAP(KEY_TYPE::KEY_N))
	{
		if (m_CoShow)
			m_CoShow = false;
		else
			m_CoShow = true;
	}
	if(!(m_timeEventplay.empty()))
	{
		m_timeEventplay.front().cTime += fDT;
		if (m_timeEventplay.front().dTime < m_timeEventplay.front().cTime)
		{
			CEventMgr::GetInst()->AddEvent(m_timeEventplay.front());
			m_timeEventplay.pop_front();
		}
	}

	CTeleportMgr::GetInst()->update(m_Player);
	for (size_t i = 0; i < m_Player->GetPokemonMember().size(); i++)
	{
		CEvolutionMgr::GetInst()->update(m_Player->GetPokemonMember()[i],i);
	}
	
	
}

void CStartScene::lateupdate()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (i == (UINT)OBJ_TYPE::TILE)
		{
			TileUpdate(1);
		}
		else
		{
			const vector<CObj*>& vecObj = GetObjects((OBJ_TYPE)i);

			for (size_t j = 0; j < vecObj.size(); ++j)
			{
				if (!vecObj[j]->IsDead())
					vecObj[j]->lateupdate();
			}
		}
	}
}

void CStartScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (i == (UINT)OBJ_TYPE::TILE)
		{
			TileUpdate(2);
		}
		else
		{
			const vector<CObj*>& vecObj = GetObjects((OBJ_TYPE)i);

			for (size_t j = 0; j < vecObj.size(); ++j)
			{
				if (!vecObj[j]->IsDead())
					vecObj[j]->finalupdate();
			}
		}
	}
}

void CStartScene::render(HDC _dc)
{
	vector<CObj*>::const_iterator iter = m_arrObjRender.begin();
	
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (i == (UINT)OBJ_TYPE::TILE)
		{
			TileUpdate(3);
		}
		else
		{
			vector<CObj*>& vecObj = m_arrObj[i];
			vector<CObj*>::const_iterator iter = vecObj.begin();
			if (i != (UINT)OBJ_TYPE::UI)
			{
				for (; iter != vecObj.end(); )
				{
					if ((*iter)->IsDead())
					{
						iter = vecObj.erase(iter);
					}
					else
					{
						/*if (i == (UINT)OBJ_TYPE::UI)
							(*iter)->render(_dc);*/
						if (m_CoShow) {
							(*iter)->colliderrender(_dc);
							}
						++iter;
					}
				}
			}
		}
	}
	for (; iter != m_arrObjRender.end(); )
	{
		if ((*iter)->IsDead())
		{
			iter = m_arrObjRender.erase(iter);
		}
		else
		{
			if ((*iter)->GetObjtype() != OBJ_TYPE::UI)
			{
				(*iter)->render(_dc);
			}
			//(*iter)->colliderrender(_dc);
			++iter;
		}
	}
	vector<CObj*>& vecObj = m_arrObj[(int)OBJ_TYPE::UI];

	for (size_t i = 0; i < vecObj.size(); i++)
	{
		if (!vecObj[i]->IsDead())
			vecObj[i]->render(_dc);
	}

	CEvolutionMgr::GetInst()->render(_dc);
	m_TextBar->render(_dc);
}

void CStartScene::TileUpdate(int _iUpdate)
{
	const vector<CObj*>& vecTile = GetObjects(OBJ_TYPE::TILE);
	//vector<CObj*>& vecObj = GetObjects2(OBJ_TYPE::TILE);
	//vector<CObj*>::iterator iter = vecObj.begin();
	Vec2 vLook = CCamera::GetInst()->GetLookAt();
	Vec2 vLT = vLook - Vec2(WIN_X / 2, WIN_Y / 2);

	int iLineXCount = WIN_X / TILE_SIZE;
	int iLineYCount = WIN_Y / TILE_SIZE;

	int iCol = (int)(vLT.x / TILE_SIZE);
	int iMaxCol = iCol + iLineXCount + 1;

	int iRow = (int)(vLT.y / TILE_SIZE);
	int iMaxRow = iRow + iLineYCount + 1;

	if (vLT.x < 0)
		iCol = 0;
	if (GetXCount() < iMaxCol)
		iMaxCol = GetXCount();

	if (vLT.y < 0)
		iRow = 0;
	if (GetYCount() < iMaxRow)
		iMaxRow = GetYCount();
	for (int i = iRow; i < iMaxRow; ++i)
	{
		for (int j = iCol; j < iMaxCol; ++j)
		{
			int idx = GetXCount() * i + j;
			if (_iUpdate == 0)
				vecTile[idx]->update();
			else if (_iUpdate == 1)
				vecTile[idx]->lateupdate();
			else if (_iUpdate == 2)
				vecTile[idx]->finalupdate();
			else
			{
				vecTile[idx]->render(CCore::GetInst()->GetMemDC());
				if(m_CoShow)
					vecTile[idx]->colliderrender(CCore::GetInst()->GetMemDC());
			}
		}
	}

}

void CStartScene::Enter()
{
	if(!m_noinit)
		init();	
	CCamera::GetInst()->Setcamera(m_preCamera);
	m_Player->Setbattle(false);
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\Pallet-Town-Theme.wav");
	pNewSound->PlayToBGM(true);
	pNewSound->SetVolume(100.f);
}

void CStartScene::Exit()
{
	m_preCamera = CCamera::GetInst()->GetLookAt();
}

void CStartScene::timeEvenadd(CObj* _pNewObj, Vec2 _vPos, OBJ_TYPE _eType, float _dtime)
{
	_pNewObj->SetPos(_vPos);

	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.wParam = (DWORD_PTR)_pNewObj;
	evn.lParam = (DWORD_PTR)_eType;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CStartScene::timeEvenadd(CObj* _pDeleteObj, float _dtime)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)_pDeleteObj;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CStartScene::timeEvenadd(SCENE_TYPE _eNextScene, float _dtime)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.wParam = (DWORD_PTR)_eNextScene;
	evn.dTime = _dtime;
	m_timeEventplay.push_back(evn);
}

void CStartScene::SetpreCamera()
{
	m_preCamera = CCamera::GetInst()->GetLookAt();
}
