#include "stdafx.h"
#include "Mouse.h"

#include "BmpMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 26.f;
	m_tInfo.fcy = 28.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;

	ShowCursor(false);// 마우스 커서를 그릴지 결정해 주는 함수. 
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Cursor.bmp", L"Cursor");
}

int CMouse::Update()
{
	POINT pt = {};

	GetCursorPos(&pt);// 마우스의 좌	표를 얻어오는 함수. 애는 스크린 기준 좌표를 얻어온다. 
	pt.x += 26;
	pt.y += 28;
					  //스크린 좌표에서 클라이언트 좌표로 변환 시켜준다. 
	ScreenToClient(g_hWND, &pt);

	m_tInfo.fx = float(pt.x);
	m_tInfo.fy = float(pt.y);
	return 0;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Cursor");
	GdiTransparentBlt(hDC,//출력할 DC
		m_tRect.left , m_tRect.top,// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		0, 0,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(100, 100, 100));// 내가 빼고자하는 색상. 
}

void CMouse::Release()
{
}
