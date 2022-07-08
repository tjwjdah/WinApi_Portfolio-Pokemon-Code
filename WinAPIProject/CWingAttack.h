#pragma once
#include "CSkill.h"
class CWingAttack :
    public CSkill
{
public:
    CWingAttack();
    ~CWingAttack();
    CWingAttack(const CWingAttack& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CWingAttack* Clone() { return new CWingAttack(*this); };
};

