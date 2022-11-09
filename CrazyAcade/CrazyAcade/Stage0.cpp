#include "stdafx.h"
#include "Stage0.h"

#include "Player.h"
#include "Block.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CStage0::CStage0()
{
}


CStage0::~CStage0()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CStage0::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage0.wav");

	CTileMgr::Get_Instance()->LoadData(0);

	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(320.0f, 175.f));

}

int CStage0::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('I'))
	{	
		CObj* pObj = CAbstractFactory<CBlock>::Create(CObjMgr::Get_Instance()->Get_Player()->Get_TileRC().left+20.f, CObjMgr::Get_Instance()->Get_Player()->Get_TileRC().bottom + 60.f);
		SCAST<CBlock*>(pObj)->Set_BlockPro(BLOCK::BASIC);
		CObjMgr::Get_Instance()->AddObject(OBJID::BLOCK, pObj);
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_MENU);
	}

	return 0;
}

void CStage0::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage0::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage3");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Flopy_Tile");
	BitBlt(hDC, POINT_X, POINT_Y, 600, 520, hMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage2");
	GdiTransparentBlt(hDC,//출력할 DC
		0, 0,// 그림을 그릴 시작 좌표 XY
		WINCX, WINCY,// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		0, 0,// 출력할 비트맵의 시작 좌표 
		WINCX, WINCY,// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
						  //BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	list<CObj*>* plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::INVEN);
	for (auto& pObj : *plistObj)
	{
		pObj->Render(hDC);
	}
}

void CStage0::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::BLOCK);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BALLON);
	CObjMgr::Get_Instance()->DeleteID(OBJID::STEM);
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CObjMgr::Get_Instance()->DeleteID(OBJID::INVEN);
	CObjMgr::Get_Instance()->DeleteID(OBJID::DART);
	CObjMgr::Get_Instance()->DeleteID(OBJID::SHIELD);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CTileMgr::Destroy_Instance();
	CObjMgr::Get_Instance()->Set_StartActing(true);
}
