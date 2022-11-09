#include "stdafx.h"
#include "LoadingUI.h"

#include "ObjMgr.h"
#include "BmpMgr.h"

CLoadingUI::CLoadingUI()
{
}


CLoadingUI::~CLoadingUI()
{
	Release();
}

void CLoadingUI::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 0.f;
	m_tInfo.fcy = 0.f;
	m_tInfo.fx = 380.f;
	m_tInfo.fy = 310.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;

	// 로딩UI 고유변수
	m_dwTime = GetTickCount();
	m_dwCoolTime = NULL;
	m_tPoint = {};
	m_fSpeed = 0.f;
}

int CLoadingUI::Update()
{
	float x = m_tPoint.x - m_tInfo.fx;
	float y = m_tPoint.y - m_tInfo.fy;
	float fDist = sqrtf((x*x) + (y*y));
	
	float m_fAngle = acosf(x / fDist);
	
	if (m_dwTime + m_dwCoolTime < GetTickCount())
	{
		//if (fDist < -30.f - m_tInfo.fcx / 2.f || m_fSpeed < 0.f)
		if ( m_fSpeed < 0.f)
			return 0;

		if (m_tInfo.fy < m_tPoint.y)
			m_fAngle *= -1;

		if(m_fSpeed > 0.f)
			m_fSpeed -= 0.8f;

		m_tInfo.fx += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fy -= sinf(m_fAngle) * m_fSpeed;

	}


	return 0;
}

void CLoadingUI::LateUpdate()
{
}

void CLoadingUI::Render(HDC hDC)
{
	if (m_dwTime + m_dwCoolTime < GetTickCount())
	{
		CObj::UpdateRect();
		HDC MemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
		GdiTransparentBlt(hDC,
			int(m_tRect.left), int(m_tRect.top),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			MemDC,
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(255, 0, 255));
	}
}

void CLoadingUI::Release()
{
	
}
