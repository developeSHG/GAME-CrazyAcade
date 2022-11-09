#include "stdafx.h"
#include "Player.h"

#include "Acting.h"
#include "Ballon.h"
#include "Shield.h"
#include "Dart.h"
#include "Item.h"
#include "Inven.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tFactSize.x = 0;
	m_tFactSize.y = 0;
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X - float(m_tFactSize.x);
	m_tInfo.fcy = TILE_SIZE_Y - float(m_tFactSize.y);
	m_tInfo.fx = 80.f;
	m_tInfo.fy = 100.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = GetTickCount();
	m_fSpeed = 3.f;
	m_bBallonOn = false;
	m_bBubbleState = false;
	m_bPushState = false;
	m_pBallonFrame = L"Ballon1";
	m_uBallonPower = 1;
	m_eOnItem = ITEM::END;
	m_bOnItem = false;
	m_bCreateTime = GetTickCount();

	m_eNextState = PLAYER::FRONT;
	m_pFrameKey = L"Walk_Front";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 0;
	m_tFrame.dwFrameTime = NULL;

	// 플레이어 고유변수
	m_dwBallonCoolTime = NULL;
	m_iBallonMaxNum = 1;
	m_dwBubbleTime = NULL;
	m_bHideState = false;
	m_dwHideTime = NULL;
	m_bLeapActive = false;
	m_bLeapCheck = false;
	m_fLeapActivePos = 0;
	iLeapBlockNum = 0;
	m_fJumpPower = -15.f;
	m_pBallonFrame = L"Ballon1";
	m_pItemFrame = NULL;
	m_bThrowState = false;
	m_bShieldState = false;
	m_bNeedleState = false;
	m_bTimerState = false;
	m_iTimerBallonNum = 0;
	m_bBananaState = false;
	m_bWingState = false;
	m_iOrder = 1;
	m_bBoardState = false;
	m_fBoardJumpPower = -3.3f;
	m_iSummonsItem = ITEM::WATER;
	m_dwInvinTime = 0;
	m_bInvinState = false;
	m_bDieState = false;
}

int CPlayer::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	
	
	if (m_dwGameStartTime + GAME_START_TIME < GetTickCount())
	{
		if (PLAYER::BUBBLE1 != m_eNextState && PLAYER::BUBBLE2 != m_eNextState &&  PLAYER::BUBBLE3 != m_eNextState && false == m_bLeapCheck && false == m_bBoardState)
		{
			// 키 움직임 (시작)
			if(PLAYER::DIE1 != m_eNextState && PLAYER::DIE2 != m_eNextState)
				 WalkActive();
			// 키 움직임 (끝)

			// 물풍선 생성 (시작)
			if (GetAsyncKeyState(VK_SPACE) && false == m_bBubbleState && false == m_bTimerState && PLAYER::TANKON != m_eNextState)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Ballon.wav", CSoundMgr::PLAYER);
				size_t BallonAmount = CObjMgr::Get_Instance()->Get_BallonAmount();
				if (BallonAmount < m_iBallonMaxNum && false == m_bBallonOn && m_dwBallonCoolTime + 200< GetTickCount())
				{	
					CObjMgr::Get_Instance()->AddObject(OBJID::BALLON, Create_Ballon());
					m_bBallonOn = true;
					m_dwBallonCoolTime = GetTickCount();
				}
			}
			else if (GetAsyncKeyState(VK_SPACE) && false == m_bBubbleState && true == m_bTimerState)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Ballon.wav", CSoundMgr::PLAYER);
				if (m_iTimerBallonNum < m_iBallonMaxNum && false == m_bBallonOn && m_dwBallonCoolTime + 200< GetTickCount())
				{
					CObjMgr::Get_Instance()->AddObject(OBJID::BALLON, Create_Ballon());
					m_bBallonOn = true;
					m_dwBallonCoolTime = GetTickCount();
					++m_iTimerBallonNum;
				}
				else if (m_iTimerBallonNum >= m_iBallonMaxNum)
				{
					m_iTimerBallonNum = 0;
					m_bTimerState = false;
				}
			}
			else if (GetAsyncKeyState(VK_SPACE) && PLAYER::TANKON == m_eNextState)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Ballon.wav", CSoundMgr::PLAYER);	
				size_t BallonAmount = CObjMgr::Get_Instance()->Get_BallonAmount();
				if (BallonAmount < 15 && false == m_bBallonOn && m_dwBallonCoolTime + 200< GetTickCount())
				{
					CObjMgr::Get_Instance()->AddObject(OBJID::BALLON, Create_Ballon());
					m_bBallonOn = true;
					m_dwBallonCoolTime = GetTickCount();

				}
				list<CObj*>* m_plistBallon = CObjMgr::Get_Instance()->Get_Obj(OBJID::BALLON);
				RECT rc = {};
				for (auto& pBallon : *m_plistBallon)
				{
					if (IntersectRect(&rc, &m_tRect, pBallon->Get_Rect()))
					{
						//SCAST<CBallon*>(pBallon)->Set_PushState(true);
						if (L"Tank_Left" == m_pFrameKey)
							SCAST<CBallon*>(pBallon)->Set_TankPush(BALLON::LEFT);
						else if (L"Tank_Back" == m_pFrameKey)
							SCAST<CBallon*>(pBallon)->Set_TankPush(BALLON::UP);
						else if (L"Tank_Right" == m_pFrameKey)
							SCAST<CBallon*>(pBallon)->Set_TankPush(BALLON::RIGHT);
						else if (L"Tank_Front" == m_pFrameKey)
							SCAST<CBallon*>(pBallon)->Set_TankPush(BALLON::DOWN);
					}
				}
			}
			// 물풍선 생성 (끝)

			// 물풍선 던지기 (시작)
			else if (true == m_bBallonOn && false == m_bBubbleState && true == m_bThrowState || GetAsyncKeyState('A'))
			{
 				if (GetAsyncKeyState('A'))
				{
					CSoundMgr::Get_Instance()->MyPlaySound(L"Kick.wav", CSoundMgr::PLAYER);
					list<CObj*>* m_plistBallon = CObjMgr::Get_Instance()->Get_Obj(OBJID::BALLON);
					RECT rc = {};
					for (auto& pBallon : *m_plistBallon)
					{
						if (IntersectRect(&rc, &m_tRect, pBallon->Get_Rect()))
						{
							ThrowActive(pBallon);
						}
					}
				}
			}
			// 물풍선 던지기 (끝)
		}

		// 블럭 뛰어넘기 (시작)
		BlockLeapCheck();
		// 블럭 뛰어넘기 (끝)

		// 버블상태 (시작)
		if (true == m_bBubbleState)
		{
			CObj::LateInit();
			static int i = 0;

			if (i == 0)
			{
				m_eNextState = PLAYER::BUBBLE1;
				m_pFrameKey = L"Bubble1";
			}
			if (true == m_bNeedleState || CKeyMgr::Get_Instance()->KeyDown('O'))
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Needle.wav", CSoundMgr::PLAYER);
				i = 0;
				m_eNextState = PLAYER::NEEDLE;
				m_pFrameKey = L"Bubble_Needle";

				m_bBubbleState = false;
				m_bIsInit = false;
				m_bBallonOn = false;
				m_dwBubbleTime = NULL;
				m_bNeedleState = false;
				m_bDieState = false;
			}
			else if (m_dwBubbleTime + 700 < GetTickCount() && i == 0)
			{
				m_eNextState = PLAYER::BUBBLE2;
				m_pFrameKey = L"Bubble2";
				i++;
			}
			else if (m_dwBubbleTime + 1400 < GetTickCount() && i == 1)
			{
				m_eNextState = PLAYER::BUBBLE3;
				m_pFrameKey = L"Bubble3";
				i++;
			}
			else if (m_dwBubbleTime + 2100 < GetTickCount() && i == 2 && PLAYER::DIE2 != m_eNextState)
			{
				
				m_eNextState = PLAYER::DIE1;
				m_pFrameKey = L"Die1";
				//m_eNextState = PLAYER::FRONT_NONE;
				//if(false == m_bBananaState && false == m_bWingState)
				//	m_pFrameKey = L"Walk_Front";
				//else if (true == m_bBananaState && false == m_bWingState)
				//	m_pFrameKey = L"Ba_Walk_Front";
				//else if (false == m_bBananaState && true == m_bWingState)
				//	m_pFrameKey = L"Wing_Walk_Front";
	
				//m_bBubbleState = false;
				//m_bIsInit = false;
				//m_bBallonOn = false;
				//m_dwBubbleTime = NULL;
			}
		}
		// 버블상태 (끝)
	}

	// 죽음상태 애니메이션 (시작)
	if (PLAYER::DIE1 == m_eNextState)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eNextState = PLAYER::DIE2;
			m_pFrameKey = L"Die2";
			m_bDieState = true;
		}
	}
	// 죽음상태 애니메이션 (끝)


	// 아이템 충돌 (시작)
	Set_Item();
	// 아이템 충돌 (끝)

	// 아이템 탑승 (시작)
	Board_Item();
	// 아이템 탑승 (끝)

	return OBJ_LIVE;
}

