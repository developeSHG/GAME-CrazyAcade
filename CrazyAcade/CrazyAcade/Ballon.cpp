#include "stdafx.h"
#include "Ballon.h"

#include "Stem.h"
#include "Block.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBallon::CBallon()
{
}


CBallon::~CBallon()
{	
	Release();
}

void CBallon::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 10.f;
	m_bBallonOn = true;
	m_bBubbleState = false;
	m_bPushState = false;

	// 물풍선 고유변수
	m_dwCreateTime = GetTickCount();
	m_uPower = 1;
	m_eDir = BALLON::NONE;
	m_bDirCheck = false;
	m_eThrowDir = BALLON::NONE;
	m_bThrowState = false;
	m_bTeleState = false;
	for (int i = 0; i < BALLON::DOWN + 1; ++i)
		m_eStemDeleteDir[i] = false;
	m_fDistX = 0;
	fThrowJump = 5.f;
	m_fThrowOriginY = 0;
	m_bThrowChange = false;
	m_bTimerState = false;
	m_bWithState = false;
	m_bBossBallon = false;

	m_pFrameKey = L"Ballon1";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 125;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CBallon::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (GetAsyncKeyState('D'))
		m_bTimerState = false;
	if (m_dwCreateTime + 1800 < GetTickCount() && false == m_bTimerState || true == m_bBubbleState)
	{
		CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(0, STEM::CENTER));
		for (size_t i = 1; i < m_uPower+1; ++i)
		{
			if(false == m_eStemDeleteDir[BALLON::LEFT])
				CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::LEFT));
			if (false == m_eStemDeleteDir[BALLON::UP])
				CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::UP));
			if (false == m_eStemDeleteDir[BALLON::RIGHT])
				CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::RIGHT));
			if (false == m_eStemDeleteDir[BALLON::DOWN])
				CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::DOWN));
		}
		m_bIsDead = OBJ_DEAD;
	}

	if (false == m_bTimerState)
		m_tFrame.iFrameEnd = 3;
	if (true == m_bTimerState)
		m_tFrame.iFrameEnd = 2;
	


	if (true == m_bPushState && false == m_bDirCheck)
	{	
		// 물풍선 밀림(시작)
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

		float pX = pPlayer->Get_Info().fx;
		float pY = pPlayer->Get_Info().fy;

		//RECT rc = {};
		//if (IntersectRect(&rc, pPlayer->Get_Rect(), &m_tRect))
		//{
		//	LONG x = rc.right - rc.left;
		//	LONG y = rc.bottom - rc.top;

		//	if (x > (m_tInfo.fcx / 1.5f) || y > (m_tInfo.fcy / 1.5f))
		//	{
		//		if (x > y)
		//		{
		//			if (x > (m_tInfo.fcx / 1.5f))
		//			{
		//				if (pPlayer->Get_Info().fy < m_tInfo.fy)
		//					m_eDir = BALLON::DOWN;
		//				else
		//					m_eDir = BALLON::UP;
		//			}
		//		}
		//		else if (x < y)
		//		{
		//			if (y > (m_tInfo.fcy / 1.5f))
		//			{
		//				if (pPlayer->Get_Info().fx < m_tInfo.fx)
		//					m_eDir = BALLON::RIGHT;
		//				else
		//					m_eDir = BALLON::LEFT;
		//			}
		//		}
		//	}
		//}
		RECT rc = {};
		if (IntersectRect(&rc, pPlayer->Get_Rect(), &m_tTile_Rc))
		{
			long x = rc.right - rc.left;
			long y = rc.bottom - rc.top;
			CSoundMgr::Get_Instance()->MyPlaySound(L"Kick.wav", CSoundMgr::PLAYER);
			if (y > x)
			{
				if(pPlayer->Get_Rect()->right+3 >= m_tTile_Rc.left && pPlayer->Get_Info().fx < m_tInfo.fx)
					m_eDir = BALLON::RIGHT;
				else if(pPlayer->Get_Rect()->left-3 <= m_tTile_Rc.right  && pPlayer->Get_Info().fx > m_tInfo.fx)
					m_eDir = BALLON::LEFT;
			}
			else if (x > y)
			{
				if (pPlayer->Get_Rect()->top-3 <= m_tTile_Rc.bottom  && pPlayer->Get_Info().fy > m_tInfo.fy)
					m_eDir = BALLON::UP;
				else if (pPlayer->Get_Rect()->bottom+3 >= m_tTile_Rc.top  && pPlayer->Get_Info().fy < m_tInfo.fy)
					m_eDir = BALLON::DOWN;
			}
		}

		m_bDirCheck = true;
		// 물풍선 밀림(끝)
	}

	switch (m_eDir)
	{
	case BALLON::LEFT:
		m_tInfo.fx -= m_fSpeed;
		break;
	case BALLON::UP:
		m_tInfo.fy -= m_fSpeed;
		break;
	case BALLON::RIGHT:
		m_tInfo.fx += m_fSpeed;
		break;
	case BALLON::DOWN:
		m_tInfo.fy += m_fSpeed;
		break;
	}

	// 물풍선 던져짐 (시작)
	if (true == m_bThrowState)
	{
		m_dwCreateTime = GetTickCount();
		switch (m_eThrowDir)
		{
		case BALLON::LEFT:
			if (m_fDistX <= TILE_SIZE_X * 8)
			{
				m_fDistX += fThrowJump + 3;
				m_tInfo.fx -= fThrowJump + 3;

				if (m_bThrowChange == false)
				{
					m_tInfo.fy -= fThrowJump;
					if (m_tTile_Rc.bottom >= m_tInfo.fy + 40.f)
					{
						m_bThrowChange = true;
					}
				}
				else if (m_bThrowChange == true)
				{
					m_tInfo.fy += fThrowJump;
					if (m_tTile_Rc.bottom <= m_tInfo.fy + 20.f)
					{
						m_bThrowChange = false;
					}
				}
			}
			break;
		case BALLON::UP:
			if (m_fDistX <= TILE_SIZE_Y * 8)
			{
				m_fDistX += fThrowJump + 3;
				m_tInfo.fy -= fThrowJump + 3;

			}
			break;
		case BALLON::RIGHT:
			if (m_fDistX <= TILE_SIZE_X * 8)
			{
				m_fDistX += fThrowJump+3;
				m_tInfo.fx += fThrowJump+3;

				if (m_bThrowChange == false)
				{
					m_tInfo.fy -= fThrowJump;
					if (m_tTile_Rc.bottom >= m_tInfo.fy + 40.f)
					{
						m_bThrowChange = true;
					}
				}
				else if(m_bThrowChange == true)
				{
					m_tInfo.fy += fThrowJump;
					if (m_tTile_Rc.bottom <= m_tInfo.fy + 20.f)
					{
						m_bThrowChange = false;
					}
				}
			}
			break;
		case BALLON::DOWN:
			if (m_fDistX <= TILE_SIZE_Y * 8)
			{
				m_fDistX += fThrowJump + 3;
				m_tInfo.fy += fThrowJump + 3;
			}
			break;
		}
		if (m_fDistX >= TILE_SIZE_X * 8)
		{
			if(BALLON::LEFT == m_eThrowDir || BALLON::RIGHT == m_eThrowDir)
				m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y/2.f;

			m_bThrowState = false;
			m_fDistX = 0;
			m_dwCreateTime = GetTickCount();
		}
	}
	// 물풍선 던져짐 (끝)

	return OBJ_LIVE;
}

