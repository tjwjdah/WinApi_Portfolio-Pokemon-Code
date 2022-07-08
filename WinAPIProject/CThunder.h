#pragma once
#include "CSkill.h"
class CThunder :
    public CSkill
{
public:
    CThunder();
    ~CThunder();
    CThunder(const CThunder& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CThunder* Clone() { return new CThunder(*this); };
};

