#include "stdafx.h"
#include "MyMenu.h"

#include "SceneMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "MyButton.h"
#include "MyBanner.h"
#include "MyCharacter.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CMyMenu::Initialize()
{
	// 메뉴 UI
	CObj* pObj = CAbstractFactory<CMyCharacter>::Create(78.f, 150.f);
	pObj->Set_Size(49.f, 60.f);
	SCAST<CMyCharacter *>(pObj)->Set_FrameKey(L"Random_Select");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(520.f, 201.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Dao_Button");
	pObj->Set_Size(63.f, 40.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(592.f, 201.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Digini_Button");
	pObj->Set_Size(63.f, 40.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(664.f, 201.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Bazzi_Button");
	pObj->Set_Size(63.f, 40.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(736.f, 201.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Uni_Button");
	pObj->Set_Size(63.f, 40.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyBanner>::Create(-693.f, 293.f);
	SCAST<CMyBanner *>(pObj)->Set_FrameKey(L"Color_Check");
	pObj->Set_Size(30.f, 35.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(505.f, 301.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Red");
	pObj->Set_Size(40.f, 35.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(757.f, 301.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Black");
	pObj->Set_Size(40.f, 35.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(609.f, 523.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Start_Button");
	pObj->Set_Size(187.f, 51.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	pObj = CAbstractFactory<CMyBanner>::Create(630.f, 137.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI, pObj);

	// 메뉴 UI 2
	pObj = CAbstractFactory<CMyBanner>::Create(630.f, 413.f);
	SCAST<CMyBanner *>(pObj)->Set_FrameKey(L"Map_Camp");
	pObj->Set_Size(287.f, 136.f);
	SCAST<CMyBanner*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyBanner>::Create(630.f, 413.f);
	SCAST<CMyBanner *>(pObj)->Set_FrameKey(L"Map_Factory");
	pObj->Set_Size(287.f, 136.f);
	SCAST<CMyBanner*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(708.f, 453.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Map_Button");
	pObj->Set_Size(122.f, 46.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyBanner>::Create(400.f, 300.f);
	SCAST<CMyBanner *>(pObj)->Set_FrameKey(L"Map_Select");
	pObj->Set_Size(534.f, 485.f);
	SCAST<CMyBanner*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(342.f, 516.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Map_SelectButton1");
	pObj->Set_Size(102.f, 30.f);
	SCAST<CMyButton*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(459.f, 516.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"Map_SelectButton2");
	pObj->Set_Size(102.f, 30.f);
	SCAST<CMyButton*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(459.f, 227.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"BlueBox1");
	pObj->Set_Size(320.f, 25.f);
	SCAST<CMyButton*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(459.f, 282.f);
	SCAST<CMyButton *>(pObj)->Set_FrameKey(L"BlueBox2");
	pObj->Set_Size(320.f, 25.f);
	SCAST<CMyButton*>(pObj)->Set_Active(false);
	CObjMgr::Get_Instance()->AddObject(OBJID::MENU_UI2, pObj);

	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.wav");
}

int CMyMenu::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE0);
	}
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyMenu::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MENU_UI);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MENU_UI2);
}
