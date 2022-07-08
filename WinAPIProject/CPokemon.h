#pragma once
#include "CObj.h"

class CTexture;
class CSkill;

class CPokemon :
    public CObj
{
public:
    CPokemon();
    ~CPokemon();
    CPokemon(const CPokemon& _origin);
private:
    int    m_pLv;   
    int    m_exp;
    int    m_maxexp;
    int    m_dropexp;

    HABCDS m_pHABCDS;
   
    int  mMax_hp;
    int  mHp;
    int  m_attack;
    int  m_block;
    int  m_contact;
    int  m_defence;
    int  m_speed;




    int m_skillamount;

    int  m_battlerank;

    POKEMON_TYPE m_pType;
    POKEMON_TYPE m_pType2;

    CTexture* m_pTex;
    CTexture* m_pTex2;

    CSkill* m_pSkill1;
    CSkill* m_pSkill2;
    CSkill* m_pSkill3;
    CSkill* m_pSkill4;

    wstring m_pName;

    bool m_Playerown;

    int m_posx;


    bool m_showon;
public:
    void LvUp();

    void SetHABCDS(HABCDS _habcds) { m_pHABCDS = _habcds; }
    void SetLv(int _Lv);
    void SetName(const wstring& _strKey) { m_pName = _strKey; }
    void SetHp(int _Hp) { mHp = _Hp; }


    void SetTex1(CTexture* _Tex) { m_pTex = _Tex; }
    void SetTex2(CTexture* _Tex2) { m_pTex2 = _Tex2; }
    void SetType(POKEMON_TYPE _pType1, POKEMON_TYPE _pType2 = POKEMON_TYPE::NONE) { m_pType = _pType1; m_pType2 = _pType2; }
    void SetPlayerown(bool _playerown) { m_Playerown = _playerown; }
    void SetSkill(CSkill* _skill1, CSkill* _skill2 = nullptr, CSkill* _skill3 = nullptr, CSkill* _skill4=nullptr){ 
        m_pSkill1 = _skill1;
        m_pSkill2 = _skill2;
        m_pSkill3 = _skill3;
        m_pSkill4 = _skill4;
    }

    void SetSkill2(CSkill* _skill2) { m_pSkill2 = _skill2; }
    void SetSkill3(CSkill* _skill3) { m_pSkill3 = _skill3; }
    void SetSkill4(CSkill* _skill4) { m_pSkill4 = _skill4; }
    void Damage(int _damage) { mHp = mHp - _damage; if (mHp < 0) mHp = 0; }
    void expup(int _exp) { m_exp += _exp; }

    void SetShow(bool _show) { m_showon = _show; }

    int GetLv() { return m_pLv; }
    int Getm_maxhp() { return mMax_hp; }
    int GetmHP() { return mHp; }
    int GetAttack() { return m_attack; }
    int Getblock() { return m_block; }
    int Getcontact() { return m_contact; }
    int Getdefence() { return m_defence; }
    int Getbattlerank() { return m_battlerank; }
    int GetDropexp() { return m_dropexp; }
    int Getexpmax() { return m_maxexp; }
    int Getexp() { return m_exp; }
    int GetSpeed() { return m_speed; }

    CSkill* GetSkill1() { return m_pSkill1; }
    CSkill* GetSkill2() { return m_pSkill2; }
    CSkill* GetSkill3() { return m_pSkill3; }
    CSkill* GetSkill4() { return m_pSkill4; }

    POKEMON_TYPE GetPokemonType1() { return m_pType; }
    POKEMON_TYPE GetPokemonType2() { return m_pType2; }
    wstring GetpName() { return m_pName; }
    bool    GetPlayerown() { return m_Playerown; }
    int     Getskillamount();

    CTexture* GetTexture() { return m_pTex; }
public:
    virtual void init();
    virtual void update();
    virtual void render(HDC _dc);

    virtual CPokemon* Clone() { return new CPokemon(*this); }
};

