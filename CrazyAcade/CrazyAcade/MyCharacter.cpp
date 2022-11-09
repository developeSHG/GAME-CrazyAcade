#include "stdafx.h"
#include "MyCharacter.h"

#include "BmpMgr.h"
#include "ObjMgr.h"

CMyCharacter::CMyCharacter()
{
}

CMyCharacter::~CMyCharacter()
{
	Release();
}

void CMyCharacter::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 0.f;
	m_tInfo.fcy = 0.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;
}

int CMyCharacter::Update()
{
	return 0;
}

void CMyCharacter::LateUpdate()
{
	if (!lstrcmp(m_pFrameKey, L"Dao_Select"))
	{
		m_tInfo.fcx = 52.f;
		m_tInfo.fcy = 63.f;
	}
	else if (!lstrcmp(m_pFrameKey, L"Digini_Select"))
	{
		m_tInfo.fcx = 45.f;
		m_tInfo.fcy = 66.f;
	}
	else if (!lstrcmp(m_pFrameKey, L"Bazzi_Select"))
	{
		m_tInfo.fcx = 45.f;
		m_tInfo.fcy = 63.f;
	}
	else if (!lstrcmp(m_pFrameKey, L"Uni_Select"))
	{
		m_tInfo.fcx = 50.f;
		m_tInfo.fcy = 63.f;
	}
}

void CMyCharacter::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC MemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);


	if (lstrcmp(m_pFrameKey, L"Random_Select"))
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left), int(m_tRect.top),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			MemDC,
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(11, 190, 255));
	}
	else
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left), int(m_tRect.top),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			MemDC,
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(100, 100, 100));
	}
}

void CMyCharacter::Release()
{
}
