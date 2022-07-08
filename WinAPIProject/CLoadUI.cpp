#include "stdafx.h"
#include "CLoadUI.h"

#include "CToolScene.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include  "CCore.h"
#include "CTile.h"

CLoadUI::CLoadUI()
{
}

CLoadUI::~CLoadUI()
{
}

void CLoadUI::MouseLBTNDown(Vec2 _vMousePos)
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
	ofn.lpstrFilter = L"All\0*.*\0Ÿ��\0*.tile\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strMapFilePath.c_str(); // Ž��â �ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);
	wstring strOutput = ofn.lpstrFile;

	// ���� �б�
	FILE* pFile = nullptr;

	// ������ �б� ���� ����(���� ������ ������ ����)
	_wfopen_s(&pFile, strOutput.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(nullptr, L"������ �������� �ʽ��ϴ�.", L"Ÿ�� �ҷ����� ����", MB_OK);
		return;
	}

	CToolScene* pCurScene = dynamic_cast<CToolScene*>(CSceneMgr::GetInst()->GetCurScene());
	assert(pCurScene);

	// Ÿ�� ���� ���� ���� �б�
	UINT xcount = 0;
	UINT ycount = 0;

	fread(&xcount, sizeof(UINT), 1, pFile);
	fread(&ycount, sizeof(UINT), 1, pFile);
	CScene* Scene = CSceneMgr::GetInst()->GetCurScene();
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		if (OBJ_TYPE::UI == (OBJ_TYPE)i || OBJ_TYPE::PLAYER == (OBJ_TYPE)i)
			continue;
		Scene->DeleteGroup((OBJ_TYPE)i);
	}
	pCurScene->CreateTile(xcount, ycount);

	// ������ Ÿ�� ���� ����
	const vector<CObj*>& vecTile = pCurScene->GetObjects(OBJ_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}
}
