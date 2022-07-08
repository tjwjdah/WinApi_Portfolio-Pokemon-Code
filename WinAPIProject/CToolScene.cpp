#include "stdafx.h"
#include "CToolScene.h"

#include "CPathMgr.h"

#include "CCamera.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "Resource.h"
#include "CCore.h"

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

#include "CTimeMgr.h"

#include "CPlayer.h"

#include "CCollisionMgr.h"

#define Tile1num 179

CToolScene::CToolScene()
	: m_hMenu(nullptr)
	, m_MouseimNum(-1)
	, m_pTex(nullptr)
	, m_pTex2(nullptr)
	, m_pTex3(nullptr)
	, m_2TileOn(false)
	, m_MouseUiType(UI_TYPE::TILE)
	, m_colliderOn(false)
	, m_PlayerPos(Vec2(0.f,0.f))

{	
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPIPROJECT));
}

CToolScene::~CToolScene()
{
	if(nullptr != m_hMenu)
		DestroyMenu(m_hMenu);	
}

void CToolScene::init()
{
	// 타일이 사용할 이미지 로딩
	m_pTex = CResMgr::GetInst()->FindTexture(L"TILE");
	if (nullptr == m_pTex)
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TILE", L"Texture\\TILE.bmp");
	m_pTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
	if (nullptr == m_pTex2)
		m_pTex2 = CResMgr::GetInst()->LoadTexture(L"2tile_a", L"Texture//2tile_a.bmp");

	m_pTex3 = CResMgr::GetInst()->FindTexture(L"objects");
	if (nullptr == m_pTex3)
		m_pTex3 = CResMgr::GetInst()->LoadTexture(L"objects", L"Texture//objects.bmp");
	// Camera 초기화
	CCamera::GetInst()->init();
}

