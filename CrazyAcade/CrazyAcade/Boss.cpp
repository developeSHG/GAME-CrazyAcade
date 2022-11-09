#include "stdafx.h"
#include "Boss.h"

#include "Acting.h"
#include "Item.h"
#include "Ballon.h"
#include "Stem.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBoss::CBoss()
{

}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y * 2;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = GetTickCount();
	m_fSpeed = 3.f;
	m_bBallonOn = true;
	m_bBubbleState = false;
	m_bPushState = false;
	m_bCreateTime = GetTickCount();

	// 보스 고유변수
	m_dwAiTime = GetTickCount() + GAME_START_TIME;
	m_dwBallonTime = GetTickCount();
	m_dwBubbleTime = NULL;
	m_dwDeadTime = NULL;
	m_dwCreateMonsterTime = GetTickCount();
	m_dwAngerShowTime = NULL;
	m_dwAngerTime = NULL;
	m_dwShadowTime = GetTickCount();
	m_dwDieTime = NULL;
	m_bShadowState = false;
	m_iShadowMove = 0;
	m_fHp = 10.f;
	m_bRealBubbleState = false;
	m_bDieState = false;
	m_bAngerState = false;
	m_bHpState = false;
	iBallonTime = 3500;
	uBallonPower = 3;

	m_tFrameSize.x = 52;
	m_tFrameSize.y = 19;

	m_eNextState = BOSS::FRONT;
	m_pFrameKey = L"Boss";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CBoss::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	if (CKeyMgr::Get_Instance()->KeyDown('U'))
	{
		m_fHp = 3;
	}
	if (CKeyMgr::Get_Instance()->KeyDown('M'))
	{
		m_fHp = 0;
	}

	if (m_dwGameStartTime + GAME_START_TIME < GetTickCount() && false == m_bRealBubbleState)
	{
		if (false == m_bBubbleState && false == m_bShadowState && BOSS::ANGER != m_eNextState)
			AISystem();

		// 몬스터 생성 (시작)
		if (m_dwCreateMonsterTime + 5000 < GetTickCount())
		{
			CreateMonster();
			m_dwCreateMonsterTime = GetTickCount();
		}
		// 몬스터 생성 (끝)

		if (m_dwBallonTime + iBallonTime < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJID::BALLON, BossCreateBallon());
			m_dwBallonTime = GetTickCount();
		}

		// 그림자모드
		if (m_fHp > 6 && m_dwShadowTime + 20000 < GetTickCount() && false == m_bShadowState)
		{
			m_bShadowState = true;
			m_eNextState = BOSS::SHADOW;
			m_dwShadowTime = GetTickCount();
		}

		if (true == m_bShadowState && m_dwShadowTime + 7000 < GetTickCount())
		{
			m_bShadowState = false;
			m_dwShadowTime = GetTickCount();
		}
		// 그림자모드

		// 앵글모드
		if (m_fHp <= 6 && m_dwAngerTime + 4000 < GetTickCount() && false == m_bAngerState)
		{
			m_bAngerState = true;
			//m_dwAngerShowTime = GetTickCount();
			m_eNextState = BOSS::ANGER;
			m_dwAngerTime = NULL;
			m_dwAngerShowTime = GetTickCount();
			iBallonTime = 500;
			uBallonPower = 7;
		}
		// 앵글모드
	}
	// 앵글상태 (시작)
	if (NULL != m_dwAngerShowTime && m_dwAngerShowTime + 1000 < GetTickCount() && NULL == m_dwAngerTime && true == m_bAngerState)
	{
		m_fSpeed = 15.f;
		m_dwAngerTime = GetTickCount();
		m_eNextState = BOSS::STATE(rand() % BOSS::BEING);
	}
	if (NULL != m_dwAngerTime && m_dwAngerTime + 4000 < GetTickCount() && true == m_bAngerState)
	{
		m_bAngerState = false;
		m_fSpeed = 2.5f;
		m_dwAngerTime = GetTickCount();
	}
	// 앵글상태 (끝)

	// 버블상태 (시작)
	if (true == m_bBubbleState)
	{
		m_eNextState = BOSS::BEING;
		m_bShadowState = false;
		m_dwShadowTime = GetTickCount();

		if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
		{
			m_bBubbleState = false;
		}
	}
	// 버블상태 (끝)

	// 셰도우상태(시작)
	if (true == m_bShadowState)
	{
		m_tFrame.iFrameStart = 18;

		if (m_dwAiTime + 1300 < GetTickCount())
		{
			m_iShadowMove = rand() % BOSS::BEING;
			m_dwAiTime = GetTickCount();
		}

		switch (m_iShadowMove)
		{
		case BOSS::FRONT:
			m_tInfo.fy += m_fSpeed;
			break;
		case BOSS::LEFT:
			m_tInfo.fx -= m_fSpeed;
			break;
		case BOSS::RIGHT:
			m_tInfo.fx += m_fSpeed;
			break;
		case BOSS::BACK:
			m_tInfo.fy -= m_fSpeed;
			break;
		}
	}

	// 리얼버블 상태 (시작)
	if (m_fHp <= 0 && false == m_bDieState)
	{
		m_eNextState = BOSS::BUBBLE;
		m_bRealBubbleState = true;

		if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
		{
			m_tFrame.iFrameStart = 12;
		}
	}
	// 리얼버블 상태 (끝)

	// 죽음 상태 (시작)
	if (true == m_bDieState && NULL == m_dwDieTime)
	{
		m_eNextState = BOSS::DIE;

		if (m_tFrame.iFrameEnd <= m_tFrame.iFrameStart)
		{
			m_tFrame.iFrameStart = 17;
			m_dwDieTime = GetTickCount();
		}
	}

	if (NULL != m_dwDieTime && m_dwDieTime + 2000 < GetTickCount())
	{
		return OBJ_DEAD;
	}
	// 죽음 상태 (끝)

	/*CUnit::LateInit();
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
	}*/
	// 셰도우상태(끝)

	// 죽음상태 보여주기 (시작)
	//if (0 != m_dwDeadTime && m_dwDeadTime + 1500 < GetTickCount())
	//{
	//	return OBJ_DEAD;
	//}
	// 죽음상태 보여주기 (끝)

	return OBJ_LIVE;
}

