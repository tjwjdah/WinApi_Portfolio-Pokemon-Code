#pragma once

#define SINGLE(type) public: \
						static type* GetInst()\
						{\
							static type inst;\
							return &inst;\
						}\
					private:\
						type();\
						~type();


#define KEY_CHECK(key, state) state == CKeyMgr::GetInst()->GetKeyState(key)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define fDT CTimeMgr::GetInst()->GetfDT()

#define WIN_X 960
#define WIN_Y 640

#define TILE_SIZE 64

#define PPOKEMONX 160
#define PPOKEMONY 232
#define OPOKEMONX 588
#define OPOKEMONY 88

enum class SCENE_TYPE
{
	TOOL,
	START,
	BATTLE,
	SWAP,
	TRAINERBATTLE,
	OP,
	ED,
	END,
};

enum class OBJ_TYPE
{
	TILE = 0,
	DEFAULT,	
	PLAYER,
	POKEMON,
	BASEOBJECT,
	HOUSE,
	DOOR,
	CHANGPLACEOBJ,
	POKEMONSPAWNOBJ,
	JUMPWALL,
	TRAINER,
	NURSE,
	NPC,
	ITEM,
	UI = 31,
	END = 32,
};

enum class PEN_TYPE
{
	GREEN,
	RED,
	BLUE,
	END,
};

enum class COLLIDER_TYPE
{
	RECT,
	CIRCLE,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

enum class DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
};


enum class UI_TYPE
{
	DEFAULT = 0,
	TILE,
	TILE2,
	TEXT,
	BUTTON,
	OBJECT,
	SAVE,
	LOAD,
	END
};

enum class BUTTON_TYPE {
	DEFAULT = 0,
	TYP
};

enum class POKEMON_TYPE {
	DEFAULT = 0,
	NORMAL,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	ICE,
	FIGHTING,
	POISON,
	GROUND,
	FLYING,
	PSYCHIC,
	BUG,
	ROCK,
	GHOST,
	DRAGON,
	DARK,
	STEEL,
	FAIRY,
	NONE
};



enum class SKILL_CATEGORY {
	DEFAULT = 0,
	PHYSICAL,
	SPECIAL,
	STATUS
};