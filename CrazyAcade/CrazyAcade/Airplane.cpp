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


	// ����� ��������
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
	// ���� �ִ� Ÿ�� ��ġüũ (����)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	// ���� �ִ� Ÿ�� ��ġüũ (��)
	
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//����� DC
		int(m_tRect.left), int(m_tRect.top),// �׸��� �׸� ���� ��ǥ XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
		hMemDC,// ������ DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// ����� ��Ʈ���� ���� ��ǥ 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
		RGB(255, 0, 255));// ���� �������ϴ� ����. 
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
