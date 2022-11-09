#include "stdafx.h"
#include "Inven.h"

#include "BmpMgr.h"

CInven::CInven()
{
}


CInven::~CInven()
{
	Release();
}

void CInven::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 38.f;
	m_tInfo.fcy = 38.f;
	m_tInfo.fx = 260.f;
	m_tInfo.fy = 590.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 0.f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;

	//m_pFrameKey = L"Item";
	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 0;
	//m_tFrame.iFrameScene = 0;
	//m_tFrame.dwFrameSpeed = 125;
	//m_tFrame.dwFrameTime = GetTickCount();

	// 인벤 고유변수
	m_iOrder = 1;
	m_bActive = false;
}

int CInven::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	return OBJ_LIVE;
}

void CInven::LateUpdate()
{
}

void CInven::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	
	if (true == m_bActive)
	{
		GdiTransparentBlt(hDC,//출력할 DC
			int(675.f), int(492.f),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 
	}
	GdiTransparentBlt(hDC,//출력할 DC
		int(m_tRect.left + 11 + ((m_iOrder-1) * 40)), int(m_tRect.top + m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
		int(22), int(22),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
}

void CInven::Release()
{
}
