#include "stdafx.h"
#include "CTeleportMgr.h"


#include "CPlayer.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
CTeleportMgr::CTeleportMgr() {

}
CTeleportMgr::~CTeleportMgr() {

}
void CTeleportMgr::init()
{
	CSound* pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Oak-Research-Institute.wav", L"Sound\\Oak-Research-Institute.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Pokemon_Center.wav", L"Sound\\Pokemon_Center.wav");
	pNewSound = CResMgr::GetInst()->LoadSound(L"Sound\\Pokemon_Gym.wav", L"Sound\\Pokemon_Gym.wav");
	SetTelpoPos(Vec2(18*64,12*64), Vec2(44*64,12*64),L"없음");//2층에서 1층
	SetTelpoPos(Vec2(45*64,12*64), Vec2(19*64,12 *64), L"없음");//1층에서 2층
	SetTelpoPos(Vec2(38*64, 19*64), Vec2(104*64, 229*64), L"없음");//1층에서 마을
	SetTelpoPos(Vec2(16 * 64, 43 * 64), Vec2(114 * 64, 235 * 64),L"Pallet-Town-Theme.wav");//박사에서 마을


	SetTelpoPos(Vec2(40 * 64, 39 * 64), Vec2(121 * 64, 152 * 64), L"Pallet-Town-Theme.wav");//짐에서 마을
	SetTelpoPos(Vec2(41 * 64, 39 * 64), Vec2(121 * 64, 152 * 64), L"Pallet-Town-Theme.wav");
	SetTelpoPos(Vec2(42 * 64, 39 * 64), Vec2(121 * 64, 152 * 64), L"Pallet-Town-Theme.wav");

	SetTelpoPos(Vec2(67 * 64, 19 * 64), Vec2(111 * 64, 168 * 64), L"Pallet-Town-Theme.wav");//센터


	SetTelpoDoorPos(Vec2(104 * 64,229 * 64), Vec2(38 * 64, 18 * 64),L"없음");//집

	SetTelpoDoorPos(Vec2(114 * 64, 235 * 64), Vec2(16 * 64, 42 * 64),L"Oak-Research-Institute.wav");//박사

	SetTelpoDoorPos(Vec2(121 * 64, 152 * 64), Vec2(41 * 64, 38 * 64), L"Pokemon_Gym.wav");//짐


	SetTelpoDoorPos(Vec2(111 * 64, 168 * 64), Vec2(67 * 64, 18 * 64), L"Pokemon_Center.wav");//센터
}

void CTeleportMgr::update(CPlayer* _player)
{
	for (size_t i = 0 ; i< PrePlayerPos.size();i++)
	{
		if (_player->GetPos() == PrePlayerPos[i])
		{
			_player->SetPlayerPos(TelpoPlayerPos[i]);
			CCamera::GetInst()->Setcamera(TelpoPlayerPos[i]);
			if (Play_Sound[i] != nullptr)
			{
				Play_Sound[i]->SetVolume(100);
				Play_Sound[i]->PlayToBGM(true);
			}
		}
	}
	for (size_t i = 0; i < PreDoorPlayerPos.size(); i++)
	{
		if (_player->GetPos() == PreDoorPlayerPos[i])
		{
			if (KEY_TAP(KEY_TYPE::KEY_UP) || KEY_AWAY(KEY_TYPE::KEY_UP))
			{
				_player->SetPlayerPos(TelpoDoorPlayerPos[i]);
				CCamera::GetInst()->Setcamera(TelpoDoorPlayerPos[i]);
				if (PlayDoor_Sound[i] != nullptr)
				{
					PlayDoor_Sound[i]->SetVolume(100);
					PlayDoor_Sound[i]->PlayToBGM(true);
				}
			}
		}
	}
}

void CTeleportMgr::SetTelpoPos(Vec2 _Pre, Vec2 _Tel, const wstring& _strKey)
{
	PrePlayerPos.push_back(_Pre);
	TelpoPlayerPos.push_back(_Tel);
	if (_strKey == L"없음")
		Play_Sound.push_back(nullptr);
	else
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\" + _strKey);
		Play_Sound.push_back(pNewSound);
	}
}

void CTeleportMgr::SetTelpoDoorPos(Vec2 _Pre, Vec2 _Tel, const wstring& _strKey)
{
	PreDoorPlayerPos.push_back(_Pre);
	TelpoDoorPlayerPos.push_back(_Tel);
	if(_strKey == L"없음")
		PlayDoor_Sound.push_back(nullptr);
	else
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Sound\\"+_strKey);
		PlayDoor_Sound.push_back(pNewSound);
	}
}

