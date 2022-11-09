#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)
public:
	enum CHANNELID { BGM, PLAYER, MONSTER, EFFECT, UI, NPC, HIT, MAXCHANNEL };
public:
	void Initialize();
	void Update();
	void Release();

public:
	void MyPlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();

public:
	void LoadSoundFile();

private:
	// FMOD_SOUND : 사운드 리소스 정보를 갖는 객체
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL -  재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// 사운드 , 채널 객체 및 장치를 관리할 객체. 
	FMOD_SYSTEM* m_pSystem;

};

