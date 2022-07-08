#pragma once
#include "CSkill.h"
class CVineWhip :
    public CSkill
{
public:
    CVineWhip();
    ~CVineWhip();
    CVineWhip(const CVineWhip& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CVineWhip* Clone() { return new CVineWhip(*this); };
};

