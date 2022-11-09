#include "stdafx.h"
#include "Loading.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "LoadingUI.h"

CLoading::CLoading()
{
}


CLoading::~CLoading()
{
	Release();
}

void CLoading::Initialize()
{
	CObj* pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading1");
	pObj->Set_Pos(380.f, 310.f);
	pObj->Set_Size(93.f, 71.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(300);
	SCAST<CLoadingUI*>(pObj)->Set_Point(460, 120);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(18.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);

	pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading2");
	pObj->Set_Pos(300.f, 250.f);
	pObj->Set_Size(118.f, 110.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(550);
	SCAST<CLoadingUI*>(pObj)->Set_Point(550, 850);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(22.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);

	pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading3");
	pObj->Set_Pos(230.f, 450.f);
	pObj->Set_Size(146.f, 129.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(800);
	SCAST<CLoadingUI*>(pObj)->Set_Point(720, 130);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(26.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);

	pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading4");
	pObj->Set_Pos(500.f, 370.f);
	pObj->Set_Size(122.f, 113.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(1050);
	SCAST<CLoadingUI*>(pObj)->Set_Point(150, 440);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(21.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);

	pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading5");
	pObj->Set_Pos(290.f, 260.f);
	pObj->Set_Size(192.f, 165.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(1300);
	SCAST<CLoadingUI*>(pObj)->Set_Point(760, 530);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(22.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);

	pObj = CAbstractFactory<CLoadingUI>::Create();
	pObj->Set_FrameKey(L"UI_Loading6");
	pObj->Set_Pos(450.f, 350.f);
	pObj->Set_Size(212, 240.f);
	SCAST<CLoadingUI*>(pObj)->Set_Timer(1550);
	SCAST<CLoadingUI*>(pObj)->Set_Point(190, 160);
	SCAST<CLoadingUI*>(pObj)->Set_Speed(21.5f);
	CObjMgr::Get_Instance()->AddObject(OBJID::LOADING_UI, pObj);
	
	m_tTime = GetTickCount();
	m_tLoadingTime = GetTickCount();
	m_fX = 351.f;
}

int CLoading::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (m_tTime + 2200 < GetTickCount())
	{
		if (0 == m_iStageActive)
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE0);
		else if(1 == m_iStageActive)
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE1);
		else if (2 == m_iStageActive)
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE2);
		else if (3 == m_iStageActive)
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE3);
		return 0;
	}

	static int iCount = 0;
	//m_fX += iCount * 50.f;
	if (m_tLoadingTime + 200 < GetTickCount())
	{
		if (2 > iCount)
		{
			m_fX += 32.f;
			++iCount;
		}
		else
		{
			m_fX = 351.f;
			iCount = 0;
		}
		m_tLoadingTime = GetTickCount();
	}
	return 0;
}

void CLoading::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CLoading::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Loading");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Loading");
	GdiTransparentBlt(hDC,
		320, 250,
		154, 96,
		hMemDC,
		0, 0,
		154, 96,
		RGB(255, 0, 255));

	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"LoadingPoint");
	GdiTransparentBlt(hDC,
		int(m_fX), 312,
		32, 30,
		hMemDC,
		0, 0,
		32, 30,
		RGB(255, 0, 255));
}

void CLoading::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::LOADING_UI);
}