void CPlayer::LateUpdate()
{
	if (false == m_bBubbleState)
	{
		// 하이드블럭 상태 빠져나오기 (시작)
		if (true == m_bHideState)
		{
			CObj::LateInit();
			if (m_dwHideTime + 300 < GetTickCount())
			{
				if (GetAsyncKeyState(VK_LEFT))
					m_tInfo.fx -= 27.f;
				else if (GetAsyncKeyState(VK_RIGHT))
					m_tInfo.fx += 27.f;
				else if (GetAsyncKeyState(VK_UP))
					m_tInfo.fy -= 27.f;
				else if (GetAsyncKeyState(VK_DOWN))
					m_tInfo.fy += 27.f;

				if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN))
					m_bHideState = false;
			}
		}
		else
		{
			m_bIsInit = false;
			m_dwHideTime = NULL;
		}
		// 하이드블럭 상태 빠져나오기 (끝)
	}

	// 아이템 장착 (시작)
	Use_Item();
	// 아이템 장착 (끝)

	// 실드상태 풀기 (시작)
	for (auto& pShield : *CObjMgr::Get_Instance()->Get_Obj(OBJID::SHIELD))
	{
		if (false == SCAST<CShield*>(pShield)->Get_Active())
		{
			m_bShieldState = false;
			pShield->Set_Dead();
		}
	}
	// 실드상태 풀기 (끝)

	// 바늘 프레임 한번만 하고 중단, 무적상태 (시작)
	if (L"Bubble_Needle" == m_pFrameKey && m_bInvinState == false)
	{
		m_dwInvinTime = GetTickCount();
		m_bInvinState = true;
		m_tFrame.iFrameStart = 0;
	}

	if (true == m_bInvinState)
	{
		if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
		{
			m_eNextState = PLAYER::FRONT_NONE;

			if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Walk_Front";
			else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Ba_Walk_Front";
			else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Wing_Walk_Front"; 

			if (m_dwInvinTime + 750 < GetTickCount())
			{
				m_bInvinState = false;
				m_dwInvinTime = 0;
			}
		}
	}
	// 바늘 프레임 한번만 하고 중단, 무적상태 (끝)

	if (true == CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER)->empty() && CSceneMgr::SCENEID::SCENE_STAGE0 != CSceneMgr::Get_Instance()->Get_SceneID()
		&& true == CObjMgr::Get_Instance()->Get_Obj(OBJID::BOSS)->empty())
	{
		m_eNextState = PLAYER::WIN;
		m_pFrameKey = L"Win";
	}


	// 아이템 소환 치트키 (시작)
	if (CKeyMgr::Get_Instance()->KeyDown('W'))
		Summons_Item();
	if (CKeyMgr::Get_Instance()->KeyDown('E'))
		++m_iSummonsItem;
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
		--m_iSummonsItem;

	if (m_iSummonsItem >= ITEM::END)
		m_iSummonsItem = 0;
	else if (m_iSummonsItem < 0)
		m_iSummonsItem = ITEM::END - 1;
	// 아이템 소환 치트키 (끝)


	SceneChange();
	CObj::MoveFrame();

}

