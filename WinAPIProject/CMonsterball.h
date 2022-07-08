#pragma once
#include "CItem.h"
class CMonsterball :
    public CItem
{
public:
    CMonsterball();
    ~CMonsterball();
    CMonsterball(const CMonsterball& _origin);

public:
    virtual void run();
    virtual void init();
    

public:
    virtual CMonsterball* Clone() { return new CMonsterball(*this); };
};

