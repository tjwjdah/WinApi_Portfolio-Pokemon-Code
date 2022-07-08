#pragma once
#include "CSkill.h"
class CFlamethrower :
    public CSkill
{
public:
    CFlamethrower();
    ~CFlamethrower();
    CFlamethrower(const CFlamethrower& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CFlamethrower* Clone() { return new CFlamethrower(*this); };
};

