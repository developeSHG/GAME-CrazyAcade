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

	// �κ� ��������
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
		GdiTransparentBlt(hDC,//����� DC
			int(675.f), int(492.f),// �׸��� �׸� ���� ��ǥ XY
			int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
			hMemDC,// ������ DC 
			int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// ����� ��Ʈ���� ���� ��ǥ 
			int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
			RGB(255, 0, 255));// ���� �������ϴ� ����. 
	}
	GdiTransparentBlt(hDC,//����� DC
		int(m_tRect.left + 11 + ((m_iOrder-1) * 40)), int(m_tRect.top + m_tFramePos.y),// �׸��� �׸� ���� ��ǥ XY
		int(22), int(22),// ����� �׸��� ũ�� 
		hMemDC,// ������ DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// ����� ��Ʈ���� ���� ��ǥ 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
		RGB(255, 0, 255));// ���� �������ϴ� ����. 
}

void CInven::Release()
{
}
