#pragma once

struct Vec2
{
	float x;
	float y;

	Vec2()
		: x(0.f), y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

public:
	float length()
	{
		return (float)sqrt((pow((double)x, 2) + pow((double)y, 2)));
	}

	void normalize()
	{
		float fLen = length();

		assert(fLen);

		x /= fLen;
		y /= fLen;
	}

	bool IsZero()
	{
		return  (x == 0.f && y == 0.f) ?  true : false;
	}

public:
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2& operator -()
	{
		x *= -1;
		y *= -1;
		return *this;
	}
	
	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);		
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator * (Vec2 _vOther)
	{		
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (float _f)
	{		
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(_vOther.x != 0 && _vOther.y != 0);	

		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator / (float _f)
	{
		assert(_f != 0 );

		return Vec2(x / _f, y / _f);
	}

	bool operator != (Vec2 _vOther)
	{
	
		if (x == _vOther.x && y == _vOther.y)
			return false;
		else
			return true;
	}
	bool operator == (Vec2 _vOther)
	{
		if (x == _vOther.x && y == _vOther.y)
			return true;
		else
			return false;
	
	}
};

class CTexture;
struct tAnimFrame
{
	CTexture*	pTargetTex;	
	Vec2		vLT;
	Vec2		vSliceSize;
	Vec2		vOffset;
	float		fDuration;
};


struct tEvent
{
	EVENT_TYPE	eEvent;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
	float		dTime;
	float       cTime = 0.f;
};

struct HABCDS
{
	int Hp;
	int Attack;
	int Block;
	int Contact;
	int Defence;
	int Speed;
	HABCDS() :Hp(0), Attack(0), Block(0), Contact(0), Defence(0), Speed(0)
	{}
	HABCDS(int _hp, int _attack, int _block, int _contact, int _defence, int _speed ) :Hp(_hp), Attack(_attack), Block(_block), Contact(_contact), Defence(_defence), Speed(_speed)
	{}
	
};
