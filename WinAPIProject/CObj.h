#pragma once

class CCollider;
class CAnimator;

class CObj
{
private:
	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;

	float		m_fMass;	// 질량
	Vec2		m_vForce;	// Object 에 누적된 힘	
	Vec2		m_vVelocity; // 속도

	bool		m_bDead;
	OBJ_TYPE    m_mObjtype;
private:
	void SetDead() { m_bDead = true; }

public:
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	void AddForce(Vec2 _vForce) { m_vForce += _vForce; }

	void AddCollider(CCollider* _pCollider);
	CCollider* GetCollider() { return m_pCollider; }
	void deleteCollder();
	void AddAnimator(CAnimator* _pAnimator);
	CAnimator* GetAnimator() { return m_pAnimator; }

	void SetObjtype(OBJ_TYPE _Objtype) {m_mObjtype = _Objtype;};
	OBJ_TYPE GetObjtype() {return m_mObjtype;}

	bool IsDead() { return m_bDead; }

	virtual void init() {}
	virtual void update();
	virtual void lateupdate();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	virtual void colliderrender(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	virtual CObj* Clone() = 0;


public:
	CObj();		
	virtual ~CObj();

protected:
	CObj(const CObj& _origin);

	friend class CEventMgr;
};

