#include "stdafx.h"
#include "Dart.h"

#include "BmpMgr.h"

CDart::CDart()
{
}


CDart::~CDart()
{
}

void CDart::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 0.f;
	m_tInfo.fcy = 0.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 13.f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;

	// 다트 고유변수
	m_eDir = PLAYER::FRONT;
}

int CDart::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case PLAYER::FRONT:
	case PLAYER::FRONT_NONE:
		m_pFrameKey = L"DartShot_Down";
		m_tInfo.fy += m_fSpeed;
		m_tInfo.fcx = 15.f;
		m_tInfo.fcy = 25.f;
		break;
	case PLAYER::LEFT:
	case PLAYER::LEFT_NONE:
		m_pFrameKey = L"DartShot_Right";
		m_tInfo.fx -= m_fSpeed;
		m_tInfo.fcx = 25.f;
		m_tInfo.fcy = 15.f;
		break;
	case PLAYER::RIGHT:
	case PLAYER::RIGHT_NONE:
		m_pFrameKey = L"DartShot_Left";
		m_tInfo.fx += m_fSpeed;
		m_tInfo.fcx = 25.f;
		m_tInfo.fcy = 15.f;
		break;
	case PLAYER::BACK:
	case PLAYER::BACK_NONE:
		m_pFrameKey = L"DartShot_Up";
		m_tInfo.fy -= m_fSpeed;
		m_tInfo.fcx = 15.f;
		m_tInfo.fcy = 25.f;
		break;
	}

	return OBJ_LIVE;
}

void CDart::LateUpdate()
{
}

void CDart::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//출력할 DC
		int(m_tRect.left), int(m_tRect.top + m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
}

void CDart::Release()
{
}
