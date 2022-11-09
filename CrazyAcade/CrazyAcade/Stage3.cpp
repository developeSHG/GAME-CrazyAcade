#include "stdafx.h"
#include "Stage3.h"

#include "Player.h"
#include "Monster.h"
#include "Boss.h"
#include "Block.h"
#include "StageUI.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
	CSoundMgr::Get_Instance()->StopAll();
	Release();
}

void CStage3::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"GameStart.wav", CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage3.wav");

	CTileMgr::Get_Instance()->LoadData(3);

	for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK))
	{
		SCAST<CBlock*>(pObj)->Set_Scene(3);
	}

	// ��������UI ����
	CObjMgr::Get_Instance()->AddObject(OBJID::STAGE_UI, CAbstractFactory<CStageUI>::Create());

	// �÷��̾� ����
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	// ���� ����
	CObj* pObj = CAbstractFactory<CBoss>::Create(560.f, 590.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::BOSS, pObj);
}

int CStage3::Update()
{
	CScene::CreateAirplane();
	CObjMgr::Get_Instance()->Update();

	//if (CKeyMgr::Get_Instance()->KeyDown('I'))
	//{
	//	CObj* pObj = nullptr;
	//	switch (m_iCreateMonster % 3)
	//	{
	//	case 0:
	//		pObj = CAbstractFactory<CMonster>::Create(200.f, 500.f);
	//		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	//		SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster1");
	//		SCAST<CMonster*>(pObj)->Set_Stage(1);
	//		break;
	//	case 1:
	//		pObj = CAbstractFactory<CMonster>::Create(500.f, 200.f);
	//		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	//		SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster1");
	//		SCAST<CMonster*>(pObj)->Set_Stage(1);
	//		break;
	//	case 2:
	//		pObj = CAbstractFactory<CMonster>::Create(500.f, 500.f);
	//		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);
	//		SCAST<CMonster*>(pObj)->Set_FrameKey(L"Stage1_Monster1");
	//		SCAST<CMonster*>(pObj)->Set_Stage(1);
	//		break;
	//	}
	//	m_iCreateMonster++;
	//}

	return 0;
}

void CStage3::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage3::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage3");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Flopy_Tile");
	BitBlt(hDC, POINT_X, POINT_Y, 600, 520, hMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Back_Stage2");
	GdiTransparentBlt(hDC,//����� DC
		0, 0,// �׸��� �׸� ���� ��ǥ XY
		WINCX, WINCY,// ����� �׸��� ũ�� 
		hMemDC,// ������ DC 
		0, 0,// ����� ��Ʈ���� ���� ��ǥ 
		WINCX, WINCY,// ����� ��Ʈ ���� ��ü ���� ���� ���� 
		RGB(255, 0, 255));// ���� �������ϴ� ����. 
						  //BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	list<CObj*>* plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::INVEN);
	for (auto& pObj : *plistObj)
	{
		pObj->Render(hDC);
	}

	plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::STAGE_UI);
	for (auto& pObj : *plistObj)
	{
		pObj->Render(hDC);
	}
}

void CStage3::Release()
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
	CObjMgr::Get_Instance()->DeleteID(OBJID::BOSS);
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::STAGE_UI);
	CTileMgr::Destroy_Instance();
	CObjMgr::Get_Instance()->Set_StartActing(true);
}