void CBallon::LateUpdate()
{
	// 물풍선 최대파워 제한 (시작)
	if (m_uPower > 6)
		m_uPower = 6;
	// 물풍선 최대파워 제한 (끝)

	Overlap();
	CObj::MoveFrame();
}

void CBallon::Render(HDC hDC)
{
	CObj::UpdateRect();
	if (false == m_bThrowState)
		CObj::TileRC_Check();

	/*if (m_tRect.left < 0 || m_tRect.right > MAP_X || m_tRect.top < 0 || m_tRect.bottom > MAP_Y)
		return;*/

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);

	RECT rc = {};
	list<CObj*>* plistBlock = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
	for (auto& pBlock : *plistBlock)
	{
		if (IntersectRect(&rc, &m_tTile_Rc, &pBlock->Get_TileRC()) && false == m_bThrowState)
		{
			if (BLOCK::HIDE == SCAST<CBlock*>(pBlock)->Get_Property())
			{
				return;
			}
		}
	}
	if (L"Ballon1" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,//출력할 DC
			m_tRect.left, m_tRect.top - 3,// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx + 6), int(m_tInfo.fcy + 6),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx + 6) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx + 6), int(m_tInfo.fcy + 6),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(0, 0, 0));// 내가 빼고자하는 색상. 
	}
	else if (L"Ballon2" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,//출력할 DC
			int(m_tRect.left-3.f), int(m_tRect.top - TILE_SIZE_Y/2.f),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx + 7), int(m_tInfo.fcy + 21),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx + 7) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx+7), int(m_tInfo.fcy+21),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 
	}
	else if (L"TimerBallon" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,//출력할 DC
			int(m_tRect.left), int(m_tRect.top),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx + 5), int(m_tInfo.fcy + 3),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx + 5) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx + 5), int(m_tInfo.fcy + 3),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 
	}
	else if (L"Ballon3" == m_pFrameKey)
	{
		GdiTransparentBlt(hDC,//출력할 DC
			int(m_tRect.left - 2.f), int(m_tRect.top - TILE_SIZE_Y / 2.f),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx + 4), int(m_tInfo.fcy + 1),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx + 4) * m_tFrame.iFrameStart), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx + 4), int(m_tInfo.fcy + 1),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 
	}
}