void CPlayer::Render(HDC hDC)
{
	// 내가 있는 타일 위치체크 (시작)
	CObj::UpdateRect();
	if(false == m_bLeapCheck)
		CObj::TileRC_Check();
	// 내가 있는 타일 위치체크 (끝)

	if (true == m_bHideState)
		return;

	if (true == m_bActingCreate && false == m_bHideState)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
		if (false == m_bBubbleState && L"Bubble_Needle" == m_pFrameKey)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - 15 - m_tFactSize.x / 2, m_tRect.top - 30 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 29 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 29 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 29 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 29 + m_tFactSize.x), int(m_tInfo.fcy + 29 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (false == m_bBubbleState && L"Win" == m_pFrameKey)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - 2 - m_tFactSize.x / 2, m_tRect.top - 16 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 4 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 16 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 4 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 4 + m_tFactSize.x), int(m_tInfo.fcy + 16 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (false == m_bBubbleState && false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - m_tFactSize.x / 2, m_tRect.top - 22 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 4 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 22 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 4 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 4 + m_tFactSize.x), int(m_tInfo.fcy + 22 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (false == m_bBubbleState && true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - m_tFactSize.x / 2, m_tRect.top - 40 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 4 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 40 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 4 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 4 + m_tFactSize.x), int(m_tInfo.fcy + 40 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (false == m_bBubbleState && false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
		{
			if (PLAYER::FRONT == m_eNextState || PLAYER::FRONT_NONE == m_eNextState
				|| PLAYER::BACK == m_eNextState || PLAYER::BACK_NONE == m_eNextState)
			{
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 17 - m_tFactSize.x / 2, m_tRect.top - 21 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 35 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 21 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + 35 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 35 + m_tFactSize.x), int(m_tInfo.fcy + 21 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상. 
			}
			else if (PLAYER::LEFT == m_eNextState || PLAYER::LEFT_NONE == m_eNextState
				|| PLAYER::RIGHT == m_eNextState || PLAYER::RIGHT_NONE == m_eNextState)
			{
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 9 - m_tFactSize.x / 2, m_tRect.top - 24 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 18 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 24 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + 18 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 18 + m_tFactSize.x), int(m_tInfo.fcy + 24 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상. 
			}
		}
		else if (true == m_bBubbleState && false == m_bOnItem && PLAYER::DIE1 != m_eNextState && PLAYER::DIE2 != m_eNextState)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - 10 - m_tFactSize.x / 2, m_tRect.top - 20 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 20 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 25 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 20 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 20 + m_tFactSize.x), int(m_tInfo.fcy + 25 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (true == m_bBubbleState && false == m_bOnItem && PLAYER::DIE1 == m_eNextState || PLAYER::DIE2 == m_eNextState)
		{
			GdiTransparentBlt(hDC,//출력할 DC
				m_tRect.left - 14 - m_tFactSize.x / 2, m_tRect.top - 50 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + 28 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 55 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + 28 + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + 28 + m_tFactSize.x), int(m_tInfo.fcy + 55 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 3, m_tRect.top - 37,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 6), int(m_tInfo.fcy + 37),// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + 6) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 6), int(m_tInfo.fcy + 37),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상.
				break;
				break;
			case PLAYER::OWLON:
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 2, m_tRect.top - 38,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 4), int(m_tInfo.fcy + 38),// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + 4) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 4), int(m_tInfo.fcy + 38),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상.
				break;
				break;
			case PLAYER::SPACEON:
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 5, m_tRect.top - 24,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 10), int(m_tInfo.fcy + 24),// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + 10) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 10), int(m_tInfo.fcy + 24),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상.
				break;
			case PLAYER::TANKON:
				GdiTransparentBlt(hDC,//출력할 DC
					m_tRect.left - 6 - m_tFactSize.x / 2, m_tRect.top - 43 - m_tFactSize.y,// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + 11 + m_tFactSize.x) + m_tFrameSize.x, int(m_tInfo.fcy + 43 + m_tFactSize.y) + m_tFrameSize.y,// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + m_tFactSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + 11 + m_tFactSize.x), int(m_tInfo.fcy + 43 + m_tFactSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상. 
				break;
			}
		}
	}
	else
	{
		if (m_bCreateTime + GAME_START_TIME < GetTickCount() && false == m_bActingCreate)
		{
			CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
			CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);

			m_bActingCreate = true;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		Rectangle(hDC, m_tTile_Rc.left, m_tTile_Rc.top, m_tTile_Rc.right, m_tTile_Rc.bottom);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CPlayer::Release()
{

}

void CPlayer::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case PLAYER::FRONT_NONE:
		case PLAYER::LEFT_NONE:
		case PLAYER::RIGHT_NONE:
		case PLAYER::BACK_NONE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			break;
		case PLAYER::FRONT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			break;
		case PLAYER::LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			break;
		case PLAYER::RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			break;
		case PLAYER::BACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			break;
		case PLAYER::TANKON:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			break;
		case PLAYER::OWLON:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			break;
		case PLAYER::SPACEON:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			break;
		case PLAYER::TURTTLEON:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			break;
		case PLAYER::BUBBLE1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			CSoundMgr::Get_Instance()->MyPlaySound(L"Bubble.wav", CSoundMgr::PLAYER);
			break;
		case PLAYER::BUBBLE2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			break;
		case PLAYER::BUBBLE3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			break;
		case PLAYER::NEEDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;

			//if (CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID())
			//	CSoundMgr::Get_Instance()->PlayBGM(L"Stage1.wav");

			CSoundMgr::Get_Instance()->MyPlaySound(L"Needle.wav", CSoundMgr::PLAYER);
			break;
		case PLAYER::DIE1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;

			CSoundMgr::Get_Instance()->MyPlaySound(L"Die.wav", CSoundMgr::PLAYER);
			break;
		case PLAYER::DIE2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;

			/*if (CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID())
				CSoundMgr::Get_Instance()->StopAll();*/

			CSoundMgr::Get_Instance()->MyPlaySound(L"Lose.wav", CSoundMgr::PLAYER);
			break;
		case PLAYER::WIN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->MyPlaySound(L"Win.wav", CSoundMgr::PLAYER);
			
			break;
		default:
			break;
		}
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 125;
		m_tFrame.dwFrameTime = GetTickCount();

		if(PLAYER::OWLON == m_eNextState)
			m_tFrame.dwFrameSpeed = 300;
		else if (PLAYER::TURTTLEON == m_eNextState)
			m_tFrame.dwFrameSpeed = 450;
		m_eCurState = m_eNextState;
	}
}

