#pragma once

class CObj;

class CTile;
class CScene
{
private:
	vector<CObj*>	m_arrObj[(UINT)OBJ_TYPE::END];
	vector<CObj*>	m_arrObjRender;
	UINT			m_iXCount;	// 타일 가로 개수
	UINT			m_iYCount;	// 타일 세로 개수


public:
	virtual void init(){}

	virtual void update();
	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);


	virtual void CreateTile(UINT _iXCount, UINT _iYCount);
	virtual void TileUpdate(int _iUpdate);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

protected:
	void DeleteGroup(OBJ_TYPE _eType);
	void DeleteAllObject();
	
	void SetTileCount(UINT _iXCount, UINT _iYCount)
	{
		m_iXCount = _iXCount; m_iYCount = _iYCount;
	}

public:
	UINT GetXCount() { return m_iXCount; }
	UINT GetYCount() { return m_iYCount; }

	void AddObj(CObj* _pObj, OBJ_TYPE _eType = OBJ_TYPE::DEFAULT);	

	const vector<CObj*>& GetObjects(OBJ_TYPE _eType) 
	{ 
		return m_arrObj[(UINT)_eType]; 
	}
	vector<CObj*>& GetObjects2(OBJ_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	void SetFocusedUI(CObj* _pFocuedUI);

	
public:
	CScene();
	virtual ~CScene();


	friend class CLoadUI;

	friend class CToolScene;
	friend class CStartScene;
};