void CBallon::Release()
{

}

void CBallon::LateInit()
{
	m_eDir = BALLON::NONE;
}

CObj* CBallon::Create_Stem(size_t _uPower, STEM::DIR _eDir)
{
	CObj* pStem = nullptr;
	
	if (true == m_eStemDeleteDir[_eDir])
		return nullptr;

	float x = m_tInfo.fx;
	float y = m_tInfo.fy;
	RECT rc_Stem = {};
	rc_Stem.left = LONG(m_tRect.left);
	rc_Stem.top = LONG(m_tRect.top);
	rc_Stem.right = LONG(m_tRect.right);
	rc_Stem.bottom = LONG(m_tRect.bottom);
	switch (_eDir)
	{
	case STEM::LEFT:
		x -= _uPower * TILE_SIZE_X;
		rc_Stem.left = LONG(x - TILE_SIZE_X / 2.f);
		break;
	case STEM::UP:
		y -= _uPower * TILE_SIZE_Y;
		rc_Stem.top = LONG(y - TILE_SIZE_Y / 2.f);
		break;
	case STEM::RIGHT:
		x += _uPower * TILE_SIZE_X;
		rc_Stem.right = LONG(x + TILE_SIZE_X / 2.f);
		break;
	case STEM::DOWN:
		y += _uPower * TILE_SIZE_Y;
		rc_Stem.bottom = LONG(y + TILE_SIZE_Y / 2.f);
		break;
	}

	list<CObj*>* plistBlock = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);

	for (auto& pBlock : *plistBlock)
	{
		RECT rc = {};
		if (BLOCK::DUNKS != SCAST<CBlock*>(pBlock)->Get_Property()
			&& BLOCK::TELEPORT1 != SCAST<CBlock*>(pBlock)->Get_Property() && BLOCK::TELEPORT2 != SCAST<CBlock*>(pBlock)->Get_Property()
			&& BLOCK::TELEPORT3 != SCAST<CBlock*>(pBlock)->Get_Property() && BLOCK::TELEPORT4 != SCAST<CBlock*>(pBlock)->Get_Property()
			&&  BLOCK::WITH != SCAST<CBlock*>(pBlock)->Get_Property())
		{
			if (IntersectRect(&rc, pBlock->Get_Rect(), &m_tRect))
			{
				if (BLOCK::THORN == SCAST<CBlock*>(pBlock)->Get_Property())
				{
					if (0 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						m_eStemDeleteDir[STEM::UP] = true;
					else if (1 == SCAST<CBlock*>(pBlock)->Get_DrawID())
					{
						if (m_tRect.left <= pBlock->Get_Rect()->right)
							m_eStemDeleteDir[STEM::LEFT] = true;
						else if (m_tRect.right >= pBlock->Get_Rect()->left)
							m_eStemDeleteDir[STEM::RIGHT] = true;
						else if (m_tRect.top <= pBlock->Get_Rect()->bottom)
							m_eStemDeleteDir[STEM::UP] = true;
						else if (m_tRect.bottom >= pBlock->Get_Rect()->top)
							m_eStemDeleteDir[STEM::DOWN] = true;
					}
					else if (2 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						m_eStemDeleteDir[STEM::DOWN] = true;
					else if (3 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						m_eStemDeleteDir[STEM::RIGHT] = true;
					else if (4 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						m_eStemDeleteDir[STEM::LEFT] = true;
					else if (5 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						continue;
					continue;
				}
			}
			if (IntersectRect(&rc, pBlock->Get_Rect(), &rc_Stem))
			{
				if (BLOCK::BASIC == SCAST<CBlock*>(pBlock)->Get_Property()
					|| BLOCK::PUSH == SCAST<CBlock*>(pBlock)->Get_Property())
				{
					m_eStemDeleteDir[_eDir] = true;
					pBlock->Set_Dead();
					SCAST<CBlock*>(pBlock)->Create_Item();
				}
				else if (BLOCK::HIDE == SCAST<CBlock*>(pBlock)->Get_Property())
				{
					pBlock->Set_Dead();
					continue;
				}
				else if (BLOCK::THORN == SCAST<CBlock*>(pBlock)->Get_Property())
				{
					if (5 == SCAST<CBlock*>(pBlock)->Get_DrawID())
						continue;
				}
				else {
					m_eStemDeleteDir[_eDir] = true;
				}
				return nullptr;
			}
		}
	}

	pStem = CAbstractFactory<CStem>::Create(x, y);

	if (BALLON::LEFT == _eDir && m_uPower == _uPower)
		dynamic_cast<CStem*>(pStem)->Set_Dir(STEM::LEFT_LAST);
	else if (BALLON::RIGHT == _eDir && m_uPower == _uPower)
		dynamic_cast<CStem*>(pStem)->Set_Dir(STEM::RIGHT_LAST);
	else if (BALLON::UP == _eDir && m_uPower == _uPower)
		dynamic_cast<CStem*>(pStem)->Set_Dir(STEM::UP_LAST);
	else if (BALLON::DOWN == _eDir && m_uPower == _uPower)
		dynamic_cast<CStem*>(pStem)->Set_Dir(STEM::DOWN_LAST);
	else
		dynamic_cast<CStem*>(pStem)->Set_Dir(_eDir);

	if (true == m_bBossBallon)
		dynamic_cast<CStem*>(pStem)->Set_BossStem();

	return pStem;
}

void CBallon::Overlap()
{
	list<CObj*>* plistBallon = CObjMgr::Get_Instance()->Get_Obj(OBJID::BALLON);

	if (false == m_bThrowState)
	{
		for (auto& pBallon : *plistBallon)
		{
			float fDistX = fabs(pBallon->Get_Info().fx - m_tInfo.fx);
			float fDistY = fabs(pBallon->Get_Info().fy - m_tInfo.fy);

			float fRadiusX = (pBallon->Get_Info().fcx / 2.f) + (m_tInfo.fcx / 2.f);
			float fRadiusY = (pBallon->Get_Info().fcy / 2.f) + (m_tInfo.fcy / 2.f);
			//float fRadiusX = TILE_SIZE_X;
			//float fRadiusY = TILE_SIZE_Y;

			if (fDistX < fRadiusX && fDistY < fRadiusY)
			{
				float fMoveX = fRadiusX - fDistX;
				float fMoveY = fRadiusY - fDistY;

				if (fMoveX > fMoveY)
				{
					if (pBallon->Get_Info().fy > m_tInfo.fy)
						fMoveY *= -1;

					pBallon->Set_Pos(pBallon->Get_Info().fx, pBallon->Get_Info().fy - fMoveY);
					SCAST<CBallon*>(pBallon)->Set_Speed(0);
				}
				else if (fMoveX < fMoveY)
				{
					if (pBallon->Get_Info().fx > m_tInfo.fx)
						fMoveX *= -1;

					pBallon->Set_Pos(pBallon->Get_Info().fx - fMoveX, pBallon->Get_Info().fy);
					SCAST<CBallon*>(pBallon)->Set_Speed(0);
				}
			}
		}
	}
}

void CBallon::ThrowActive()
{
}