void CToolScene::Enter()
{
	init();

	// 메뉴바 추가
	SetMenu(CCore::GetInst()->GetHwnd(), m_hMenu);

	// 메뉴바를 감안한 윈도우 크기 재 계산 및 변경	
	CCore::GetInst()->ChangeWindowSize(POINT{ 10, 10 }, POINT{ WIN_X, WIN_Y }, true);

	// 타일 생성
	CreateTile(10, 10);

	{

		CUI* pPanelUI_Bar = new CMapToolUI;

		CTexture* pPanelTex = CResMgr::GetInst()->FindTexture(L"MapToolUI");
		if (nullptr == pPanelTex)
		{
			pPanelTex = CResMgr::GetInst()->LoadTexture(L"MapToolUI", L"Texture//MapToolUI.bmp");
		}
		pPanelUI_Bar->SetTexture(pPanelTex);
		pPanelUI_Bar->SetScale(Vec2(pPanelTex->Width(), pPanelTex->Height()));
		pPanelUI_Bar->SetPos(Vec2(WIN_X - pPanelUI_Bar->GetScale().x, 0));



		// UI 생성
		CUI* pPanelUI = new CTilePanelUI;

		pPanelTex = CResMgr::GetInst()->FindTexture(L"PanelUITex");
		if (nullptr == pPanelTex)
		{
			pPanelTex = CResMgr::GetInst()->LoadTexture(L"PanelUITex", L"Texture//TilePanel.bmp");
		}
		pPanelUI->SetTexture(pPanelTex);
		pPanelUI->SetScale(Vec2(pPanelTex->Width(), pPanelTex->Height()));
		pPanelUI->SetPos(Vec2(WIN_X - pPanelUI->GetScale().x, 165));


		//버튼
		CUI* pUI = new CUIButtonUI;

		CUIButtonUI* ButtonUI = dynamic_cast<CUIButtonUI*>(pUI);
		ButtonUI->SetConnectPanel(pPanelUI);
		ButtonUI->SetchangeUiType(UI_TYPE::TILE);
		CTexture* pTile = CResMgr::GetInst()->FindTexture(L"TileButton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"TileButton", L"Texture//TileButton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()));
		pUI->SetPos(Vec2(25, 20));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);

		pUI = new CUIButtonUI;
		ButtonUI = dynamic_cast<CUIButtonUI*>(pUI);
		ButtonUI->SetConnectPanel(pPanelUI);
		ButtonUI->SetchangeUiType(UI_TYPE::TILE2);
		pTile = CResMgr::GetInst()->FindTexture(L"TileButton2");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"TileButton2", L"Texture//TileButton2.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()));
		pUI->SetPos(Vec2(100, 20));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);

		pUI = new CUIButtonUI;
		ButtonUI = dynamic_cast<CUIButtonUI*>(pUI);
		ButtonUI->SetConnectPanel(pPanelUI);
		ButtonUI->SetchangeUiType(UI_TYPE::OBJECT);
		pTile = CResMgr::GetInst()->FindTexture(L"ObjectButton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"ObjectButton", L"Texture//ObjectButton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()));
		pUI->SetPos(Vec2(175, 20));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);



		pUI = new C2Tilebutton;
		pTile = CResMgr::GetInst()->FindTexture(L"2tilebutton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"2tilebutton", L"Texture//2tilebutton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()/2));
		pUI->SetPos(Vec2(60, 80));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);
	
		pUI = new CTIleColliderOn;
		pTile = CResMgr::GetInst()->FindTexture(L"colliderbutton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"colliderbutton", L"Texture//colliderbutton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()/2));
		pUI->SetPos(Vec2(250, 20));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);





		pUI = new CSaveUI;

		
		pTile = CResMgr::GetInst()->FindTexture(L"savebutton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"savebutton", L"Texture//savebutton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()));
		pUI->SetPos(Vec2(250, 80));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);

		pUI = new CLoadUI;


		pTile = CResMgr::GetInst()->FindTexture(L"loadbutton");
		if (nullptr == pTile)
		{
			pTile = CResMgr::GetInst()->LoadTexture(L"loadbutton", L"Texture//loadbutton.bmp");
		}
		pUI->SetTexture(pTile);
		pUI->SetScale(Vec2((float)pTile->Width(), (float)pTile->Height()));
		pUI->SetPos(Vec2(325, 80));
		pUI->SetUse(true);
		pUI->SetUIType(UI_TYPE::BUTTON);
		//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
		// 부모 UI 에 자식 UI 추가
		pPanelUI_Bar->AddChildUI(pUI);



		/*m_pTex = CResMgr::GetInst()->FindTexture(L"TILE");
		if (nullptr == m_pTex)
		{
			m_pTex = CResMgr::GetInst()->LoadTexture(L"TILE", L"Texture//TILE.bmp");
		}*/
		//타일 UI 넣어주는 함수
		{
			pUI = new CTileUI;
			
			pUI->SetTexture(m_pTex);
			pUI->SetScale(Vec2(64.f, 64.f));
			pUI->SetPos(Vec2(10, 10));
			pUI->SetUse(true);
			pUI->SetUIType(UI_TYPE::TILE);
			//pUI->SetPos(Vec2((pPanelUI->GetScale().x / 2.f) - (pUI->GetScale().x / 2.f), (pPanelUI->GetScale().y / 2.f) - (pUI->GetScale().y / 2.f)));
			// 부모 UI 에 자식 UI 추가
			pPanelUI->AddChildUI(pUI);

			for (int i = 0; i < 6; i++)
			{
				for (int l = 0; l < 5; l++)
				{
					if (i == 0 && l == 0)
						continue;
					pUI = new CTileUI(i * 5 + l);

		
					pUI->SetTexture(m_pTex);
					pUI->SetScale(Vec2(64.f, 64.f));
					pUI->SetPos(Vec2(10 + l * 84, 10 + i * 84));
					pUI->SetUse(true);
					pUI->SetUIType(UI_TYPE::TILE);
					pPanelUI->AddChildUI(pUI);

				}
			}
			for (int z = 1;z<6; z++)
			{

				for (int i = 0; i < 6; i++)
				{
					for (int l = 0; l < 5; l++)
					{
						if (z * 30 + (i * 5 + l) >= Tile1num)
							break;
						pUI = new CTileUI(z * 30 + (i * 5 + l));

					
						pUI->SetTexture(m_pTex);
						pUI->SetScale(Vec2(64.f, 64.f));
						pUI->SetPos(Vec2(10 + l * 84, 10 + i * 84));
						pUI->SetUse(false);
						pUI->SetUIType(UI_TYPE::TILE);
						pPanelUI->AddChildUI(pUI);
					}
				}
			}

			for (int z = 0;z<2; z++)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int l = 0; l < 5; l++)
					{
						if (z * 30 + (i * 5 + l) == 46)
							break;
						pUI = new CTileUI(z * 30 + (i * 5 + l));

					
						pUI->SetTexture(m_pTex2);
						pUI->SetScale(Vec2(64.f, 64.f));
						pUI->SetPos(Vec2(10 + l * 84, 10 + i * 84));
						pUI->SetUse(false);
						pUI->SetUIType(UI_TYPE::TILE2);
						pPanelUI->AddChildUI(pUI);

					}
				}
			} //2타일

			for (int z = 0; z < 2; z++)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int l = 0; l < 5; l++)
					{
						if (z * 30 + (i * 5 + l) == 39)
							break;
						pUI = new CTileUI(z * 30 + (i * 5 + l));
						
						pUI->SetTexture(m_pTex3);
						pUI->SetScale(Vec2(64.f, 64.f));
						pUI->SetPos(Vec2(10 + l * 84, 10 + i * 84));
						pUI->SetUse(false);
						pUI->SetUIType(UI_TYPE::OBJECT);
						pPanelUI->AddChildUI(pUI);
					}
				}
			}
		


		} 


			pUI = new CArrowUI(false);
			pTile = CResMgr::GetInst()->FindTexture(L"ARROW");
			if (nullptr == pTile)
			{
				pTile = CResMgr::GetInst()->LoadTexture(L"ARROW", L"Texture//arrow.bmp");
			}
			pUI->SetTexture(pTile);
			pUI->SetScale(Vec2(44.f, 36.f));
			pUI->SetPos(Vec2(116.f, 500.f));
			pPanelUI->AddChildUI(pUI);
			pUI = new CArrowUI(true);
			pTile = CResMgr::GetInst()->FindTexture(L"ARROW");
			if (nullptr == pTile)
			{
				pTile = CResMgr::GetInst()->LoadTexture(L"ARROW", L"Texture//arrow.bmp");
			}
			pUI->SetTexture(pTile);
			pUI->SetScale(Vec2(44.f, 36.f));
			pUI->SetPos(Vec2(270.f, 500.f));
			pPanelUI->AddChildUI(pUI);
		

			CObj* pObj = new CPlayer;
			
			pObj->SetPos(Vec2(8000.f, 14656.f));
			pObj->init();
			//pObj->SetPos(Vec2((float)WIN_X / 2.f, (float)WIN_Y / 2.f + 200.f));
			pObj->SetScale(Vec2(50.f, 50.f));
			AddObj(pObj, OBJ_TYPE::PLAYER);
			m_PlayerPos = pObj->GetPos();

			
		AddObj(pPanelUI_Bar, OBJ_TYPE::UI);
		AddObj(pPanelUI, OBJ_TYPE::UI);
	}


	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::BASEOBJECT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::HOUSE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::PLAYER, OBJ_TYPE::JUMPWALL);
	
}