void CPlayer::LateInit()
{
	if (true == m_bBubbleState)
	{
		m_dwBubbleTime = GetTickCount();
	}
	else if (true == m_bHideState)
		m_dwHideTime = GetTickCount();
}

CObj* CPlayer::Create_Ballon()
{
	CObj* pWater = nullptr;
	pWater = CAbstractFactory<CBallon>::Create(m_tTile_Rc.left + TILE_SIZE_X/2.f, m_tTile_Rc.top + TILE_SIZE_Y/2.f);
	if (false == m_bTimerState)
	{
		pWater->Set_FrameKey(m_pBallonFrame);
		SCAST<CBallon*>(pWater)->Set_Timer(false);
	}
	else if (true == m_bTimerState)
	{
		pWater->Set_FrameKey(L"TimerBallon");
		SCAST<CBallon*>(pWater)->Set_Timer(true);
	}
	SCAST<CBallon*>(pWater)->Set_Power(m_uBallonPower);
	return pWater;
}

void CPlayer::WalkActive()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if(false == m_bOnItem)
			m_eNextState = PLAYER::LEFT;
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				m_pFrameKey = L"Turtle_Left";
				break;
			case PLAYER::OWLON:
				m_pFrameKey = L"Owl_Left";
				break;
			case PLAYER::SPACEON:
				m_pFrameKey = L"Space_Left";
				break;
			case PLAYER::TANKON:
				//m_tFrame.iFrameStart = 1;
				//m_tFrame.iFrameEnd = 1;
				m_pFrameKey = L"Tank_Left";
				break;
			}
		}

		if (false == m_bInvinState)
		{
			if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Walk_Left";
			else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Ba_Walk_Left";
			else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Wing_Walk_Left";
		}

		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fx -= m_fSpeed / sqrtf(2);
			m_tInfo.fy -= m_fSpeed / sqrtf(2);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fx -= m_fSpeed / sqrtf(2);
			m_tInfo.fy += m_fSpeed / sqrtf(2);
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fx += m_fSpeed;
			m_tInfo.fx -= m_fSpeed;
		}
		else
			m_tInfo.fx -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (false == m_bOnItem)
			m_eNextState = PLAYER::RIGHT;
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				m_pFrameKey = L"Turtle_Right";
				break;
			case PLAYER::OWLON:
				m_pFrameKey = L"Owl_Right";
				break;
			case PLAYER::SPACEON:
				m_pFrameKey = L"Space_Right";
				break;
			case PLAYER::TANKON:
				//m_tFrame.iFrameStart = 2;
				//m_tFrame.iFrameEnd = 2;
				m_pFrameKey = L"Tank_Right";
				break;
			}
		}

		if (false == m_bInvinState)
		{
			if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Walk_Right";
			else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Ba_Walk_Right";
			else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Wing_Walk_Right";
		}

		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fx += m_fSpeed / sqrtf(2);
			m_tInfo.fy -= m_fSpeed / sqrtf(2);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fx += m_fSpeed / sqrtf(2);
			m_tInfo.fy += m_fSpeed / sqrtf(2);
		}
		else
			m_tInfo.fx += m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (false == m_bOnItem)
			m_eNextState = PLAYER::BACK;
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				m_pFrameKey = L"Turtle_Back";
				break;
			case PLAYER::OWLON:
				m_pFrameKey = L"Owl_Back";
				break;
			case PLAYER::SPACEON:
				m_pFrameKey = L"Space_Back";
				break;
			case PLAYER::TANKON:
				/*m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 3;*/
				m_pFrameKey = L"Tank_Back";
				break;
			}
		}

		if (false == m_bInvinState)
		{
			if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Walk_Back";
			else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Ba_Walk_Back";
			else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Wing_Walk_Back";
		}

		m_tInfo.fy -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (false == m_bOnItem)
			m_eNextState = PLAYER::FRONT;
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				m_pFrameKey = L"Turtle_Front";
				break;
			case PLAYER::OWLON:
				m_pFrameKey = L"Owl_Front";
				break;
			case PLAYER::SPACEON:
				m_pFrameKey = L"Space_Front";
				break;
			case PLAYER::TANKON:
				///m_tFrame.iFrameStart = 0;
				//m_tFrame.iFrameEnd = 0;
				m_pFrameKey = L"Tank_Front";
				break;
			}
		}

		if (false == m_bInvinState)
		{
			if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Walk_Front";
			else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Ba_Walk_Front";
			else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
				m_pFrameKey = L"Wing_Walk_Front";
		}

		m_tInfo.fy += m_fSpeed;
	}
	else
	{
		if (false == m_bOnItem)
		{
			if(PLAYER::FRONT == m_eNextState)
				m_eNextState = PLAYER::FRONT_NONE;
			if (PLAYER::LEFT == m_eNextState)
				m_eNextState = PLAYER::LEFT_NONE;
			if (PLAYER::RIGHT == m_eNextState)
				m_eNextState = PLAYER::RIGHT_NONE;
			if (PLAYER::BACK == m_eNextState)
				m_eNextState = PLAYER::BACK_NONE;
		}
		else if (true == m_bOnItem)
		{
			switch (m_eNextState)
			{
			case PLAYER::TURTTLEON:
				m_eNextState = PLAYER::TURTTLEON;
				//m_pFrameKey = L"Turtle_Front";
				break;
			case PLAYER::OWLON:
				m_eNextState = PLAYER::OWLON;
				//m_pFrameKey = L"Owl_Front";
				break;
			case PLAYER::SPACEON:
				m_eNextState = PLAYER::SPACEON;
				//m_pFrameKey = L"Space_Front";
				break;
			case PLAYER::TANKON:
				m_eNextState = PLAYER::TANKON;
				//m_pFrameKey = L"Tank_Front";
				break;
			}
		}
	}
}

