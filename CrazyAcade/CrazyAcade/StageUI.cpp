#include "stdafx.h"
#include "StageUI.h"

#include "Player.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"


CStageUI::CStageUI()
{
}


CStageUI::~CStageUI()
{
	Release();
}

void CStageUI::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 0.f;
	m_tInfo.fcy = 0.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;

	// 스테이지UI 고유변수
	m_dwGameStartTime = GetTickCount();
	m_dwPosTime = GetTickCount();
	m_bFade = false;
	m_bFinish = false;
	m_bFinishBmp = false;
	m_bResult = false;
	m_bIsInit = false;
}

int CStageUI::Update()
{
	if (m_dwPosTime + 400 < GetTickCount())
	{
		m_bFade = !m_bFade;
		m_dwPosTime = GetTickCount();
	}
	if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && m_dwPosTime + 1000 < GetTickCount())
	{
		//CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE2);
	}
	if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && CSceneMgr::SCENEID::SCENE_STAGE3 != CSceneMgr::Get_Instance()->Get_SceneID())
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
			return 0;

		}
	}
	if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && true == CObjMgr::Get_Instance()->Get_Obj(OBJID::BOSS)->empty()
		&& CSceneMgr::SCENEID::SCENE_STAGE3 == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			CTileMgr::Get_Instance()->Game_Finish();
			CObjMgr::Get_Instance()->DeleteID(OBJID::BLOCK);
			CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
			CObjMgr::Get_Instance()->DeleteID(OBJID::AIRPLANE);
			m_bFinish = true;
		}

		if (170 > CObjMgr::Get_Instance()->Get_Player()->Get_Info().fy && true == m_bFinish)
		{
			m_bFinishBmp = true;
		}
	}


	return 0;
}

void CStageUI::LateUpdate()
{
}

void CStageUI::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC MemDC;
	if (m_dwGameStartTime + GAME_START_TIME > GetTickCount())
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Game_Start");
		GdiTransparentBlt(hDC,
			int(MAP_X/2.f - 135.f), int(MAP_Y/2.f -15.f),
			350, 113,
			MemDC,
			0, 0,
			350, 113,
			RGB(255, 0, 255));
	}
	if (m_dwGameStartTime + GAME_START_TIME + 500 < GetTickCount() && m_dwGameStartTime + GAME_START_TIME + 5000 > GetTickCount() && false == m_bFade)
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"PlayerPos");
		GdiTransparentBlt(hDC,
			int(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()->left), int(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()->top - 55.f),
			45, 56,
			MemDC,
			0, 0,
			45, 56,
			RGB(255, 0, 255));
	}
	else if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID()
		&& CSceneMgr::SCENEID::SCENE_STAGE3 != CSceneMgr::Get_Instance()->Get_SceneID())
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Clear");
		GdiTransparentBlt(hDC,
			int(MAP_X / 2.f - 110.f), int(MAP_Y / 2.f + 10.f),
			300, 47,
			MemDC,
			0, 0,
			300, 47,
			RGB(255, 0, 255));	

		m_bResult = true;
		CObj::LateInit();
	}
	else if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && CSceneMgr::SCENEID::SCENE_STAGE2 == CSceneMgr::Get_Instance()->Get_SceneID()
		&& CSceneMgr::SCENEID::SCENE_STAGE3 != CSceneMgr::Get_Instance()->Get_SceneID())
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Clear");
		GdiTransparentBlt(hDC,
			int(MAP_X / 2.f - 110.f), int(MAP_Y / 2.f + 10.f),
			300, 47,
			MemDC,
			0, 0,
			300, 47,
			RGB(255, 0, 255));

		m_bResult = true;
		CObj::LateInit();

	}
	else if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && true == CObjMgr::Get_Instance()->Get_Obj(OBJID::BOSS)->empty()
		&& CSceneMgr::SCENEID::SCENE_STAGE3 == CSceneMgr::Get_Instance()->Get_SceneID() && false == m_bFinish)
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Clear");
		GdiTransparentBlt(hDC,
			int(MAP_X / 2.f - 110.f), int(MAP_Y / 2.f + 10.f),
			300, 47,
			MemDC,
			0, 0,
			300, 47,
			RGB(255, 0, 255));

		m_bResult = true;
		CObj::LateInit();

	}
	else if (true == SCAST<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_DieState())
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Lose");
		GdiTransparentBlt(hDC,
			int(MAP_X / 2.f - 110.f), int(MAP_Y / 2.f + 10.f),
			300, 54,
			MemDC,
			0, 0,
			300, 54,
			RGB(255, 0, 255));

		m_bResult = false;
		CObj::LateInit();
	}

	if (true == m_bFinishBmp)
	{
		MemDC = CBmpMgr::Get_Instance()->FindImage(L"Finish");
		BitBlt(hDC, 0, 0, WINCX, WINCY, MemDC, 0, 0, SRCCOPY);
	}
}

void CStageUI::Release()
{
}

void CStageUI::LateInit()
{

}
