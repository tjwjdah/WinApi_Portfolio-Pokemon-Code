#include "stdafx.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CSceneMgr.h"
#include "CObjectMgr.h"
#include "CScene.h"


#include "CHouse.h"
#include "CDoor.h"

#include "CKeyMgr.h"
CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(-1)
	, m_pTileTex2(nullptr)
	, m_p2TileOn(false)
	, m_randerTile(UI_TYPE::TILE)
	, m_p2Tile(nullptr)
	, m_ObjectOn(false)
	, m_ObjectNum(OBJECTSNAME::NONE)
	, m_pObject(nullptr)
	, m_pColliderOn(false)
	, m_ShowVec(false)

{
	SetObjtype(OBJ_TYPE::TILE);
}

CTile::~CTile()
{
	if (m_p2Tile != nullptr)
		delete m_p2Tile;
}

void CTile::update()
{
	if (m_p2TileOn && m_p2Tile != nullptr)
	{
		if(!m_p2Tile->IsDead())
		m_p2Tile->update();
	}
	if (m_ObjectNum == OBJECTSNAME::NONE && m_pObject==nullptr)
		m_ObjectOn = false;

	if (KEY_TAP(KEY_TYPE::KEY_M))
	{
		if (m_ShowVec)
			m_ShowVec = false;
		else
			m_ShowVec = true;
	}

}

void CTile::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	if (nullptr == m_pTileTex)
	{
		HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);			

		Rectangle(_dc, (int)vRenderPos.x, (int)vRenderPos.y, (int)vRenderPos.x + TILE_SIZE, (int)vRenderPos.y + TILE_SIZE);

		SelectObject(_dc, hPrevBrush);
	}
	else
	{
		if (m_randerTile == UI_TYPE::TILE) {
			int iColMax = m_pTileTex->Width() / TILE_SIZE;
			int iRowMax = m_pTileTex->Height() / TILE_SIZE;
			int iMaxImgIdx = iColMax * iRowMax;

			if (iMaxImgIdx > m_iImgIdx)
			{
				int iRow = m_iImgIdx / iColMax;
				int iCol = m_iImgIdx % iColMax;

				BitBlt(_dc
					, (int)vRenderPos.x
					, (int)vRenderPos.y
					, TILE_SIZE, TILE_SIZE
					, m_pTileTex->GetDC()
					, iCol * TILE_SIZE
					, iRow * TILE_SIZE
					, SRCCOPY);
			}

			//Rectangle(_dc, (int)vRenderPos.x, (int)vRenderPos.y, (int)vRenderPos.x + TILE_SIZE, (int)vRenderPos.y + TILE_SIZE);
		}
		else if((m_randerTile == UI_TYPE::TILE2))
		{
			int iColMax = m_pTileTex2->Width() / TILE_SIZE;
			int iRowMax = m_pTileTex2->Height() / TILE_SIZE;
			int iMaxImgIdx = iColMax * iRowMax;

			BLENDFUNCTION ftn = {};

				ftn.BlendOp = AC_SRC_OVER;
				ftn.AlphaFormat = AC_SRC_ALPHA;
				ftn.SourceConstantAlpha = 255;


				if (iMaxImgIdx > m_iImgIdx)
				{
					int iRow = m_iImgIdx / iColMax;
					int iCol = m_iImgIdx % iColMax;
					AlphaBlend(_dc
						, (int)vRenderPos.x
						, (int)vRenderPos.y
						, TILE_SIZE
						, TILE_SIZE
						, m_pTileTex2->GetDC()
						, iCol * TILE_SIZE
						, iRow * TILE_SIZE
						, TILE_SIZE
						, TILE_SIZE
						, ftn);
				}
		}
	}	
	if (m_p2TileOn && m_p2Tile !=nullptr)
	{
		if (!m_p2Tile->IsDead())
			m_p2Tile->render(_dc);
	}
	if (m_ShowVec) {
		wstring strPath;
		int x = GetPos().x / 64;
		int y = GetPos().y / 64;
		strPath = std::to_wstring(x) + L"." + std::to_wstring(y);
		TextOut(_dc, vRenderPos.x, vRenderPos.y, strPath.c_str(), strPath.size());
	}
}
void CTile::ColliderOn()
{
	if (GetCollider() == nullptr && !m_pColliderOn)
	{
		CCollider* pCollider = new CCollider;
		pCollider->SetOffsetPos(Vec2(32.f, 32.f));
		pCollider->SetCRPen(PEN_TYPE::BLUE);
		pCollider->SetScale(Vec2(64.f, 64.f));
		AddCollider(pCollider);
		m_pColliderOn = true;
	}
	else
	{
		m_pColliderOn = false;
		deleteCollder();
	}
}

