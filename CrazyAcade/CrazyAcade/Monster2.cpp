#include "stdafx.h"
#include "Monster2.h"

#include "Acting.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CMonster2::CMonster2()
{
	srand(unsigned(time(NULL)));
}

CMonster2::~CMonster2()
{
	Release();
}

void CMonster2::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y;
	m_tInfo.fx = 300.f;
	m_tInfo.fy = 56.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = GetTickCount();
	m_fSpeed = 3.5f;
	m_bBallonOn = true;
	m_bBubbleState = false;
	m_dwBubbleTime = NULL;
	m_bPushState = false;
	m_bCreateTime = GetTickCount();

	// ���� ��������
	m_dwAiTime = GetTickCount() + GAME_START_TIME;
	m_dwBubbleTime = NULL;
	m_bHideState = false;
	m_dwHideTime = NULL;

	m_eNextState = MONSTER::FRONT;
	m_pFrameKey = L"Stage1_Monster1";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMonster2::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_dwGameStartTime + GAME_START_TIME < GetTickCount())
	{
		/*if(false == m_bBubbleState && false == m_bHideState)
		AISystem();*/
	}

	// ������� (����)
	if (true == m_bBubbleState)
	{
		CUnit::LateInit();
		m_eNextState = MONSTER::BUBBLE;

		if (m_dwBubbleTime + 3000 < GetTickCount())
		{
			m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
			m_dwAiTime = GetTickCount();
			m_bBubbleState = false;
			m_dwBubbleTime = NULL;
			m_bIsInit = false;
		}
	}
	// ������� (��)

	return OBJ_LIVE;
}

void CMonster2::LateUpdate()
{
	// ���̵�� ���� ���������� (����)
	if (true == m_bHideState)
	{
		CUnit::Set_ZeroSize();
		if (m_dwHideTime + 500< GetTickCount())
		{
			m_tInfo.fcx = TILE_SIZE_X;
			m_tInfo.fcy = TILE_SIZE_Y;
			m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
			m_dwAiTime = GetTickCount();
			m_bHideState = false;
			m_dwHideTime = NULL;

			switch (m_eNextState)
			{
			case MONSTER::FRONT:
				m_tInfo.fy += 35.f;
				break;
			case MONSTER::LEFT:
				m_tInfo.fx -= 35.f;
				break;
			case MONSTER::RIGHT:
				m_tInfo.fx += 35.f;
				break;
			case MONSTER::BACK:
				m_tInfo.fy -= 35.f;
				break;
			}
		}
	}
	// ���̵�� ���� ���������� (��)

	// ���� ������� ���� �츮��(����)
	list<CObj*>* plistMonster = CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER);
	if (plistMonster->empty())
		return;

	for (auto& pMonster : *plistMonster)
	{
		RECT rc = {};
		if (IntersectRect(&rc, &m_tTile_Rc, &SCAST<CUnit*>(pMonster)->Get_TileRC()))
		{
			if (m_tRect.left == rc.left && m_tRect.right == rc.right && m_tRect.top == rc.top && m_tRect.bottom == rc.bottom)
				continue;

			if (true == m_bBubbleState)
			{
				m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
				m_dwAiTime = GetTickCount();
				m_bBubbleState = false;
				m_dwBubbleTime = NULL;
				m_bIsInit = false;
			}
		}
	}
	// ���� ������� ���� �츮��(��)

	SceneChange();
	CObj::MoveFrame();
	KindsCheck();
}

void CMonster2::Render(HDC hDC)
{
	// ���� �ִ� Ÿ�� ��ġüũ (����)
	CObj::UpdateRect();
	CObj::TileRC_Check();
	// ���� �ִ� Ÿ�� ��ġüũ (��)

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (true == m_bActingCreate)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
		GdiTransparentBlt(hDC,//����� DC
			int(m_tRect.left - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y / 2.f - m_tFramePos.y),// �׸��� �׸� ���� ��ǥ XY
			int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// ����� �׸��� ũ�� 
			hMemDC,// ������ DC 
			int((m_tInfo.fcx) * m_tFrame.iFrameStart + m_tFrameStart.x), int(m_tInfo.fcy) * m_tFrame.iFrameScene + +m_tFrameStart.y,// ����� ��Ʈ���� ���� ��ǥ 
			int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
			RGB(255, 0, 255));// ���� �������ϴ� ����. 
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

	//GdiTransparentBlt(hDC,//����� DC
	//	m_tRect.left, m_tRect.top,// �׸��� �׸� ���� ��ǥ XY
	//	int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� �׸��� ũ�� 
	//	hMemDC,// ������ DC 
	//	int(m_tInfo.fcx * m_tFrame.iFrameStart), int(m_tInfo.fcy * m_tFrame.iFrameScene),// ����� ��Ʈ���� ���� ��ǥ 
	//	int(m_tInfo.fcx), int(m_tInfo.fcy),// ����� ��Ʈ ���� ��ü ���� ���� ���� 
	//	RGB(255, 255, 255));// ���� �������ϴ� ����. 
}

void CMonster2::Release()
{
}

void CMonster2::LateInit()
{
	m_dwBubbleTime = GetTickCount();
}

void CMonster2::AISystem()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

	if (m_dwAiTime + 1500 < GetTickCount())
	{
		m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE);
		//m_eNextState = MONSTER::FRONT;
		m_dwAiTime = GetTickCount();
	}

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

void CMonster2::KindsCheck()
{
	m_tFrameSize.x = 0;
	m_tFrameSize.y = 0;
	m_tFrameStart.x = 0;
	m_tFrameStart.x = 0;
	m_tFramePos.x = 0;
	m_tFramePos.y = 0;

	if (L"Stage1_Monster1" == m_pFrameKey)
	{
		m_tFrameSize.y = 13;
		m_tFramePos.x = 5;

		if (1 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 8;
		}
		else if (2 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 11;
			m_tFrameStart.x = 11;
		}
		else if (3 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 13;
			m_tFrameStart.x = 24;
		}
		else if (4 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 11;
			m_tFrameStart.x = 35;
		}
		else if (5 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 13;
			m_tFrameStart.x = 48;
		}
		else if (6 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 8;
			m_tFrameStart.x = 56;
		}
		else if (7 == m_tFrame.iFrameStart)
		{
			m_tFrameSize.x = 8;
			m_tFrameStart.x = 64;
		}
	}
}

void CMonster2::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case MONSTER::FRONT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 1300;
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
			break;
		case MONSTER::NEEDLE:
			m_tFrame.iFrameStart = 12;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case MONSTER::DIE:
			m_tFrame.iFrameStart = 16;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}
