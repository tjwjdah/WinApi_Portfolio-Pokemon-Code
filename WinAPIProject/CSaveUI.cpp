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
	strOutput += L".tile";
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

	fwrite(&xcount, sizeof(UINT), 1, pFile);
	fwrite(&ycount, sizeof(UINT), 1, pFile);

	// 타일 개별 정보 저장
	const vector<CObj*>& vecTile = pCurScene->GetObjects(OBJ_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}
