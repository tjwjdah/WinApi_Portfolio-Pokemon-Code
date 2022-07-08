#pragma once
#include "CObj.h"

class CTexture;

class CTile :
    public CObj
{
private:
    CTexture* m_pTileTex;
    CTexture* m_pTileTex2;
    int         m_iImgIdx;
    bool        m_p2TileOn;
    bool        m_pColliderOn;
    UI_TYPE     m_randerTile;

    CTile* m_p2Tile;

    bool m_ObjectOn;
    OBJECTSNAME m_ObjectNum;
    CObj* m_pObject;

    bool m_ShowVec;
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    void SetTileTex(CTexture* _pTex, CTexture* _pTex2) { m_pTileTex = _pTex; m_pTileTex2 = _pTex2; }
    void SetImgIdx(int _iImgIdx) { m_iImgIdx = _iImgIdx; }
    void SetranderTile(UI_TYPE _randertile) { m_randerTile = _randertile; }
    int GetImgIdx() { return m_iImgIdx; }

    void Set2tile(CTile* _tile2) { m_p2Tile = _tile2; }
    void Set2tileOn(bool _tile2On) { m_p2TileOn = _tile2On; }
    CTexture* GetTile1() { return m_pTileTex; }
    CTexture* GetTile2() { return m_pTileTex2; }
    CTile* Get2Tile() { return m_p2Tile; }


    CObj* GetpObject() { return m_pObject; }
    void SetpObject(CObj* _obj) { m_pObject = _obj; }

    OBJECTSNAME GetpObjectNum() { return m_ObjectNum; }
    void SetpObjectNum(OBJECTSNAME _ObjNum) { m_ObjectNum = _ObjNum; }

    bool GetObjectOn() { return m_ObjectOn; }
    void SetObjectOn(bool _on) { m_ObjectOn = _on; }
    
    void ColliderOn();

    virtual CTile* Clone() { return new CTile(*this); }

public:
    CTile();
    ~CTile();
};

