#include "stdafx.h"
#include "Monster.h"

#include "Acting.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{

	Release();
}

void CMonster::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y;
	m_tInfo.fx = 300.f;
	m_tInfo.fy = 56.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = GetTickCount();
	m_fSpeed = 2.5f;
	m_bBallonOn = true;
	m_bBubbleState = false;
	m_bPushState = false;
	m_bCreateTime = GetTickCount();

	// 몬스터 고유변수
	m_dwAiTime = GetTickCount() + GAME_START_TIME;
	m_dwBubbleTime = NULL;
	m_bHideState = false;
	m_dwHideTime = NULL;
	m_bChetkiState = false;
	ZeroMemory(&m_tChetkiPoint, sizeof(m_tChetkiPoint));
	m_dwDeadTime = 0;
	m_iStage = 1;

	m_eNextState = MONSTER::FRONT;
	m_pFrameKey = L"Stage2_Monster1";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMonster::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_dwGameStartTime + GAME_START_TIME < GetTickCount() && false == m_bChetkiState)
	{
		if (false == m_bBubbleState && false == m_bHideState && false == m_bChetkiState)
			AISystem();
	}

	// 버블상태 (시작)
	if (true == m_bBubbleState)
	{
		if (1 == m_iStage)
		{
			m_eNextState = MONSTER::DIE;

			if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
				return OBJ_DEAD;

		}
		else if (2 == m_iStage)
		{
			CUnit::LateInit();
			if (MONSTER::DIE == m_eNextState && 0 == m_dwDeadTime)
			{
				SceneChange();
				CObj::MoveFrame(m_tFrame.iFrameStartReset);
				if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
				{
					m_dwDeadTime = GetTickCount();
				}
			}
			else if (MONSTER::NEEDLE != m_eNextState && 0 == m_dwDeadTime)
				m_eNextState = MONSTER::BUBBLE;

			if (m_dwBubbleTime + 5000 < GetTickCount() && MONSTER::DIE != m_eNextState)
			{
				m_eNextState = MONSTER::NEEDLE;
			}
		}
	}
	// 버블상태 (끝)

	// 죽음상태 보여주기 (시작)
	if (0 != m_dwDeadTime && m_dwDeadTime + 1500 < GetTickCount())
	{
		return OBJ_DEAD;
	}
	// 죽음상태 보여주기 (끝)


	// 니들상태 (시작)
	if (MONSTER::NEEDLE == m_eNextState && 0 == m_dwDeadTime)
	{
		if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
		{
			m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
			m_dwAiTime = GetTickCount();
			m_bBubbleState = false;
			m_dwBubbleTime = NULL;
			m_bIsInit = false;
		}
	}
	// 니들상태 (끝)

	return OBJ_LIVE;
}

void CMonster::LateUpdate()
{
	if (false == m_bHideState && false == m_bChetkiState)
	{
		switch (m_eNextState)
		{
		case MONSTER::FRONT:
			m_tInfo.fy += m_fSpeed;
			break;
		case MONSTER::LEFT:
			m_tInfo.fx -= m_fSpeed;
			break;
		case MONSTER::RIGHT:
			m_tInfo.fx += m_fSpeed;
			break;
		case MONSTER::BACK:
			m_tInfo.fy -= m_fSpeed;
			break;
		}
	}

	// 하이드블럭 상태 빠져나오기 (시작)
	if (true == m_bHideState)
	{
		if (m_dwHideTime + 300< GetTickCount())
		{
			m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
			m_dwAiTime = GetTickCount();
			m_bHideState = false;
			m_dwHideTime = NULL;

			switch (m_eNextState)
			{
			case MONSTER::FRONT:
				m_tInfo.fy += 25.f;
				break;
			case MONSTER::LEFT:
				m_tInfo.fx -= 25.f;
				break;
			case MONSTER::RIGHT:
				m_tInfo.fx += 25.f;
				break;
			case MONSTER::BACK:
				m_tInfo.fy -= 25.f;
				break;
			}
		}
	}
	// 하이드블럭 상태 빠져나오기 (끝)

	if (CSceneMgr::SCENEID::SCENE_STAGE2 == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		// 몬스터 버블상태 서로 살리기(시작)
		list<CObj*>* plistMonster = CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER);
		if (plistMonster->empty())
			return;

		for (auto& pMonster : *plistMonster)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &m_tRect, SCAST<CUnit*>(pMonster)->Get_Rect()) && false == SCAST<CUnit*>(pMonster)->Get_BubbleState())
			{
				if (m_tRect.left == rc.left && m_tRect.right == rc.right && m_tRect.top == rc.top && m_tRect.bottom == rc.bottom)
					continue;

				if (true == m_bBubbleState && 0 == m_dwDeadTime)
				{
					m_eNextState = MONSTER::NEEDLE;
				}
			}
		}

		//list<CObj*>* plistBoss = CObjMgr::Get_Instance()->Get_Obj(OBJID::BOSS);
		//if (plistBoss->empty())
		//	return;

		//for (auto& pBoss : *plistBoss)
		//{
		//	RECT rc = {};
		//	if (IntersectRect(&rc, &m_tRect, SCAST<CUnit*>(pBoss)->Get_Rect()) && false == SCAST<CUnit*>(pBoss)->Get_BubbleState())
		//	{
		//		if (m_tRect.left == rc.left && m_tRect.right == rc.right && m_tRect.top == rc.top && m_tRect.bottom == rc.bottom)
		//			continue;

		//		if (true == m_bBubbleState && 0 == m_dwDeadTime)
		//		{
		//			m_eNextState = MONSTER::NEEDLE;
		//		}
		//	}
		//}
		// 몬스터 버블상태 서로 살리기(끝)
	}

	// 치트키 (시작)
	if (GetAsyncKeyState('P'))
	{
		m_bChetkiState = true;
		m_tChetkiPoint.x = long(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fx);
		m_tChetkiPoint.y = long(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fy + TILE_SIZE_Y + 10.f);
	}
	if (true == m_bChetkiState)
	{
		float x = m_tChetkiPoint.x - m_tInfo.fx;
		float y = m_tChetkiPoint.y - m_tInfo.fy;
		float fDist = sqrtf((x*x) + (y*y));

		float m_fAngle = acosf(x / fDist);

		if (m_tInfo.fy < m_tChetkiPoint.y)
			m_fAngle *= -1;

		m_tInfo.fx += cosf(m_fAngle) * 6;
		m_tInfo.fy -= sinf(m_fAngle) * 6;

	}
	// 치트키 (끝)



	SceneChange();
	if (0 == m_dwDeadTime)
		CObj::MoveFrame(m_tFrame.iFrameStartReset);
}

