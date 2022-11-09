#include "stdafx.h"
#include "Shield.h"

#include "BmpMgr.h"
#include "ObjMgr.h"

CShield::CShield()
{
}


CShield::~CShield()
{
}

void CShield::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 88.5f;
	m_tInfo.fcy = 101.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 0.f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;

	m_pFrameKey = L"ShieldAni";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	// 쉴드 고유변수
	m_dwTime = GetTickCount();
	m_bActive = true;
}

int CShield::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	m_tInfo.fx = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fx;
	m_tInfo.fy = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fy;

	if (m_dwTime + 3000 < GetTickCount())
	{
		m_bActive = false;
	}

	return OBJ_LIVE;
}

void CShield::LateUpdate()
{
	CObj::MoveFrame();
}

void CShield::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"ShieldAni");
	GdiTransparentBlt(hDC,//출력할 DC
		int(m_tRect.left+7), int(m_tRect.top + m_tFramePos.y - 15),// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
}

void CShield::Release()
{
}
