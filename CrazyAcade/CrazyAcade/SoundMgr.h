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
	// FMOD_SOUND : ���� ���ҽ� ������ ���� ��ü
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL -  ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// ���� , ä�� ��ü �� ��ġ�� ������ ��ü. 
	FMOD_SYSTEM* m_pSystem;

};

