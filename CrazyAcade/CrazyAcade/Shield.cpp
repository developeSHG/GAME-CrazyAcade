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

	// ���� ��������
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
	GdiTransparentBlt(hDC,//����� DC
		int(m_tRect.left+7), int(m_tRect.top + m_tFramePos.y - 15),// �׸��� �׸� ���� ��ǥ XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
		hMemDC,// ������ DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// ����� ��Ʈ���� ���� ��ǥ 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
		RGB(255, 0, 255));// ���� �������ϴ� ����. 
}

void CShield::Release()
{
}
