#include "stdafx.h"
#include "MyBanner.h"

#include "BmpMgr.h"

CMyBanner::CMyBanner()
{
}


CMyBanner::~CMyBanner()
{
	Release();
}

void CMyBanner::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 283.f;
	m_tInfo.fcy = 88.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;

	
	m_bActive = true;
}

int CMyBanner::Update()
{
	return 0;
}

void CMyBanner::LateUpdate()
{
}

void CMyBanner::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC MemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (true == m_bActive && L"Color_Check" != m_pFrameKey)
	{
		BitBlt(hDC, int(m_tRect.left), int(m_tRect.top), int(m_tInfo.fcx), int(m_tInfo.fcy), MemDC, 0, 0, SRCCOPY);
	}
	else if (L"Color_Check" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,//����� DC
			int(m_tRect.left), int(m_tRect.top + m_tFramePos.y),// �׸��� �׸� ���� ��ǥ XY
			int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
			MemDC,// ������ DC 
			int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// ����� ��Ʈ���� ���� ��ǥ 
			int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
			RGB(255, 0, 255));// ���� �������ϴ� ����. 
	}
}

void CMyBanner::Release()
{
}
