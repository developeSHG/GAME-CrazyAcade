#include "stdafx.h"
#include "Obj.h"
#include "TileMgr.h"

CObj::CObj()
	: m_bIsDead(OBJ_DEAD)
	, m_bIsInit(FALSE)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFactSize, sizeof(POINT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tFrameSize, sizeof(POINT));
	ZeroMemory(&m_tFramePos, sizeof(POINT));
	ZeroMemory(&m_tFrameStart, sizeof(POINT));
	ZeroMemory(&m_tTile_Rc, sizeof(m_tTile_Rc));
}


CObj::~CObj()
{
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fx - (m_tInfo.fcx / 2.f));
	m_tRect.top = LONG(m_tInfo.fy - (m_tInfo.fcy / 2.f));
	m_tRect.right = LONG(m_tInfo.fx + (m_tInfo.fcx / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fy + (m_tInfo.fcy / 2.f));
}

void CObj::MoveFrame()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}

void CObj::MoveFrame(int _StartFrame)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = _StartFrame;
}

void CObj::TileRC_Check()
{
	// 내가 있는 타일 위치체크 (시작)
	vector<CObj*> vecTile = CTileMgr::Get_Instance()->Get_Tile();

	float now_pos = 0;
	for (auto& Tile : vecTile)
	{
		RECT rc = {};
		if (IntersectRect(&rc, &m_tRect, Tile->Get_Rect()))
		{
			float rcx = float(rc.right - rc.left);
			float rcy = float(rc.bottom - rc.top);
			float size = rcx + rcy;

			if (size >= now_pos)
			{
				now_pos = size;
				memcpy(&m_tTile_Rc, Tile->Get_Rect(), sizeof(RECT));
			}
		}
	}
	// 내가 있는 타일 위치체크 (끝)
}
