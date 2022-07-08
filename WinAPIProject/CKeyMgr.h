#pragma once

enum class KEY_STATE
{
	TAP,  // �� ���ȴ�.
	HOLD, // �������� ������ ���ݵ� �����ִ�
	AWAY, // �� �ô�
	NONE  // �ƹ��͵� �ƴ�
};

enum class KEY_TYPE
{
	KEY_W, // = 0
	KEY_S, // = 1
	KEY_A, // = 2
	KEY_D, // = 3
	KEY_Z,
	KEY_X,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,


	SPACE, 
	ENTER,

	LBTN,
	RBTN,

	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,

	END,
};

struct tKeyData
{
	KEY_STATE	eState;
	bool		bPress;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyData>	m_vecKey;
	POINT				m_ptMousePos;
	POINT				m_ptPrevMousePos;

public:
	void init();
	void update();

public:
	POINT GetMousePos() { return m_ptMousePos; }
	POINT GetPrevMousePos() { return m_ptPrevMousePos; }

public:
	KEY_STATE GetKeyState(KEY_TYPE _eType)
	{
		return m_vecKey[(UINT)_eType].eState;
	}

};

