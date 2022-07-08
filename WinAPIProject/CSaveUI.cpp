#include "stdafx.h"
#include "CSaveUI.h"

#include "CToolScene.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include  "CCore.h"
#include "CTile.h"

CSaveUI::CSaveUI()
{
}

CSaveUI::~CSaveUI()
{
}

void CSaveUI::MouseLBTNDown(Vec2 _vMousePos)
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

	GetSaveFileName(&ofn);
	wstring strOutput = ofn.lpstrFile;

	// Ÿ�� ���� ����
	// ���� ����
	FILE* pFile = nullptr;

	// ������
	// ������ ������ �����, ������ �����.
	strOutput += L".tile";
	_wfopen_s(&pFile, strOutput.c_str(), L"wb");

	// ���� ���� ����
	if (nullptr == pFile)
	{
		MessageBox(nullptr, L"Ÿ�� ���� ����", L"����", MB_OK);
		return;
	}

	// Ÿ�� ���� ����
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Ÿ�� ���� ���� ���� ����
	UINT xcount = pCurScene->GetXCount();
	UINT ycount = pCurScene->GetYCount();

	fwrite(&xcount, sizeof(UINT), 1, pFile);
	fwrite(&ycount, sizeof(UINT), 1, pFile);

	// Ÿ�� ���� ���� ����
	const vector<CObj*>& vecTile = pCurScene->GetObjects(OBJ_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}
