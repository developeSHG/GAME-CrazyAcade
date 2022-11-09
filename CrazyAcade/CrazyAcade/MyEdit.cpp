#include "stdafx.h"
#include "MyEdit.h"

#include "Player.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Block.h"
#include "ObjMgr.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
}

void CMyEdit::Initialize()
{
	//CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CTileMgr::Get_Instance()->Set_Scene(1);
	CTileMgr::Get_Instance()->LoadData(1);
	//CTileMgr::Get_Instance()->Initialize();
	//for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK))
	//{
	//	SCAST<CBlock*>(pObj)->Set_Scene(3);
	//}
}

int CMyEdit::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		POINT pt = {};
		GetCursorPos(&pt);
		pt.y -= 28;
		ScreenToClient(g_hWND, &pt);
		CTileMgr::Get_Instance()->PickTile_DrawID(pt, 1);
	}
	else if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))	
	{
		POINT pt = {};
		GetCursorPos(&pt);
		pt.y -= 28;
		ScreenToClient(g_hWND, &pt);
		CTileMgr::Get_Instance()->PickTile_Option(pt, 1);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
	{
		CTileMgr::Get_Instance()->Set_KindsPlus();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('2'))
	{
		CTileMgr::Get_Instance()->Set_KindsMinus();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		//CTileMgr::Get_Instance()->SaveData(1);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('D'))
	{
		//CTileMgr::Get_Instance()->SaveData(2);
	}
	if (CKeyMgr::Get_Instance()->KeyDown('F'))
	{
		//CTileMgr::Get_Instance()->SaveData(3);
	}
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyEdit::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyEdit::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage1");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release()
{
}