void CToolScene::Exit()
{
	
	

	// 메뉴바 제거

	

	//DeleteAllObject();
	SetMenu(CCore::GetInst()->GetHwnd(), nullptr);
	CCore::GetInst()->ChangeWindowSize(POINT{ 10, 10 }, POINT{ WIN_X, WIN_Y }, false);
}

bool compare2(CObj* a, CObj* b)
{
	if (a->GetPos().y == b->GetPos().y)
	{
		if (a->GetObjtype() == OBJ_TYPE::PLAYER)
			return  true;
		
	}
	return a->GetPos().y < b->GetPos().y;
}
void CToolScene::update()
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
							std::sort(begin, end, compare2);
						}
					}
					vecObj[j]->update();

				}
			}
		}		
	}

	KeyCheck();
}

void CToolScene::lateupdate()
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

void CToolScene::finalupdate()
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

void CToolScene::render(HDC _dc)
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();



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

			for (; iter != vecObj.end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = vecObj.erase(iter);
				}
				else
				{
					/*if(i == (UINT)OBJ_TYPE::UI)
						(*iter)->render(_dc);*/
					//(*iter)->colliderrender(_dc);
					++iter;
				}
			}
			
		}
		
	}
	vector<CObj*>::const_iterator iter = m_arrObjRender.begin();
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
				(*iter)->colliderrender(_dc);
			}
			++iter;
		}
	}
	vector<CObj*>& vecObj = m_arrObj[(int)OBJ_TYPE::UI];

	for (size_t i = 0; i < vecObj.size(); i++)
	{
		if (!vecObj[i]->IsDead())
			vecObj[i]->render(_dc);
	}
	switch (m_MouseUiType)
	{
	case UI_TYPE::TILE:
	{
		int iColMax = m_pTex->Width() / TILE_SIZE;
		int iRowMax = m_pTex->Height() / TILE_SIZE;
		int iMaxImgIdx = iColMax * iRowMax;
		if (iMaxImgIdx > m_MouseimNum && m_MouseimNum >= 0)
		{
			int iRow = m_MouseimNum / iColMax;
			int iCol = m_MouseimNum % iColMax;

			BitBlt(_dc
				, (int)vMousePos.x - 32, (int)vMousePos.y - 32
				, TILE_SIZE, TILE_SIZE
				, m_pTex->GetDC()
				, iCol * TILE_SIZE
				, iRow * TILE_SIZE
				, SRCCOPY);
		}
	}
	break;
	case UI_TYPE::TILE2:
	{
		int iColMax = m_pTex2->Width() / TILE_SIZE;
		int iRowMax = m_pTex2->Height() / TILE_SIZE;
		int iMaxImgIdx = iColMax * iRowMax;
		if (iMaxImgIdx > m_MouseimNum && m_MouseimNum >= 0)
		{
			int iRow = m_MouseimNum / iColMax;
			int iCol = m_MouseimNum % iColMax;

			BitBlt(_dc
				, (int)vMousePos.x - 32, (int)vMousePos.y - 32
				, TILE_SIZE, TILE_SIZE
				, m_pTex2->GetDC()
				, iCol * TILE_SIZE
				, iRow * TILE_SIZE
				, SRCCOPY);
		}
	}
	break;

	case UI_TYPE::OBJECT:
		int iColMax = m_pTex3->Width() / TILE_SIZE;
		int iRowMax = m_pTex3->Height() / TILE_SIZE;
		int iMaxImgIdx = iColMax * iRowMax;
		if (iMaxImgIdx > m_MouseimNum && m_MouseimNum >= 0)
		{
			int iRow = m_MouseimNum / iColMax;
			int iCol = m_MouseimNum % iColMax;

			BitBlt(_dc
				, (int)vMousePos.x - 32, (int)vMousePos.y - 32
				, TILE_SIZE, TILE_SIZE
				, m_pTex3->GetDC()
				, iCol * TILE_SIZE
				, iRow * TILE_SIZE
				, SRCCOPY);
		}
		break;

	}
	
}

