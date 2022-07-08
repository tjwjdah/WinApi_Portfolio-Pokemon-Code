#pragma once
class CPlayer;
class CSound;
class CTeleportMgr
{
	SINGLE(CTeleportMgr);
private:
	
	vector<Vec2>	 PrePlayerPos;
	vector<Vec2>	 TelpoPlayerPos;
	vector<Vec2>	 PreDoorPlayerPos;
	vector<Vec2>	 TelpoDoorPlayerPos;
	vector<CSound*>  Play_Sound;
	vector<CSound*>  PlayDoor_Sound;
public:
	void init();
	void update(CPlayer* _player);
	void SetTelpoPos(Vec2 _Pre, Vec2 _Tel, const wstring& _strKey);
	void SetTelpoDoorPos(Vec2 _Pre, Vec2 _Tel, const wstring& _strKey);
};	

