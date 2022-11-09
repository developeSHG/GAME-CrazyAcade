#include "stdafx.h"
#include "Logo.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	TCHAR* pAllUser[115] = {
		L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", 
		L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo1", L"Logo7", L"Logo8", L"Logo9", L"Logo10", L"Logo11", 
		L"Logo12", L"Logo13", L"Logo14", L"Logo15", L"Logo16", L"Logo17", L"Logo18", L"Logo19", L"Logo20", L"Logo21", 
		L"Logo22", L"Logo23", L"Logo24", L"Logo25",
		L"LogoN1", L"LogoN2", L"LogoN3", L"LogoN4", L"LogoN5", L"LogoN6", L"LogoN7", L"LogoN8", L"LogoN9", L"LogoN10",
		L"LogoN11", L"LogoN12", L"LogoN13", L"LogoN14", L"LogoN15", L"LogoN16", L"LogoN17", L"LogoN18", L"LogoN19", L"LogoN20",
		L"LogoN21", L"LogoN22", L"LogoN23", L"LogoN24", L"LogoN25", L"LogoN26", L"LogoN27", L"LogoN28", L"LogoN29", L"LogoN30",
		L"LogoN31", L"LogoN32", L"LogoN33", L"LogoN34", L"LogoN35", L"LogoN36", L"LogoN37", L"LogoN38", L"LogoN39", L"LogoN40",
		L"LogoN41", L"LogoN42", L"LogoN43", L"LogoN44", L"LogoN45", L"LogoN46", L"LogoN47", L"LogoN48", L"LogoN49", L"LogoN50",
		L"LogoN51", L"LogoN52", L"LogoN53", L"LogoN54", L"LogoN55", L"LogoN56", L"LogoN57", L"LogoN58", L"LogoN59", L"LogoN60",
		L"LogoN61", L"LogoN62", L"LogoN63", L"LogoN64", L"LogoN65", L"LogoN66", L"LogoN67", L"LogoN68", L"LogoN69", L"LogoN70",
		L"LogoN71", L"LogoN72", L"LogoN73", L"LogoN73", L"LogoN73", L"LogoN73", L"LogoN73", L"LogoN73", L"LogoN73", L"LogoN73",
		L"LogoN73"
	};

	memcpy(m_pAllUser, pAllUser, sizeof(pAllUser));
	m_dwTime = GetTickCount();
	m_iStep = 1;
}

int CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CLogo::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGIN);
	}
	CObjMgr::Get_Instance()->LateUpdate();
}

void CLogo::Render(HDC hDC)
{
	static int i = 0;

	if (m_dwTime + 33 < GetTickCount() && 1 == m_iStep)
	{
		if (i == 33)
			m_iStep = 2;

		m_dwTime = GetTickCount();
		++i;
	}
	if (m_dwTime + 67 < GetTickCount() && 2 == m_iStep)
	{
		if (i == 114)
		{
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGIN);
			return;
		}
		m_dwTime = GetTickCount();
		++i;
	}
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pAllUser[i]);
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release()
{
	//CBmpMgr::Destroy_Instance();
}