void CPlayer::ThrowActive(CObj* _pBallon)
{
	if (false == m_bOnItem)
	{
		if (PLAYER::LEFT_NONE == m_eNextState)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::LEFT);
		else if (PLAYER::BACK_NONE == m_eNextState)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::UP);
		else if (PLAYER::RIGHT_NONE == m_eNextState)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::RIGHT);
		else if (PLAYER::FRONT_NONE == m_eNextState)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::DOWN);
	}
	else if (true == m_bOnItem)
	{
		if (L"Tank_Left" == m_pFrameKey)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::LEFT);
		else if (L"Tank_Back" == m_pFrameKey)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::UP);
		else if (L"Tank_Right" == m_pFrameKey)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::RIGHT);
		else if (L"Tank_Front" == m_pFrameKey)
			SCAST<CBallon*>(_pBallon)->Set_ThrowDir(BALLON::DOWN);
	}
}

void CPlayer::BlockLeapCheck()
{
	if (false == m_bLeapCheck && false == m_bBubbleState && true == m_bLeapActive && GetAsyncKeyState(VK_CONTROL)
		|| (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState('S')) && true == m_bWingState|| (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState('S') && true == m_bWingState)
		|| (GetAsyncKeyState(VK_UP) && GetAsyncKeyState('S')) && true == m_bWingState || (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState('S') && true == m_bWingState))
	{
		RECT rc = {};
		rc.left = m_tTile_Rc.left;
		rc.top = m_tTile_Rc.top;
		rc.right = m_tTile_Rc.right;
		rc.bottom = m_tTile_Rc.bottom;
		if (PLAYER::LEFT == m_eNextState)
			rc.left -= LONG(5.f);
		else if (PLAYER::BACK == m_eNextState)
			rc.top -= LONG(5.f);
		else if (PLAYER::RIGHT == m_eNextState)
			rc.right += LONG(5.f);
		else if (PLAYER::FRONT == m_eNextState)
			rc.bottom += LONG(5.f);

		list<CObj*>* m_plistBlock = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);

		
			for (auto& pBlcok : *m_plistBlock)
			{
				RECT nullrc = {};
				if (IntersectRect(&nullrc, &rc, pBlcok->Get_Rect()))
				{
					if (PLAYER::LEFT == m_eNextState || PLAYER::BACK == m_eNextState || PLAYER::RIGHT == m_eNextState || PLAYER::FRONT == m_eNextState)
					{
					
					//if ((GetAsyncKeyState(VK_LEFT) && CKeyMgr::Get_Instance()->KeyDown('S')) || (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState('S'))
						//|| (GetAsyncKeyState(VK_UP) && GetAsyncKeyState('S')) || (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState('S')))
					
						RECT rc2 = {};
						rc2.left = m_tTile_Rc.left;
						rc2.top = m_tTile_Rc.top;
						rc2.right = m_tTile_Rc.right;
						rc2.bottom = m_tTile_Rc.bottom;
						if (PLAYER::LEFT == m_eNextState)
						{
							rc2.right = rc.left;
							rc2.left = LONG(m_tTile_Rc.left - (TILE_SIZE_X * 4));
						}
						else if (PLAYER::BACK == m_eNextState)
						{
							rc2.bottom = rc.top;
							rc2.top = LONG(m_tTile_Rc.top - (TILE_SIZE_Y * 4));
						}
						else if (PLAYER::RIGHT == m_eNextState)
						{
							rc2.left = rc.right;
							rc2.right = LONG(m_tTile_Rc.right + (TILE_SIZE_X * 4));
						}
						else if (PLAYER::FRONT == m_eNextState)
						{
							rc2.top = rc.bottom;
							rc2.bottom = LONG(m_tTile_Rc.bottom + (TILE_SIZE_Y * 4));
						}

						RECT nullrc2 = {};
						bool bActive = true;
						bool bBlockCheck[4] = { true };
						for (auto& pBlock : *m_plistBlock)
						{
							if (IntersectRect(&nullrc2, &rc2, pBlock->Get_Rect()))
							{
								if (PLAYER::LEFT == m_eNextState)
								{
									if (pBlock->Get_Rect()->left < (rc2.left + TILE_SIZE_X / 2.f))
										bBlockCheck[3] = true;
									else if (pBlock->Get_Rect()->left == m_tTile_Rc.right - (TILE_SIZE_X * 4))
										bBlockCheck[2] = true;
									else if (pBlock->Get_Rect()->left == m_tTile_Rc.right - (TILE_SIZE_X * 3))
										bBlockCheck[1] = true;
									else if (pBlock->Get_Rect()->left == m_tTile_Rc.right - (TILE_SIZE_X * 2))
										bBlockCheck[0] = true;
								}
								else if (PLAYER::RIGHT == m_eNextState)
								{
									if (pBlock->Get_Rect()->right >(rc2.right - TILE_SIZE_X / 2.f))
										bBlockCheck[3] = true;
									else if (pBlock->Get_Rect()->right == m_tTile_Rc.left + (TILE_SIZE_X * 4))
										bBlockCheck[2] = true;
									else if (pBlock->Get_Rect()->right == m_tTile_Rc.left + (TILE_SIZE_X * 3))
										bBlockCheck[1] = true;
									else if (pBlock->Get_Rect()->right == m_tTile_Rc.left + (TILE_SIZE_X * 2))
										bBlockCheck[0] = true;
								}
								else if (PLAYER::BACK == m_eNextState)
								{
									if (pBlock->Get_Rect()->top < (rc2.top + TILE_SIZE_Y / 2.f))
										bBlockCheck[3] = true;
									else if (pBlock->Get_Rect()->top == m_tTile_Rc.bottom - (TILE_SIZE_Y * 4))
										bBlockCheck[2] = true;
									else if (pBlock->Get_Rect()->top == m_tTile_Rc.bottom - (TILE_SIZE_Y * 3))
										bBlockCheck[1] = true;
									else if (pBlock->Get_Rect()->top == m_tTile_Rc.bottom - (TILE_SIZE_Y * 2))
										bBlockCheck[0] = true;
								}
								else if (PLAYER::FRONT == m_eNextState)
								{
									if (pBlock->Get_Rect()->bottom >(rc2.bottom - TILE_SIZE_Y / 2.f))
										bBlockCheck[3] = true;
									else if (pBlock->Get_Rect()->bottom == m_tTile_Rc.top + (TILE_SIZE_Y * 4))
										bBlockCheck[2] = true;
									else if (pBlock->Get_Rect()->bottom == m_tTile_Rc.top + (TILE_SIZE_Y * 3))
										bBlockCheck[1] = true;
									else if (pBlock->Get_Rect()->bottom == m_tTile_Rc.top + (TILE_SIZE_Y * 2))
										bBlockCheck[0] = true;
								}

							}
								/*if (3 == iLeapBlockNum)
								{
									if (pBlock->Get_Rect()->left < (rc2.left + TILE_SIZE_X / 2.f) && PLAYER::LEFT == m_eNextState
										|| pBlock->Get_Rect()->right >(rc2.right - TILE_SIZE_X / 2.f) && PLAYER::RIGHT == m_eNextState
										|| pBlock->Get_Rect()->top < (rc2.top + TILE_SIZE_Y / 2.f) && PLAYER::BACK == m_eNextState
										|| pBlock->Get_Rect()->bottom >(rc2.bottom - TILE_SIZE_Y / 2.f) && PLAYER::FRONT == m_eNextState)
									{
										bActive = false;
										m_bLeapCheck = false;
										m_dwLeapTime = 0;
										iLeapBlockNum = 0;
										return;
									}
								}*/
						}
						if (true == bBlockCheck[3] && bBlockCheck[2] && bBlockCheck[1] && bBlockCheck[0])
						{
							bActive = false;
							m_bLeapCheck = false;				
							iLeapBlockNum = 0;
							return;
						}
						if (true == bActive)
						{
							m_bLeapCheck = true;
						
							if (false == bBlockCheck[3] && bBlockCheck[2] && bBlockCheck[1] && bBlockCheck[0])
								iLeapBlockNum = 3;
							else if (false == bBlockCheck[2] && bBlockCheck[1])
								iLeapBlockNum = 2;
							else if (false == bBlockCheck[2] && false == bBlockCheck[1] && bBlockCheck[0]
							|| true == bBlockCheck[2] && false == bBlockCheck[1] && bBlockCheck[0])
							iLeapBlockNum = 1;
						}
					}
				}
			}
	}
	if (true == m_bLeapCheck)
		LeapActive(iLeapBlockNum);
}

