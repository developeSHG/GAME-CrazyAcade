#include "stdafx.h"
#include "Tile.h"

#include "Acting.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CTile::CTile()
	: m_iDrawID(0)
	, m_iOption(0)
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y;
	
	switch (m_iScene)
	{
	case 1:
		hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Tile");
		break;
	case 2:
		hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Tile2");
		break;
	case 3:
		hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Tile3");
		break;
	}
	m_bFinish = false;
}

int CTile::Update()
{
	switch (m_iScene)
	{
	case 1:
		if (m_iDrawID > 12)
			m_iDrawID = 0;
		break;
	case 2:
		if (m_iDrawID > 15)
			m_iDrawID = 0;
		break;
	case 3:
		if (m_iDrawID > 15)
			m_iDrawID = 0;
		break;
	}

	return 0;
}

void CTile::LateUpdate()
{
	if (GetAsyncKeyState('U'))
	{
		//m_tInfo.fx -= TILE_SIZE_X;
	}
}

void CTile::Render(HDC hDC)
{
	CObj::UpdateRect();
	if (m_tInfo.fx < 0 || m_tInfo.fx > WINCX || true == m_bFinish)
		return;


	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BitBlt(hDC, int(m_tRect.left), int(m_tRect.top),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		hMemDC,
		int(m_tInfo.fcx * m_iDrawID), 0,
		SRCCOPY);


	if (GetAsyncKeyState(VK_TAB))
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
	//TCHAR buffer[80];
	//wsprintf(buffer, TEXT("%d"), m_iOption);
	//TextOut(hDC, m_tRect.left, m_tRect.top, buffer, lstrlen(buffer));
	//TextOut(hDC, m_tRect.left, m_tRect.top, TEXT("≈∏¿œ"), 2);
}

void CTile::Release()
{
}

void CTile::Create_Acting()
{
	CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
	CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);
	m_bFinish = true;
}