void CBoss::LateUpdate()
{
	if (false == m_bBubbleState)
	{
		switch (m_eNextState)
		{
		case BOSS::FRONT:
			m_tInfo.fy += m_fSpeed;
			break;
		case BOSS::LEFT:
			m_tInfo.fx -= m_fSpeed;
			break;
		case BOSS::RIGHT:
			m_tInfo.fx += m_fSpeed;
			break;
		case BOSS::BACK:
			m_tInfo.fy -= m_fSpeed;
			break;
		}
	}


	SceneChange();
	if (NULL == m_dwDeadTime && false == m_bShadowState && NULL == m_dwDieTime)
		CObj::MoveFrame(m_tFrame.iFrameStartReset);
}

void CBoss::Render(HDC hDC)
{
	// 내가 있는 타일 위치체크 (시작)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	m_tTile_Rc.top -= TILE_SIZE_Y;
	// 내가 있는 타일 위치체크 (끝)

	if (true == m_bActingCreate)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
		GdiTransparentBlt(hDC,//출력할 DC
			int(m_tRect.left - m_tFrameSize.x / 2), int(m_tRect.top - m_tFrameSize.y),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx + m_tFrameSize.x) * m_tFrame.iFrameStart), int(m_tInfo.fcy + m_tFrameStart.y) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 	
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

void CBoss::Release()
{
}

void CBoss::LateInit()
{
	m_bHpState = true;
	m_fHp--;
}

void CBoss::AISystem()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

	if (m_dwAiTime + 1700 < GetTickCount())
	{
		m_eNextState = BOSS::STATE(rand() % BOSS::BEING);
		//m_eNextState = MONSTER::FRONT;
		m_dwAiTime = GetTickCount();
	}
}

