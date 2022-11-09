#include "stdafx.h"
#include "Item.h"

#include "BmpMgr.h"

CItem::CItem()
{
}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 38.f;
	m_tInfo.fcy = 38.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 0.15f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;

	m_pFrameKey = L"Item";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 125;
	m_tFrame.dwFrameTime = GetTickCount();

	// 아이템 고유변수
	m_bInPlace = false;
	m_fPos = 0;
	m_dwCreateTime = GetTickCount();
	m_bCreateCheck = false;
}

int CItem::Update()
{
	if (m_bIsDead || true == m_bBubbleState)
		return OBJ_DEAD;

	if (m_dwCreateTime + 2000 < GetTickCount())
		m_bCreateCheck = true;

	switch (m_eProperty)
	{
	case ITEM::WATER:
		m_pFrameKey = L"Water";
		break;
	case ITEM::POWER:
		m_pFrameKey = L"Power";
		break;
	case ITEM::ROLLER:
		m_pFrameKey = L"Roller";
		break;
	case ITEM::GLOVE:
		m_pFrameKey = L"Glove";
		break;
	case ITEM::GAS:
		m_pFrameKey = L"Gas";
		break;
	case ITEM::FLY:
		m_pFrameKey = L"Fly";
		break;
	case ITEM::SHOES:
		m_pFrameKey = L"Shoes";
		break;
	case ITEM::NEEDLE:
		m_pFrameKey = L"Needle";
		break;
	case ITEM::DART:
		m_pFrameKey = L"Dart";
		break;
	case ITEM::DEVIL:
		m_pFrameKey = L"Devil";
		break;
	case ITEM::TIMER:
		m_pFrameKey = L"Timer";
		break;
	case ITEM::SHIELD:
		m_pFrameKey = L"Shield";
		break;
	case ITEM::SPACE:
		m_pFrameKey = L"Space";
		break;
	case ITEM::TURTLE:
		m_pFrameKey = L"Turtle";
		break;
	case ITEM::OWL:
		m_pFrameKey = L"Owl";
		break;
	case ITEM::TANK:
		m_pFrameKey = L"Tank";
		break;
	case ITEM::BANANA:
		m_pFrameKey = L"Banana";
		break;
	case ITEM::BLACKBALLON:
		m_pFrameKey = L"BlackBallon";
		break;
	case ITEM::WING:
		m_pFrameKey = L"Wing";
		break;
	}

	return OBJ_LIVE;
}

void CItem::LateUpdate()
{
	if (false == m_bInPlace)
	{	
		if (m_fPos > -10.f)
		{
			m_fPos -= m_fSpeed;
			m_tInfo.fy -= m_fSpeed;
		}
		else
		{
			m_bInPlace = true;
			m_fPos = 0;
		}
	}
	else
	{
		if (m_fPos < 10.f)
		{
			m_fPos += m_fSpeed;
			m_tInfo.fy += m_fSpeed;
		}
		else
		{
			m_bInPlace = false;
			m_fPos = 0;
		}
	}

	CObj::MoveFrame();
}

void CItem::Render(HDC hDC)
{
	// 내가 있는 타일 위치체크 (시작)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	// 내가 있는 타일 위치체크 (끝)

	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,//출력할 DC
		int(m_tRect.left), int(m_tRect.top),// 그림을 그릴 시작 좌표 XY
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		hMemDC,// 복사할 DC 
		int((m_tInfo.fcx) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		RGB(255, 0, 255));// 내가 빼고자하는 색상. 
}

void CItem::Release()
{
}

