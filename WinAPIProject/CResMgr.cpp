#include "stdafx.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    for (auto& pair: m_mapTex)
    {
        if (nullptr != pair.second)
            delete pair.second;
    }

    for (auto& pair : m_mapSound)
    {
        if (nullptr != pair.second)
            delete pair.second;
    }
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    assert(nullptr == FindTexture(_strKey));    

    CTexture* pTex = new CTexture;

    wstring strFilePath = CPathMgr::GetResPath();
    strFilePath += _strRelativePath;
    pTex->Load(strFilePath);
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    // map 에 등록
    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

    if (iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    assert(nullptr == FindSound(_strKey));

    CSound* pSound = new CSound;

    wstring strFilePath = CPathMgr::GetResPath();
    strFilePath += _strRelativePath;
    pSound->Load(strFilePath);
    pSound->SetKey(_strKey);
    pSound->SetRelativePath(_strRelativePath);

    // map 에 등록
    m_mapSound.insert(make_pair(_strKey, pSound));

    return pSound;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
    map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

    if (iter == m_mapSound.end())
        return nullptr;

    return iter->second;
}
