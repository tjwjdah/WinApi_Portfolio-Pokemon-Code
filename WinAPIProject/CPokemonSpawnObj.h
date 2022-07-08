#pragma once
#include "CObj.h"


class CPokemon;
class CPokemonSpawnObj :
    public CObj
{
public:
    CPokemonSpawnObj();
    ~CPokemonSpawnObj();


    CPokemonSpawnObj(const CPokemonSpawnObj& _origin);
private:
    CTexture* m_pTex;
public:
    void SetTexture(CTexture* _pTex);
    CTexture* GetTexture() { return m_pTex; };

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual CPokemonSpawnObj* Clone() { return new CPokemonSpawnObj(*this); }


public:
    CPokemon* PokemonSpawn();
};