void CMonster::Render(HDC hDC)
{
	// 내가 있는 타일 위치체크 (시작)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	// 내가 있는 타일 위치체크 (끝)

	if (true == m_bHideState)
		return;

	if (true == m_bActingCreate && false == m_bHideState)
	{
		if (1 == m_iStage)
		{
			if (L"Stage1_Monster1" == m_pFrameKey)
			{
				m_tFrameSize.x = 21;
				m_tFrameSize.y = 19;
				m_tFramePos.y = -4;
			}
			else if ((L"Stage1_Monster2" == m_pFrameKey))
			{
				m_tFrameSize.x = 21;
				m_tFrameSize.y = 19;
				m_tFramePos.y = -2;
			}
			else if ((L"Stage1_Monster3" == m_pFrameKey))
			{
				m_tFrameSize.x = 21;
				m_tFrameSize.y = 19;
				m_tFramePos.y = -10;
			}
			else if ((L"Stage1_Monster4" == m_pFrameKey))
			{
				m_tFrameSize.x = 21;
				m_tFrameSize.y = 19;
				m_tFramePos.y = -10;
			}
			else if ((L"Stage1_Monster5" == m_pFrameKey))
			{
				m_tFrameSize.x = 30;
				m_tFrameSize.y = 28;
				//m_tFramePos.y = -10;
			}
			HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
			GdiTransparentBlt(hDC,//출력할 DC
				int(m_tRect.left - m_tFrameSize.x / 2.f), int(m_tRect.top - m_tFrameSize.y - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + m_tFrameSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy + m_tFrameSize.y) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
		else if (2 == m_iStage)
		{
			m_tFrameSize.x = 21;
			m_tFrameSize.y = 33;

			HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
			GdiTransparentBlt(hDC,//출력할 DC
				int(m_tRect.left - 10 - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + m_tFrameSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy + m_tFrameStart.y) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
	}
	else
	{
		if (CSceneMgr::SCENEID::SCENE_STAGE3 == CSceneMgr::Get_Instance()->Get_SceneID())
		{
			CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
			CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);

			m_bActingCreate = true;
		}
		else if (m_bCreateTime + GAME_START_TIME < GetTickCount() && false == m_bActingCreate)
		{
			CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
			CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);

			m_bActingCreate = true;
		}
	}

	//GdiTransparentBlt(hDC,//출력할 DC
	//	m_tRect.left, m_tRect.top,// 그림을 그릴 시작 좌표 XY
	//	int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
	//	hMemDC,// 복사할 DC 
	//	int(m_tInfo.fcx * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// 출력할 비트맵의 시작 좌표 
	//	int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
	//	RGB(255, 255, 255));// 내가 빼고자하는 색상. 

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		Rectangle(hDC, m_tTile_Rc.left, m_tTile_Rc.top, m_tTile_Rc.right, m_tTile_Rc.bottom);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMonster::Release()
{
}

void CMonster::LateInit()
{
	m_dwBubbleTime = GetTickCount();
}

void CMonster::AISystem()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

	if (m_dwAiTime + 1800 < GetTickCount())
	{
		m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
		//m_eNextState = MONSTER::FRONT;
		m_dwAiTime = GetTickCount();

	}
}



void CMonster::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case MONSTER::FRONT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case MONSTER::LEFT:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case MONSTER::RIGHT:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case MONSTER::BACK:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case MONSTER::BUBBLE:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();

			CSoundMgr::Get_Instance()->MyPlaySound(L"Bubble.wav", CSoundMgr::PLAYER);
			break;
		case MONSTER::NEEDLE:
			m_tFrame.iFrameStart = 12;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();

			CSoundMgr::Get_Instance()->MyPlaySound(L"Needle.wav", CSoundMgr::PLAYER);
			break;
		case MONSTER::DIE:
			CSoundMgr::Get_Instance()->MyPlaySound(L"Mon.wav", CSoundMgr::PLAYER);
			if (1 == m_iStage)
			{
				m_tFrame.iFrameStart = 8;
				m_tFrame.iFrameEnd = 11;
			}
			else if (2 == m_iStage)
			{
				m_tFrame.iFrameStart = 16;
				m_tFrame.iFrameEnd = 18;
			}
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 270;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_tFrame.iFrameStartReset = m_tFrame.iFrameStart;
		m_eCurState = m_eNextState;
	}
}
