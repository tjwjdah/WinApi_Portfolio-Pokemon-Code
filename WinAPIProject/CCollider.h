#pragma once

class CObj;

class CCollider
{
private:
	static	UINT	g_iColliderNextID;

private:
	CObj*	m_pObject;
	Vec2	m_vScale;
	Vec2	m_vOffsetPos;
	Vec2	m_vFinalPos;
	int		m_iCollisionCount;

	DIR     m_CollisionDir;

	UINT	m_iColliderID;

	COLLIDER_TYPE m_eType;
	PEN_TYPE	m_ePen;

	
public:
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }

	Vec2 GetFinalPos() { return m_vFinalPos; }
	UINT GetColliderID() { return m_iColliderID; }

	void SetColliderType(COLLIDER_TYPE _eType) { m_eType = _eType; }
	COLLIDER_TYPE GetColliderType() { return m_eType; }

	void SetCRPen(PEN_TYPE _C) { m_ePen = _C; }
	CObj* GetObj() { return m_pObject; }


	void SetDir(DIR _Dir) { m_CollisionDir = _Dir; };
	DIR  GetDir() { return m_CollisionDir; }

public:
	void render(HDC _dc);
	void finalupdate();

public:
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

public:
	void operator = (const CCollider& _origin)
	{
		m_pObject = nullptr;
		m_vScale = _origin.m_vScale;
		m_vOffsetPos = _origin.m_vOffsetPos;
		m_vFinalPos = _origin.m_vFinalPos;
		m_eType = _origin.m_eType;
		m_iColliderID = g_iColliderNextID++;		
	}

	CCollider* Clone() { return new CCollider(*this); }

public:
	CCollider();
	~CCollider();

private:
	CCollider(const CCollider& _Origin);

	friend class CObj;
};

