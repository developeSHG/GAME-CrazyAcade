#include "stdafx.h"
#include "Stage2.h"

#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "StageUI.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CStage2::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"GameStart.wav", CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage2.wav");

	CTileMgr::Get_Instance()->LoadData(2);

	for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK))
	{
		SCAST<CBlock*>(pObj)->Set_Scene(2);
	}

	// 스테이지UI 생성
	CObjMgr::Get_Instance()->AddObject(OBJID::STAGE_UI, CAbstractFactory<CStageUI>::Create());

	// 플레이어 생성
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	//// 몬스터 생성
	CObj* pObj = CAbstractFactory<CMonster>::Create(200.f, 500.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster1");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(450.f, 450.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster2");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(500.f, 200.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster3");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(400.f, 100.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster4");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(500.f, 600.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster1");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(100.f, 500.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster2");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(50.f, 500.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster3");
	SCAST<CMonster*>(pObj)->Set_Stage(2);

	pObj = CAbstractFactory<CMonster>::Create(150.f, 250.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage2_Monster4");
	SCAST<CMonster*>(pObj)->Set_Stage(2);
}

int CStage2::Update()
{
	CScene::CreateAirplane();
	CObjMgr::Get_Instance()->Update();


	return 0;
}

void CStage2::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage2::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage3");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

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

void CStage2::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BLOCK);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BALLON);
	CObjMgr::Get_Instance()->DeleteID(OBJID::STEM);
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CObjMgr::Get_Instance()->DeleteID(OBJID::INVEN);
	CObjMgr::Get_Instance()->DeleteID(OBJID::AIRPLANE);
	CObjMgr::Get_Instance()->DeleteID(OBJID::DART);
	CObjMgr::Get_Instance()->DeleteID(OBJID::SHIELD);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::STAGE_UI);
	CTileMgr::Destroy_Instance();
	CObjMgr::Get_Instance()->Set_StartActing(true);
}
