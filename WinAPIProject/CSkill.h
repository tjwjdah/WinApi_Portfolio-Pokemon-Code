#pragma once
#include "CObj.h"

class CPokemon;
class CSkill :
    public CObj
{   
public:
    CSkill();
    ~CSkill();
    CSkill(const CSkill& _origin);

protected:
    CPokemon*       m_iPokemon;
    CPokemon*       m_oPokemon;
    POKEMON_TYPE    m_skillType;
    SKILL_CATEGORY  m_skillcategory;
    wstring         m_skillname;
    
    CTexture*       m_skilleffect;
    
    int             m_damage;
    int             m_Accuracy;
    int             m_pp;
    int             m_ppMax;
    int             m_effect_text;

    int             m_damagecount;
    


    float           m_time;
    bool            m_skillon;
    bool            m_textpush;
    bool            m_textpush2;
public:
    virtual int Damagecount(CPokemon* _iPokemon, CPokemon* _oPokemon);
    virtual void SkillText();
    virtual void SkillUse();
    virtual CSkill* Clone() { return new CSkill(*this); };

public:

    void Settarget(CPokemon* _iPokemon, CPokemon* _oPokemon) { m_iPokemon = _iPokemon; m_oPokemon = _oPokemon; }
    
    void skillon(bool _skillon) { m_skillon = _skillon; }

    wstring GetSkillname() { return m_skillname; }
    int GetSkillpp() { return m_pp; }
    int GetSkillppMax() { return m_ppMax; }

    POKEMON_TYPE GetSkillType() { return m_skillType; }
    wstring GetSkillType_ToString();
};