void CToolScene::KeyCheck()
{
	if (KEY_TAP(KEY_TYPE::LBTN))
	{
		if (m_MouseUiType == UI_TYPE::OBJECT)
		{
			Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
			vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

			CTexture* pTileTex = CResMgr::GetInst()->FindTexture(L"TILE");
			CTexture* pTileTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
			int iCol = (int)vMousePos.x / TILE_SIZE;
			int iRow = (int)vMousePos.y / TILE_SIZE;

			if (0.f < vMousePos.x && iCol < (int)GetXCount()
				&& 0.f < vMousePos.y && iRow < (int)GetYCount() && !UIMouseOnCheck())
			{
				const vector<CObj*>& vecTile = GetObjects(OBJ_TYPE::TILE);
				int iIdx = iRow * (int)GetXCount() + iCol;

				CTile* pTile = dynamic_cast<CTile*>(vecTile[(size_t)iIdx]);
				assert(pTile);
				if (m_MouseUiType == UI_TYPE::OBJECT) {
					if (m_MouseimNum >= 0 && m_MouseimNum < 39)
					{
						if (pTile->GetObjectOn())
						{
							pTile->SetObjectOn(false);
							DeleteObject(pTile->GetpObject());
							pTile->SetpObject(nullptr);
							pTile->SetpObjectNum(OBJECTSNAME::NONE);
						}
						else
						{
							CObj* ob = CObjectMgr::GetInst()->objectspawn((OBJECTSNAME)m_MouseimNum);
							pTile->SetpObjectNum((OBJECTSNAME)m_MouseimNum);
							ob->SetPos(pTile->GetPos());
							pTile->SetObjectOn(true);
							pTile->SetpObject(ob);
							OBJ_TYPE a = ob->GetObjtype();
							AddObj(ob, ob->GetObjtype());
						}
					}
				}
			}
		}
	}
	if (KEY_HOLD(KEY_TYPE::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		CTexture* pTileTex = CResMgr::GetInst()->FindTexture(L"TILE");
		CTexture* pTileTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f < vMousePos.x && iCol < (int)GetXCount()
			&& 0.f < vMousePos.y && iRow < (int)GetYCount() && !UIMouseOnCheck())
		{
			const vector<CObj*>& vecTile = GetObjects(OBJ_TYPE::TILE);
			int iIdx = iRow * (int)GetXCount() + iCol;

			CTile* pTile = dynamic_cast<CTile*>(vecTile[(size_t)iIdx]);
			assert(pTile);
			
			switch (m_MouseUiType)
			{
			case UI_TYPE::TILE:
				if (m_MouseimNum >= 0 && m_MouseimNum < Tile1num)
				{
					if (!m_2TileOn)
					{
						pTile->SetImgIdx(m_MouseimNum);
						pTile->SetranderTile(m_MouseUiType);
						if (pTile->Get2Tile() != nullptr)
						{
							DeleteObject(pTile->Get2Tile());
							pTile->Set2tileOn(false);
							pTile->Set2tile(nullptr);
						}
						
					}
					else
					{
						/*CTile* p2Tile = new CTile;

						Vec2 vPos = pTile->GetPos();
						p2Tile->SetPos(vPos);
						p2Tile->SetTileTex(pTileTex, pTileTex2);
						p2Tile->SetImgIdx(m_MouseimNum);
						p2Tile->SetranderTile(m_MouseUiType);

						AddObj(p2Tile, OBJ_TYPE::TILE);
						if (pTile->Get2Tile() != nullptr)
							DeleteObject(pTile->Get2Tile());
						pTile->Set2tile(p2Tile);
						pTile->Set2tileOn(true);
						*/
						pTile->SetImgIdx(m_MouseimNum);
						pTile->SetranderTile(m_MouseUiType);
						if (pTile->Get2Tile() != nullptr)
						{
							DeleteObject(pTile->Get2Tile());
							pTile->Set2tileOn(false);
							pTile->Set2tile(nullptr);
						}
					}
				}
			break;
			case UI_TYPE::TILE2:
				if (m_MouseimNum >= 0 && m_MouseimNum < 46)
				{
					if (!m_2TileOn)
					{
						pTile->SetImgIdx(m_MouseimNum);
						pTile->SetranderTile(m_MouseUiType);
						pTile->Set2tileOn(false);

					}
					else
					{
						if (pTile->Get2Tile() != nullptr)
						{
							DeleteObject(pTile->Get2Tile());
						}
						CTile* p2Tile = new CTile;

						Vec2 vPos = pTile->GetPos();
						p2Tile->SetPos(vPos);
						p2Tile->SetTileTex(pTileTex, pTileTex2);
						p2Tile->SetImgIdx(m_MouseimNum);
						p2Tile->SetranderTile(m_MouseUiType);

						//AddObj(p2Tile, OBJ_TYPE::TILE);
						
							
						pTile->Set2tile(p2Tile);
						pTile->Set2tileOn(true);
					}
				}
				break;
			case UI_TYPE::OBJECT:
			{
			
			}
				break;
			case UI_TYPE::SAVE:
				break;
			case UI_TYPE::LOAD:
				break;
			}
			
			
		}
	}
	if (KEY_TAP(KEY_TYPE::RBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		CTexture* pTileTex = CResMgr::GetInst()->FindTexture(L"TILE");
		CTexture* pTileTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f < vMousePos.x && iCol < (int)GetXCount()
			&& 0.f < vMousePos.y && iRow < (int)GetYCount() && !UIMouseOnCheck())
		{
			const vector<CObj*>& vecTile = GetObjects(OBJ_TYPE::TILE);
			int iIdx = iRow * (int)GetXCount() + iCol;

			CTile* pTile = dynamic_cast<CTile*>(vecTile[(size_t)iIdx]);
			assert(pTile);
			
			
			if (m_colliderOn == true)
			{
				pTile->ColliderOn();
			}
		}
		
		
	}
	if (KEY_TAP(KEY_TYPE::ENTER))
	{
		CCamera::GetInst()->FadeOut(0.2f);
		CCamera::GetInst()->FadeIn(0.2f);
		CCamera::GetInst()->FadeOut(0.2f);
		CCamera::GetInst()->FadeIn(0.2f);

		ChangeScene(SCENE_TYPE::BATTLE);
	}
}