void CTile::Save(FILE* _pFile)
{
	// 텍스쳐 정보 저장(키값, 경로)
	bool bTileExist = true;
	if (nullptr == m_pTileTex)
		bTileExist = false;

	fwrite(&bTileExist, 1, 1, _pFile);
	
	if (bTileExist)
	{
		// 키값, 경로
		wstring strKey = m_pTileTex->GetKey();
		wstring strPath = m_pTileTex->GetRelativePath();
		wstring strKey2 = m_pTileTex2->GetKey();
		wstring strPath2 = m_pTileTex2->GetRelativePath();
		SaveWString(strKey, _pFile);
		SaveWString(strPath, _pFile);
		SaveWString(strKey2, _pFile);
		SaveWString(strPath2, _pFile);

		fwrite(&m_p2TileOn, 1, 1, _pFile);
		fwrite(&m_pColliderOn, sizeof(UI_TYPE), 1, _pFile);

		fwrite(&m_randerTile, sizeof(UI_TYPE), 1, _pFile);
		if (m_p2TileOn && !m_p2Tile->IsDead())
		{
			int Tile2ImagIdx = m_p2Tile->GetImgIdx();
			fwrite(&Tile2ImagIdx, sizeof(int), 1, _pFile);
		}
		else
		{
			int a = -1;
			fwrite(&a, sizeof(int), 1, _pFile);
		}

		fwrite(&m_ObjectOn, sizeof(int), 1, _pFile);
		fwrite(&m_ObjectNum, sizeof(OBJECTSNAME), 1, _pFile);
		

		// 인덱스
		fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
	}
}

void CTile::Load(FILE* _pFile)
{
	// 텍스쳐 정보 저장(키값, 경로)


	bool bTileExist = true;
	fread(&bTileExist, 1, 1, _pFile);

	if (bTileExist)
	{
		
		// 키값, 경로
		wstring strKey, strPath, strKey2, strPath2;
		bool Tile2On;
		int Tile2ImagIdx;
		LoadWString(strKey, _pFile);
		LoadWString(strPath, _pFile);
		LoadWString(strKey2, _pFile);
		LoadWString(strPath2, _pFile);
		m_pTileTex = CResMgr::GetInst()->FindTexture(strKey);
		if(nullptr == m_pTileTex)
			m_pTileTex = CResMgr::GetInst()->LoadTexture(strKey, strPath);
		m_pTileTex2 = CResMgr::GetInst()->FindTexture(strKey2);
		if (nullptr == m_pTileTex)
			m_pTileTex2 = CResMgr::GetInst()->LoadTexture(strKey2, strPath2);

		fread(&m_p2TileOn, 1, 1, _pFile);
		fread(&m_pColliderOn, sizeof(UI_TYPE), 1, _pFile);
			if (m_pColliderOn)
			{
				CCollider* pCollider = new CCollider;
				pCollider->SetOffsetPos(Vec2(32.f, 32.f));
				pCollider->SetCRPen(PEN_TYPE::BLUE);
				pCollider->SetScale(Vec2(64.f, 64.f));
				AddCollider(pCollider);
			}

		fread(&m_randerTile, sizeof(UI_TYPE), 1, _pFile);

		if (m_p2TileOn)
		{
			
			fread(&Tile2ImagIdx, sizeof(int), 1, _pFile);
			CTile* p2Tile = new CTile;
			Vec2 vPos = GetPos();
			p2Tile->SetPos(vPos);
			p2Tile->SetTileTex(m_pTileTex, m_pTileTex2);
			p2Tile->SetImgIdx(Tile2ImagIdx);
			p2Tile->SetranderTile(UI_TYPE::TILE2);

			Set2tile(p2Tile);
		}
		else
		{
			fread(&Tile2ImagIdx, sizeof(int), 1, _pFile);
		}
		
		fread(&m_ObjectOn, sizeof(int), 1, _pFile);
		
		fread(&m_ObjectNum, sizeof(OBJECTSNAME), 1, _pFile);
		if (m_ObjectOn)
		{
			CObj* ob = CObjectMgr::GetInst()->objectspawn(m_ObjectNum);
			ob->SetPos(GetPos());
			SetpObject(ob);
			
			OBJ_TYPE a = ob->GetObjtype();
			CScene* Scene = CSceneMgr::GetInst()->GetCurScene();
			Scene->AddObj(ob, ob->GetObjtype());
			
		}
		
		// 인덱스
		fread(&m_iImgIdx, sizeof(int), 1, _pFile);
	}
}
