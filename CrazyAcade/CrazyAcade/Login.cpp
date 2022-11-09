#include "stdafx.h"
#include "Login.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "MyButton.h"


CLogin::CLogin()
{
}


CLogin::~CLogin()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CLogin::Initialize()
{
	CObj* pObj = CAbstractFactory<CMyButton>::Create(238.f, 474.f);
	dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Button_Start");
	CObjMgr::Get_Instance()->AddObject(OBJID::LOGIN_UI, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(400.f, 450.f);
	//dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Button_Edit");
	//pObj->Set_Size(168.f, 34.f);
	//CObjMgr::Get_Instance()->AddObject(OBJID::LOGIN_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(560.f, 475.f);
	dynamic_cast<CMyButton *>(pObj)->Set_FrameKey(L"Button_Exit");
	CObjMgr::Get_Instance()->AddObject(OBJID::LOGIN_UI, pObj);

	CSoundMgr::Get_Instance()->PlayBGM(L"Login.wav");
}

int CLogin::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CLogin::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CLogin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Login");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogin::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::LOGIN_UI);
}
