#include "stdafx.h"
#include "Stage1.h"

#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "StageUI.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CStage1::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"GameStart.wav", CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage1.wav");

	CTileMgr::Get_Instance()->LoadData(1);

	for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK))
	{
		SCAST<CBlock*>(pObj)->Set_Scene(1);
	}

	// 스테이지UI 생성
	CObjMgr::Get_Instance()->AddObject(OBJID::STAGE_UI, CAbstractFactory<CStageUI>::Create());

	// 플레이어 생성
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	//// 몬스터 생성
	CObj* pObj = CAbstractFactory<CMonster>::Create(200.f, 500.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster1");
	SCAST<CMonster*>(pObj)->Set_Stage(1);

	pObj = CAbstractFactory<CMonster>::Create(500.f, 300.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster2");
	SCAST<CMonster*>(pObj)->Set_Stage(1);

	pObj = CAbstractFactory<CMonster>::Create(300.f, 500.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster3");
	SCAST<CMonster*>(pObj)->Set_Stage(1);

	pObj = CAbstractFactory<CMonster>::Create(600.f, 400.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster4");
	SCAST<CMonster*>(pObj)->Set_Stage(1);

	pObj = CAbstractFactory<CMonster>::Create(300.f, 450.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster5");
	SCAST<CMonster*>(pObj)->Set_Stage(1);

	pObj = CAbstractFactory<CMonster>::Create(400.f, 700.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster1");

	pObj = CAbstractFactory<CMonster>::Create(600.f, 100.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster2");

	pObj = CAbstractFactory<CMonster>::Create(200.f, 450.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster3");

	pObj = CAbstractFactory<CMonster>::Create(150.f, 220.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster4");

	pObj = CAbstractFactory<CMonster>::Create(500.f, 100.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster5");
}

int CStage1::Update()
{
	CScene::CreateAirplane();
	CObjMgr::Get_Instance()->Update();


	return 0;
}

void CStage1::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage1::Render(HDC hDC)
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

void CStage1::Release()
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
