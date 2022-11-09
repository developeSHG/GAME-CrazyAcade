#include "stdafx.h"
#include "Stem.h"

#include "BmpMgr.h"

CStem::CStem()
{
}


CStem::~CStem()
{
	Release();
}

void CStem::Initialize()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"Stem.wav", CSoundMgr::PLAYER);

	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 40.f;
	m_tInfo.fcy = 40.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;

	// 물줄기 고유변수
	m_eDir = STEM::CENTER;
	m_dwCreateTime = GetTickCount();
	m_bBossStem = false;

	m_pFrameKey = L"Stem_Center";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 0;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CStem::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	
	if (m_dwCreateTime + 500 < GetTickCount())
		m_bIsDead = OBJ_DEAD;

	return OBJ_LIVE;
}

void CStem::LateUpdate()
{
	CObj::LateInit();
	CObj::MoveFrame();
}

void CStem::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::TileRC_Check();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (m_tRect.left < POINT_X || m_tRect.right > MAP_X+POINT_X || m_tRect.top < POINT_Y || m_tRect.bottom > MAP_Y + POINT_Y)
	{
		m_bIsDead = OBJ_DEAD;
		return;
	}

	//// 가운데
	//switch (m_eDir)
	//{
	//case STEM::CENTER:
	//	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//	break;
	//case STEM::LEFT:
	//	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//	break;
	//case STEM::UP:
	//	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//	break;
	//case STEM::RIGHT:
	//	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//	break;
	//case STEM::DOWN:
	//	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//	break;
	//}

	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//출력할 DC
		m_tRect.left, m_tRect.top,// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int(m_tInfo.fcx * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(0, 0, 0));// 내가 빼고자하는 색상. 

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		Rectangle(hDC, m_tTile_Rc.left, m_tTile_Rc.top, m_tTile_Rc.right, m_tTile_Rc.bottom);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CStem::Release()
{
}

void CStem::LateInit()
{
	SceneChane();
}

void CStem::SceneChane()
{
	switch (m_eDir)
	{
	case STEM::CENTER:
		m_pFrameKey = L"Stem_Center";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 2;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::LEFT:
		m_pFrameKey = L"Stem_Left";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::UP:
		m_pFrameKey = L"Stem_Up";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::RIGHT:
		m_pFrameKey = L"Stem_Right";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::DOWN:
		m_pFrameKey = L"Stem_Down";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::LEFT_LAST:
		m_pFrameKey = L"Stem_LeftLast";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::UP_LAST:
		m_pFrameKey = L"Stem_UpLast";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::RIGHT_LAST:
		m_pFrameKey = L"Stem_RightLast";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case STEM::DOWN_LAST:
		m_pFrameKey = L"Stem_DownLast";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}
}
