#pragma once

#include "CSkill.h"


class CTackle :
    public CSkill
{
    
public:
    CTackle();
    ~CTackle();
    CTackle(const CTackle& _origin);
public:
   
    virtual void SkillUse();
    virtual void SkillText();
    virtual void render(HDC _dc);
    virtual CTackle* Clone() { return new CTackle(*this); };
};

