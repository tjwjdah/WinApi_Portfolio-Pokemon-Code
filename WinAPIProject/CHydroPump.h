#pragma once
#include "CSkill.h"
class CHydroPump :
    public CSkill
{
public:
    CHydroPump();
    ~CHydroPump();
    CHydroPump(const CHydroPump& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CHydroPump* Clone() { return new CHydroPump(*this); };
};

