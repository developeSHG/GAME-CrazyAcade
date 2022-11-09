#include "stdafx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);

	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	LoadSoundFile();

	FMOD_Channel_SetVolume(m_pChannelArr[CHANNELID::HIT], 0.5f);
}

void CSoundMgr::Update()
{
}

void CSoundMgr::Release()
{
	for (int i = 0; i < CHANNELID::MAXCHANNEL; ++i)
	{
		for (std::map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin(); iter != m_mapSound.end();)
		{
			delete iter->first;
			FMOD_Sound_Release(iter->second);
			iter = m_mapSound.erase(iter);
		}
	}
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void CSoundMgr::MyPlaySound(TCHAR * pSoundKey, CHANNELID eID)
{
	/*auto& iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& Pair)
	{
	return lstrcmp(pSoundKey, Pair.first);
	});*/
	if (m_mapSound.empty())
		return;

	auto& iter = find_if(m_mapSound.begin(), m_mapSound.end(), CMyStrCmp(pSoundKey));
	if (iter == m_mapSound.end())
		return;
	//FMOD_BOOL isPlay;

	/*if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &isPlay))
	{*/
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	//}
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR * pSoundKey)
{
	if (m_mapSound.empty())
		return;

	auto& iter = find_if(m_mapSound.begin(), m_mapSound.end(), CMyStrCmp(pSoundKey));

	if (m_mapSound.end() == iter)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;

	// 사운드 경로를 바꾸고 싶다면 여기서 너네가 원하는 경로를 적어주면 됨. 
	long handle = _findfirst("../Sound/*.*", &fd);

	if (handle == 0)
		return;

	int iResult = 0;

	// 사운드 경로를 바꾸고 싶다면 여기서 너네가 원하는 경로를 적어주면 됨. 
	char szCurPath[128] = "../Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);
		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pSystem);
}
