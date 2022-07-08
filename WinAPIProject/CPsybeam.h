#pragma once
#include "CSkill.h"
class CPsybeam :
    public CSkill
{

public:
    CPsybeam();
    ~CPsybeam();
    CPsybeam(const CPsybeam& _origin);
public:

    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CPsybeam* Clone() { return new CPsybeam(*this); };
};