void CPlayer::LeapActive(int _iBlockNum)
{
	switch (_iBlockNum)
	{
	case 1:
		if ( m_fLeapActivePos < TILE_SIZE_X * 2)
		{
			switch (m_eNextState)
			{
			case PLAYER::LEFT:
				m_tInfo.fx -= 5.f;

				if (m_tRect.bottom <= m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER + 0.8);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom > m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::BACK:
				m_tInfo.fy -= 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			case PLAYER::RIGHT:
				m_tInfo.fx += 5.f;

				if (m_tRect.bottom <= m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER + 0.8);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom > m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::FRONT:
				m_tInfo.fy += 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			}
			m_fLeapActivePos += 5.f;
		}
		else
		{
			m_bLeapCheck = false;
			m_fLeapActivePos = 0;
			iLeapBlockNum = 0;
			m_tFrameSize.x = 0;
			m_tFrameSize.y = 0;
			m_fJumpPower = -15.f;
		}
		break;
	case 2:
		if (m_fLeapActivePos < TILE_SIZE_X * 3)
		{
			switch (m_eNextState)
			{
			case PLAYER::LEFT:
				m_tInfo.fx -= 5.f;

				if (m_tRect.bottom <= m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER + 0.28);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom > m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::BACK:
				m_tInfo.fy -= 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			case PLAYER::RIGHT:
				m_tInfo.fx += 5.f;

				if (m_tRect.bottom <= m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER + 0.28);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom > m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::FRONT:
				m_tInfo.fy += 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			}
			m_fLeapActivePos += 5.f;
		}
		else
		{
			m_bLeapCheck = false;
			m_fLeapActivePos = 0;
			iLeapBlockNum = 0;
			m_tFrameSize.x = 0;
			m_tFrameSize.y = 0;
			m_fJumpPower = -15.f;
		}
		break;
	case 3:
		if (m_fLeapActivePos < TILE_SIZE_X * 4)
		{
			switch (m_eNextState)
			{
			case PLAYER::LEFT:
				m_tInfo.fx -= 5.f;

				if (m_tInfo.fy < m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER - 0.095f);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom >= m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::BACK:
				m_tInfo.fy -= 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			case PLAYER::RIGHT:
				m_tInfo.fx += 5.f;

				if (m_tInfo.fy < m_tTile_Rc.bottom)
				{
					m_fJumpPower += float(GRAVITY_POWER - 0.095f);
					m_tInfo.fy += m_fJumpPower;
				}
				else if (m_tRect.bottom >= m_tTile_Rc.bottom)
					m_tInfo.fy = m_tTile_Rc.bottom - TILE_SIZE_Y / 2.f;
				break;
			case PLAYER::FRONT:
				m_tInfo.fy += 5.f;
				m_tFrameSize.x = -4;
				m_tFrameSize.y = -4;
				break;
			}
			m_fLeapActivePos += 5.f;
		}
		else
		{
			m_bLeapCheck = false;
			m_fLeapActivePos = 0;
			iLeapBlockNum = 0;
			m_tFrameSize.x = 0;
			m_tFrameSize.y = 0;
			m_fJumpPower = -15.f;
		}
		break;
	}
	m_bLeapActive = false;
}

