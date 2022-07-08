#pragma once


class CScene;
class CTrainerBattle;
class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurScene;
	


public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void ChangeScene(SCENE_TYPE _eNextScene, float _Time = 0.f);

public:
	CScene* GetCurScene() { return m_pCurScene; }
	CScene* GetBattleScene() { return m_arrScene[(UINT)SCENE_TYPE::BATTLE]; }
	CScene* GetTrainerBattle() { return m_arrScene[(UINT)SCENE_TYPE::TRAINERBATTLE]; }
	friend class CEventMgr;
};