CObj* CBoss::BossCreateBallon()
{
	CSoundMgr::Get_Instance()->MyPlaySound(L"Ballon.wav", CSoundMgr::PLAYER);
	CObj* pWater = nullptr;
	pWater = CAbstractFactory<CBallon>::Create(m_tTile_Rc.left + TILE_SIZE_X, m_tTile_Rc.bottom - TILE_SIZE_Y);
	SCAST<CBallon*>(pWater)->Set_FrameKey(L"Ballon3");
	SCAST<CBallon*>(pWater)->Set_Power(uBallonPower);
	SCAST<CBallon*>(pWater)->Set_Timer(false);
	SCAST<CBallon*>(pWater)->Set_FrameEndScene(2);
	SCAST<CBallon*>(pWater)->Set_BossBallon();
	return pWater;
}


void CBoss::CreateMonster()
{
	int iRan = rand() % 4;
	float x = 0;
	float y = 0;
	switch (iRan)
	{
	case 0:
		x = -TILE_SIZE_X;
		break;
	case 1:
		y = -TILE_SIZE_Y;
		break;
	case 2:
		x = TILE_SIZE_X;
		break;
	case 3:
		y = TILE_SIZE_Y;
		break;
	}
	CObj* pObj = CAbstractFactory<CMonster>::Create(m_tInfo.fx + x, m_tInfo.fy + y);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pObj);

	iRan = rand() % 9;
	TCHAR* FrameRan = nullptr;
	switch (iRan)
	{
	case 0:
		FrameRan = L"Stage1_Monster1";
		SCAST<CMonster*>(pObj)->Set_Stage(1);
		break;
	case 1:
		FrameRan = L"Stage1_Monster2";
		SCAST<CMonster*>(pObj)->Set_Stage(1);
		break;
	case 2:
		FrameRan = L"Stage1_Monster3";
		SCAST<CMonster*>(pObj)->Set_Stage(1);
		break;
	case 3:
		FrameRan = L"Stage1_Monster4";
		SCAST<CMonster*>(pObj)->Set_Stage(1);
		break;
	case 4:
		FrameRan = L"Stage1_Monster5";
		SCAST<CMonster*>(pObj)->Set_Stage(1);
		break;
	case 5:
		FrameRan = L"Stage2_Monster1";
		SCAST<CMonster*>(pObj)->Set_Stage(2);
		break;
	case 6:
		FrameRan = L"Stage2_Monster2";
		SCAST<CMonster*>(pObj)->Set_Stage(2);
		break;
	case 7:
		FrameRan = L"Stage2_Monster3";
		SCAST<CMonster*>(pObj)->Set_Stage(2);
		break;
	case 8:
		FrameRan = L"Stage2_Monster4";
		SCAST<CMonster*>(pObj)->Set_Stage(2);
		break;
	}
	SCAST<CMonster*>(pObj)->Set_FrameKey(FrameRan);
}

void CBoss::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case BOSS::FRONT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::LEFT:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::RIGHT:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::BACK:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::BEING:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::SHADOW:
			m_tFrame.iFrameStart = 18;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case BOSS::ANGER:
			m_tFrame.iFrameStart = 10;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->MyPlaySound(L"Anger.wav", CSoundMgr::PLAYER);
			break;
		case BOSS::BUBBLE:
			m_tFrame.iFrameStart = 11;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->MyPlaySound(L"Bubble.wav", CSoundMgr::PLAYER);
			break;
		case BOSS::DIE:
			m_tFrame.iFrameStart = 16;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			CSoundMgr::Get_Instance()->MyPlaySound(L"Mon.wav", CSoundMgr::PLAYER);
			break;
		default:
			break;
		}
		m_tFrame.iFrameStartReset = m_tFrame.iFrameStart;
		m_eCurState = m_eNextState;
	}
}