void CPlayer::Set_Item()
{
	list<CObj*>* plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::ITEM);

	for (auto& pItem : *plistObj)
	{
		RECT rc = {};
		if (IntersectRect(&rc, &m_tTile_Rc, &pItem->Get_TileRC()) && false == m_bBoardState && PLAYER::SPACEON != m_eNextState)
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"SetItem.wav", CSoundMgr::PLAYER);
			switch (SCAST<CItem*>(pItem)->Get_Property())
			{
			case ITEM::WATER:
				if(m_iBallonMaxNum < 8)
					++m_iBallonMaxNum;
				break;
			case ITEM::POWER:
				if(m_uBallonPower < 6)
					++m_uBallonPower;
				break;
			case ITEM::ROLLER:
				if (m_fSpeed < 7.f && false == m_bOnItem)
					m_fSpeed += 0.5f;
				break;
			case ITEM::GLOVE:
				m_bThrowState = true;
				break;
			case ITEM::GAS:
				m_uBallonPower = 6;
				break;
			case ITEM::FLY:
				m_pItemFrame = L"Fly";
				break;
			case ITEM::SHOES:
				m_bPushState = true;
				break;
			case ITEM::NEEDLE:
				m_pItemFrame = L"Needle";
				break;
			case ITEM::DART:
				m_pItemFrame = L"Dart";
				break;
			case ITEM::DEVIL:
				if (false == m_bOnItem)
					m_fSpeed = 7.f;
				break;
			case ITEM::TIMER:
				m_pItemFrame = L"Timer";
				break;
			case ITEM::SHIELD:
				m_pItemFrame = L"Shield";
				break;
			case ITEM::TURTLE:
				if (false == m_bOnItem)
				{
					m_bBoardState = true;
					m_eOnItem = ITEM::TURTLE;
					m_fSpeed = 1.f;
				}
				break;
			case ITEM::SPACE:
				if (false == m_bOnItem)
				{
					m_bBoardState = true;
					m_eOnItem = ITEM::SPACE;
					m_fSpeed = 5.f;
				}
				break;
			case ITEM::OWL:
				if (false == m_bOnItem)
				{
					m_bBoardState = true;
					m_eOnItem = ITEM::OWL;
					m_fSpeed = 3.5f;
				}
				break;
			case ITEM::TANK:
				if (false == m_bOnItem)
				{
					m_bBoardState = true;
					m_eOnItem = ITEM::TANK;
				}
				break;
			case ITEM::BANANA:
				m_fSpeed = 3.f;
				m_bBananaState = true;
				m_bWingState = false;
				break;
			case ITEM::BLACKBALLON:
				m_pBallonFrame = L"Ballon2";
				break;
			case ITEM::WING:
				m_bWingState = true;
				m_bBananaState = false;
				break;
			}
			ITEM::PROPERTY eItem = SCAST<CItem*>(pItem)->Get_Property();
			if (ITEM::FLY == eItem || ITEM::NEEDLE == eItem || ITEM::DART == eItem || ITEM::TIMER == eItem || ITEM::SHIELD == eItem)
			{
				if (6 > CObjMgr::Get_Instance()->Get_Obj(OBJID::INVEN)->size())
				{
					CObj* pObj = CAbstractFactory<CInven>::Create();
					CObjMgr::Get_Instance()->AddObject(OBJID::INVEN, pObj);
					pObj->Set_FrameKey(m_pItemFrame);
					SCAST<CInven*>(pObj)->Set_Property(eItem);
					SCAST<CInven*>(pObj)->Set_Order(m_iOrder);
					m_iOrder++;
					
				}
			}
			SCAST<CItem*>(pItem)->Set_Dead();
		}
	}
}

