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
	// UI �׷� ��������
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObj*>& vecUI = pCurScene->GetObjects(OBJ_TYPE::UI);

	// ���콺 ��ǥ ��������
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	// ���콺 ���� üũ
	bool bLBTNTap = KEY_TAP(KEY_TYPE::LBTN);
	bool bLBTNUp = KEY_AWAY(KEY_TYPE::LBTN);
	
	CUI* pNewFocuedUI = m_pFocusedUI;

	int i = (int)vecUI.size() - 1;
	for (; i >= 0; --i)
	{
		CUI* pParentUI = (CUI*)vecUI[i];
	
		// �̺�Ʈ�� ���� �� UI ã��(�θ� UI �� ������ �ִ� ChildUI ����, �˻�����)
		CUI* pTargetUI = GetTargetUI(pParentUI, vMousePos);

		if (nullptr == pTargetUI)
			continue;
		
		pTargetUI->MouseOn(vMousePos);

		if (bLBTNTap)
		{
			pTargetUI->MouseLBTNDown(vMousePos);

			// Focus ����
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
		// ���ο� UI �� Focus �Ǿ���
		// Scene UI �׷� ������ ������ �ٲ��� �Ѵ�.
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
		UI�� ���콺�� �÷����ִٸ�
		Ÿ�� UI�� ������ �ִ� �ڽĵ��� ����Ʈ�� ������
		�ڽ� UI���� ���콺�� �÷����ִ��� �˻�
		�ݺ� �� ���������� ��ȯ �� Ÿ�� UI�� ã��
		*/
	}

	return pTargetUI;
}
