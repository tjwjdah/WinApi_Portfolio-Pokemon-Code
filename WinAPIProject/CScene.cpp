#include "stdafx.h"
#include "CScene.h"

#include "CObj.h"
#include "CTile.h"

#include "CCore.h"
#include "Resource.h"
#include "CResMgr.h"
#include "CCamera.h"


CScene::CScene()
	: m_iXCount(0)
	, m_iYCount(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (nullptr != m_arrObj[i][j])
			{
				if(m_arrObj[i][j])
				delete m_arrObj[i][j];
			}
		}
	}

}

void CScene::update()
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
				if (!m_arrObj[i][j]->IsDead())
					m_arrObj[i][j]->update();
			}
		}
	}
	
}

void CScene::lateupdate()
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
				if (!m_arrObj[i][j]->IsDead())
					m_arrObj[i][j]->lateupdate();
			}
		}
	}
}

void CScene::finalupdate()
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
				if (!m_arrObj[i][j]->IsDead())
					m_arrObj[i][j]->finalupdate();
			}
		}
	}

}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (i == (UINT)OBJ_TYPE::TILE)
		{
			
			TileUpdate(3);
		}
		else
		{
			vector<CObj*>& vecObj = m_arrObj[i];
			vector<CObj*>::iterator iter = vecObj.begin();

			for (; iter != vecObj.end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = vecObj.erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}
void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	// Tile Object 삭제
	DeleteGroup(OBJ_TYPE::TILE);

	// 타일 가로 세로 개수 설정
	SetTileCount(_iXCount, _iYCount);

	// 타일이 참조할 텍스쳐 로드
	CTexture* pTileTex = CResMgr::GetInst()->FindTexture(L"TILE");
	if (nullptr == pTileTex)
		pTileTex = CResMgr::GetInst()->LoadTexture(L"TILE", L"Texture\\TILE.bmp");
	CTexture* pTileTex2 = CResMgr::GetInst()->FindTexture(L"2tile_a");
	if (nullptr == pTileTex2)
	{
		pTileTex2 = CResMgr::GetInst()->LoadTexture(L"2tile_a", L"Texture//2tile_a.bmp");
	}
	// 타일 생성 및 Scene 에 추가
	for (UINT i = 0; i < GetYCount(); ++i)
	{
		for (UINT j = 0; j < GetXCount(); ++j)
		{
			CTile* pTile = new CTile;

			Vec2 vPos = Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE));
			pTile->SetPos(vPos);
			pTile->SetTileTex(pTileTex,pTileTex2);
			pTile->SetImgIdx(0);

			AddObj(pTile, OBJ_TYPE::TILE);

		}
	}
}

void CScene::TileUpdate(int _iUpdate)
{
	const vector<CObj*> vecTile = GetObjects(OBJ_TYPE::TILE);
	//vector<CObj*>& vecObj = m_arrObj[(INT)OBJ_TYPE::TILE];
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
				vecTile[idx]->render(CCore::GetInst()->GetMemDC());
		}
	}
}

void CScene::DeleteGroup(OBJ_TYPE _eType)
{
	vector<CObj*>& vecObj = m_arrObj[(UINT)_eType];

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		assert(vecObj[i]);
		delete vecObj[i];
	}

	vecObj.clear();
}

void CScene::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		DeleteGroup((OBJ_TYPE)i);
	}
}


#include "CUI.h"
bool Ycompare(CObj* a, CObj* b)
{
	//y값 기준으로 비교
	return a->GetPos().y < b->GetPos().y;
}

void CScene::AddObj(CObj* _pObj, OBJ_TYPE _eType)
{
	if (OBJ_TYPE::UI == _eType)
	{
		CUI* pUI = dynamic_cast<CUI*>(_pObj);
		assert(pUI);
	}

	m_arrObj[(UINT)_eType].push_back(_pObj);
	if (OBJ_TYPE::UI != _eType && OBJ_TYPE::TILE  != _eType)
	{
		m_arrObjRender.push_back(_pObj);
		vector<CObj*>::iterator begin = m_arrObjRender.begin();
		vector<CObj*>::iterator end = m_arrObjRender.end();
		//y값 기준으로 객체를 정렬시킴
		std::sort(begin, end, Ycompare);
	}
	int a = 0;
}



void CScene::SetFocusedUI(CObj* _pFocuedUI)
{
	vector<CObj*>::iterator iter = m_arrObj[(UINT)OBJ_TYPE::UI].begin();
	for (; iter != m_arrObj[(UINT)OBJ_TYPE::UI].end() ; ++iter)
	{
		if (*iter == _pFocuedUI)
		{
			m_arrObj[(UINT)OBJ_TYPE::UI].erase(iter);
			m_arrObj[(UINT)OBJ_TYPE::UI].push_back(_pFocuedUI);
			return;
		}
	}

	assert(nullptr);
}