void CPlayer::Use_Item()
{
	int iUseItem = 0;
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
		iUseItem = 1;
	else if (CKeyMgr::Get_Instance()->KeyDown('2'))
		iUseItem = 2;
	else if (CKeyMgr::Get_Instance()->KeyDown('3'))
		iUseItem = 3;
	else if (CKeyMgr::Get_Instance()->KeyDown('4'))
		iUseItem = 4;
	else if (CKeyMgr::Get_Instance()->KeyDown('5'))
		iUseItem = 5;
	else if (CKeyMgr::Get_Instance()->KeyDown('6'))
		iUseItem = 6;

	if (iUseItem)
	{
		list<CObj*>* plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::INVEN);

		for (auto& pItem : *plistObj)
		{
			SCAST<CInven*>(pItem)->Set_Active(false);
			if (iUseItem == SCAST<CInven*>(pItem)->Get_Order())
			{
				SCAST<CInven*>(pItem)->Set_Active(true);
			}
		}
	}

	bool bUse = false;
	if (CKeyMgr::Get_Instance()->KeyDown(VK_CONTROL))
	{
		list<CObj*>* plistObj = CObjMgr::Get_Instance()->Get_Obj(OBJID::INVEN);

		for (auto& pItem : *plistObj)
		{
			if (true == SCAST<CInven*>(pItem)->Get_Active())
			{
				ITEM::PROPERTY eItem = SCAST<CInven*>(pItem)->Get_Property();
				CObj* pObj = nullptr;
				switch (eItem)
				{
				case ITEM::FLY:
					m_bLeapActive = true;
					break;
				case ITEM::NEEDLE:
					m_bNeedleState = true;
					break;
				case ITEM::DART:
					pObj = CAbstractFactory<CDart>::Create();
					pObj->Set_Pos(m_tInfo.fx, m_tInfo.fy-5.f);
					SCAST<CDart*>(pObj)->Set_Dir(m_eNextState);
					CObjMgr::Get_Instance()->AddObject(OBJID::DART, pObj);
					break;
				case ITEM::TIMER:
					m_bTimerState = true;
					break;
				case ITEM::SHIELD:
					pObj = CAbstractFactory<CShield>::Create();
					pObj->Set_Pos(m_tInfo.fx, m_tInfo.fy);
					CObjMgr::Get_Instance()->AddObject(OBJID::SHIELD, pObj);
					m_bShieldState = true;
					break;
				}
				pItem->Set_Dead();
				bUse = true;
			}
			if (true == bUse)
			{
				SCAST<CInven*>(pItem)->Set_OrderMius();
				m_iOrder = int(plistObj->size());
			}
		}
	}
}

void CPlayer::Board_Item()
{
	if (true == m_bBoardState)
	{
		if (false == m_bOnItem)
		{
			if (PLAYER::FRONT == m_eNextState)
				m_eNextState = PLAYER::FRONT_NONE;
			if (PLAYER::LEFT == m_eNextState)
				m_eNextState = PLAYER::LEFT_NONE;
			if (PLAYER::RIGHT == m_eNextState)
				m_eNextState = PLAYER::RIGHT_NONE;
			if (PLAYER::BACK == m_eNextState)
				m_eNextState = PLAYER::BACK_NONE;
		}
		else if (true == m_bOnItem)
		{
			if (L"Tank_Front" == m_pFrameKey || L"Space_Front" == m_pFrameKey || L"Owl_Front" == m_pFrameKey || L"Turtle_Front" == m_pFrameKey)
			{
				m_eNextState = PLAYER::FRONT_NONE;

				if (false == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Walk_Front";
				else if (true == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Ba_Walk_Front";
				else if (false == m_bBananaState && true == m_bWingState)
					m_pFrameKey = L"Wing_Walk_Front";
			}
			else if (L"Tank_Left" == m_pFrameKey || L"Space_Left" == m_pFrameKey || L"Owl_Left" == m_pFrameKey || L"Turtle_Left" == m_pFrameKey)
			{
				m_eNextState = PLAYER::LEFT_NONE;

				if (false == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Walk_Left";
				else if (true == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Ba_Walk_Left";
				else if (false == m_bBananaState && true == m_bWingState)
					m_pFrameKey = L"Wing_Walk_Left";
			}
			else if (L"Tank_Right" == m_pFrameKey || L"Space_Right" == m_pFrameKey || L"Owl_Right" == m_pFrameKey || L"Turtle_Right" == m_pFrameKey)
			{
				m_eNextState = PLAYER::RIGHT_NONE;

				if (false == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Walk_Right";
				else if (true == m_bBananaState && false == m_bWingState)
					m_pFrameKey = L"Ba_Walk_Right";
				else if (false == m_bBananaState && true == m_bWingState)
					m_pFrameKey = L"Wing_Walk_Right";
			}
			else if (L"Tank_Back" == m_pFrameKey || L"Space_Back" == m_pFrameKey || L"Owl_Back" == m_pFrameKey || L"Turtle_Back" == m_pFrameKey)
			{
				m_eNextState = PLAYER::BACK_NONE;

				if (false == m_bBananaState && false == m_bWingState && false == m_bOnItem)
					m_pFrameKey = L"Walk_Back";
				else if (true == m_bBananaState && false == m_bWingState && false == m_bOnItem)
					m_pFrameKey = L"Ba_Walk_Back";
				else if (false == m_bBananaState && true == m_bWingState && false == m_bOnItem)
					m_pFrameKey = L"Wing_Walk_Back";
			}
			m_fSpeed = 3.5f;
			m_bOnItem = false;
			m_eOnItem = ITEM::END;
		}

		if (3.0f > m_fBoardJumpPower)
		{
			m_fBoardJumpPower += 0.1f;
			m_tInfo.fy += m_fBoardJumpPower;
		}
		else if (3.0f <= m_fBoardJumpPower)
		{
			m_bBoardState = false;
			
			switch (m_eOnItem)
			{
			case ITEM::TURTLE:
				m_eNextState = PLAYER::TURTTLEON;
				m_pFrameKey = L"Turtle_Front";
				m_bOnItem = true;
				break;
			case ITEM::OWL:
				m_eNextState = PLAYER::OWLON;
				m_pFrameKey = L"Owl_Front";
				m_bOnItem = true;
				break;
			case ITEM::SPACE:
				m_eNextState = PLAYER::SPACEON;
				m_pFrameKey = L"Space_Front";
				m_bOnItem = true;
				break;
			case ITEM::TANK:
				m_eNextState = PLAYER::TANKON;
				m_pFrameKey = L"Tank_Front";
				m_bOnItem = true;
				break;
			}
			m_eOnItem = ITEM::END;
		}
	}
	else if (false == m_bBoardState && false == m_bLeapCheck)
	{
		m_fBoardJumpPower = -3.3f;
	}
}

void CPlayer::Summons_Item()
{
	CObj* pObj = CAbstractFactory<CItem>::Create(m_tInfo.fx-40.f, m_tInfo.fy);
	SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(m_iSummonsItem));
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
}