bool CToolScene::UIMouseOnCheck()
{
	const vector<CObj*>& vecUI = GetObjects(OBJ_TYPE::UI);
	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pParentUI = (CUI*)vecUI[i];
		if (pParentUI->IsMouseOn())
			return true;
	}
	return false;
}

void CToolScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	// Tile Object 삭제
	DeleteGroup(OBJ_TYPE::TILE);

	// 타일 가로 세로 개수 설정
	SetTileCount(_iXCount, _iYCount);

	// 타일이 참조할 텍스쳐 로드
	CTexture* pTileTex = CResMgr::GetInst()->FindTexture(L"TILE");
	CTexture* pTileTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
	// 타일 생성 및 Scene 에 추가
	for (UINT i = 0; i < GetYCount(); ++i)
	{
		for (UINT j = 0; j < GetXCount(); ++j)
		{
			CTile* pTile = new CTile;

			Vec2 vPos = Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE));		
			pTile->SetPos(vPos);
			pTile->SetTileTex(pTileTex, pTileTex2);
			pTile->SetImgIdx(138);

			AddObj(pTile, OBJ_TYPE::TILE);
		}
	}
}

void CToolScene::TileUpdate(int _iUpdate)
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
		

	/*for (; iter != vecObj.end(); )
	{
		if ((*iter)->IsDead())
		{
			iter = vecObj.erase(iter);
		}
		else
		{
			if (_iUpdate == 0)
			{
				(*iter)->update();
				++iter;
			}
			else if (_iUpdate == 1)
			{
				(*iter)->lateupdate();
				++iter;
			}
			else if (_iUpdate == 2)
			{
				(*iter)->finalupdate();
				++iter;
			}
			else
			{
				(*iter)->render(CCore::GetInst()->GetMemDC());
				(*iter)->colliderrender(CCore::GetInst()->GetMemDC());
				++iter;
			}
		}
	}*/

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
			vecTile[idx]->colliderrender(CCore::GetInst()->GetMemDC());
			}
		}
	}
	
}


