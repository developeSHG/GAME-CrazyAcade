#include "stdafx.h"
#include "Acting.h"

#include "BmpMgr.h"

CActing::CActing()
{
}


CActing::~CActing()
{
}

void CActing::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"Acting.wav", CSoundMgr::UI);
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y+4;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;

	m_pFrameKey = L"Acting";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 125;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CActing::Update()
{
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
	{
		m_bIsDead = OBJ_DEAD;
		return OBJ_DEAD;
	}
	return 0;
}

void CActing::LateUpdate()
{
	CObj::MoveFrame();
}

void CActing::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//출력할 DC
		m_tRect.left, m_tRect.top,// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx ), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx ) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 


}

void CActing::Release()
{
}
