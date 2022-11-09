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

	ShowCursor(false);// ���콺 Ŀ���� �׸��� ������ �ִ� �Լ�. 
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Cursor.bmp", L"Cursor");
}

int CMouse::Update()
{
	POINT pt = {};

	GetCursorPos(&pt);// ���콺�� ��	ǥ�� ������ �Լ�. �ִ� ��ũ�� ���� ��ǥ�� ���´�. 
	pt.x += 26;
	pt.y += 28;
					  //��ũ�� ��ǥ���� Ŭ���̾�Ʈ ��ǥ�� ��ȯ �����ش�. 
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
	GdiTransparentBlt(hDC,//����� DC
		m_tRect.left , m_tRect.top,// �׸��� �׸� ���� ��ǥ XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
		hMemDC,// ������ DC 
		0, 0,// ����� ��Ʈ���� ���� ��ǥ 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
		RGB(100, 100, 100));// ���� �������ϴ� ����. 
}

void CMouse::Release()
{
}
