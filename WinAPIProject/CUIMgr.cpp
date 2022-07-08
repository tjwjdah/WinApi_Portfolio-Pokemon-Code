#include "stdafx.h"
#include "CUIMgr.h"

#include "CUI.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// UI 그룹 가져오기
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObj*>& vecUI = pCurScene->GetObjects(OBJ_TYPE::UI);

	// 마우스 좌표 가져오기
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	// 마우스 상태 체크
	bool bLBTNTap = KEY_TAP(KEY_TYPE::LBTN);
	bool bLBTNUp = KEY_AWAY(KEY_TYPE::LBTN);
	
	CUI* pNewFocuedUI = m_pFocusedUI;

	int i = (int)vecUI.size() - 1;
	for (; i >= 0; --i)
	{
		CUI* pParentUI = (CUI*)vecUI[i];
	
		// 이벤트를 실행 할 UI 찾기(부모 UI 가 가지고 있는 ChildUI 포함, 검사진행)
		CUI* pTargetUI = GetTargetUI(pParentUI, vMousePos);

		if (nullptr == pTargetUI)
			continue;
		
		pTargetUI->MouseOn(vMousePos);

		if (bLBTNTap)
		{
			pTargetUI->MouseLBTNDown(vMousePos);

			// Focus 변경
			pNewFocuedUI = pParentUI;
		}
		else if (bLBTNUp)
		{
			pTargetUI->MouseLBTNUp(vMousePos);

			if (pTargetUI->m_bLBTNDown)
			{
				pTargetUI->MouseLBTNClicked(vMousePos);
			}
		}		

		break;
	}

	if (m_pFocusedUI != pNewFocuedUI)
	{
		// 새로운 UI 가 Focus 되었다
		// Scene UI 그룹 내에서 순서가 바뀌어야 한다.
		m_pFocusedUI = pNewFocuedUI;
		pCurScene->SetFocusedUI(m_pFocusedUI);
	}
}

CUI* CUIMgr::GetTargetUI(CUI* _pParentUI, Vec2 _vMousePos)
{
	list<CUI*> listTarget;
	listTarget.push_back(_pParentUI);

	CUI* pTargetUI = nullptr;

	while (!listTarget.empty())
	{
		CUI* pUI = listTarget.back();
		listTarget.pop_back();
		if (pUI->IsMouseOn())
		{

			listTarget.clear();

			pTargetUI = pUI;

			const vector<CUI*>& vecChildUI = pUI->GetChild();
			for (size_t i = 0; i < vecChildUI.size(); ++i)
			{
				if (vecChildUI[i]->GetUse())
				listTarget.push_front(vecChildUI[i]);
			}
		
		}
		/*
		UI에 마우스가 올려져있다면
		타겟 UI가 가지고 있는 자식들을 리스트에 넣은후
		자식 UI에도 마우스가 올려져있는지 검사
		반복 후 최종적으로 반환 할 타겟 UI를 찾음
		*/
	}

	return pTargetUI;
}