// ==================
// Tile Info Save
// ==================
void SaveTile()
{
	OPENFILENAME ofn = {};       // common dialog box structure
	wchar_t szFile[260] = { 0 };       // if using TCHAR macros

	wstring strMapFilePath = CPathMgr::GetResPath();
	strMapFilePath += L"Tile\\";

	// Initialize OPENFILENAME	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetHwnd();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0타일\0*.tile\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strMapFilePath.c_str(); // 탐색창 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetSaveFileName(&ofn);
	wstring strOutput = ofn.lpstrFile;

	// 타일 정보 저장
	// 파일 열기
	FILE* pFile = nullptr;

	// 쓰기모드
	// 파일이 있으면 덮어쓰고, 없으면 만든다.
	_wfopen_s(&pFile, strOutput.c_str(), L"wb"); 

	// 파일 열기 실패
	if (nullptr == pFile)
	{
		MessageBox(nullptr, L"타일 저장 실패", L"에러", MB_OK);
		return;
	}
	
	// 타일 정보 저장
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 타일 가로 세로 개수 저장
	UINT xcount = pCurScene->GetXCount();
	UINT ycount = pCurScene->GetYCount();

	fwrite(&xcount , sizeof(UINT), 1, pFile );
	fwrite(&ycount, sizeof(UINT), 1, pFile);

	// 타일 개별 정보 저장
	const vector<CObj*>& vecTile = pCurScene->GetObjects(OBJ_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}
	
	fclose(pFile);
}

void LoadTile()
{
	OPENFILENAME ofn = {};       // common dialog box structure
	wchar_t szFile[260] = { 0 };       // if using TCHAR macros

	wstring strMapFilePath = CPathMgr::GetResPath();
	strMapFilePath += L"Tile\\";

	// Initialize OPENFILENAME	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = CCore::GetInst()->GetHwnd();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0이미지\0*.bmp\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strMapFilePath.c_str(); // 탐색창 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);
	wstring strOutput = ofn.lpstrFile;

	// 파일 읽기
	FILE* pFile = nullptr;

	// 파일을 읽기 모드로 연다(실제 파일이 없으면 실패)
	_wfopen_s(&pFile, strOutput.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(nullptr, L"파일이 존재하지 않습니다.", L"타일 불러오기 실패", MB_OK);
		return;
	}

	CToolScene* pCurScene = dynamic_cast<CToolScene*>(CSceneMgr::GetInst()->GetCurScene());
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
}




// =======================
// Create Tile Dialog Proc
// =======================
INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{	
		if (LOWORD(wParam) == IDOK)
		{
			int xcount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			int ycount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);			

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->CreateTile(xcount, ycount);

			EndDialog(hDlg, IDOK);

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, IDCANCEL);
			return (INT_PTR)TRUE;
		}
	}
		break;
	}
	return (INT_PTR)FALSE;
}