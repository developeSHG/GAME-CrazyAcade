#include "stdafx.h"
#include "Airplane.h"

#include"Item.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CAirplane::CAirplane()
{
}


CAirplane::~CAirplane()
{
	Release();
}

void CAirplane::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 146.f;
	m_tInfo.fcy = 76.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 3.f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;

	m_pFrameKey = L"Airplane_Left";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();


	// 비행기 고유변수
	static int iDir = 0;
	++iDir;
	switch (iDir % 2)
	{
	case 0:
		m_pFrameKey = L"Airplane_Left";
		m_tInfo.fx = WINCX;
		break;
	case 1:
		m_pFrameKey = L"Airplane_Right";
		m_tInfo.fx = -150.f;
		break;
	}
	m_tInfo.fy = float(rand() % 500 + 50);
	
	m_dwTime = GetTickCount();
	m_iCreateItemTime = rand() % 2500 + 1000;
}

int CAirplane::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (L"Airplane_Left" == m_pFrameKey)
		m_tInfo.fx -= m_fSpeed;
	else
		m_tInfo.fx += m_fSpeed;

	if (m_dwTime + m_iCreateItemTime < GetTickCount())
	{
		Create_Item();
		m_iCreateItemTime = GetTickCount();
	}


	return OBJ_LIVE;
}

void CAirplane::LateUpdate()
{
	if (L"Airplane_Left" == m_pFrameKey)
	{
		if (-100.f > m_tInfo.fx)
			m_bIsDead = OBJ_DEAD;
	}
	else
	{
		if (WINCX < m_tInfo.fx)
			m_bIsDead = OBJ_DEAD;
	}

	CObj::MoveFrame();
}

void CAirplane::Render(HDC hDC)
{
	// 내가 있는 타일 위치체크 (시작)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	// 내가 있는 타일 위치체크 (끝)
	
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//출력할 DC
		int(m_tRect.left), int(m_tRect.top),// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
}

void CAirplane::Release()
{
}

void CAirplane::Create_Item()
{
	CObj* pObj = CAbstractFactory<CItem>::Create(m_tInfo.fx, m_tInfo.fy + 30.f);

	int Item = rand() % 6;

	if (0 <= Item && 2 >= Item)
		SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(ITEM::SHOES+1)));
	else if( 3 <= Item && 4 >= Item)
		SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(5)+ ITEM::NEEDLE));
	else if (5 == Item)
		SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(7)+ ITEM::TURTLE));

	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	SCAST<CItem*>(pObj)->Set_CreateCheck();

}
