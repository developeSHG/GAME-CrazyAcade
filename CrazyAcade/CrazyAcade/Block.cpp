#include "stdafx.h"
#include "Block.h"

#include "Acting.h"
#include "Item.h"
#include "Stem.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CBlock::CBlock()
{
}


CBlock::~CBlock()
{
	Release();
}

int CBlock::m_iRan = 0;

void CBlock::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = TILE_SIZE_X;
	m_tInfo.fcy = TILE_SIZE_Y;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_bIsInit = false;
	m_dwGameStartTime = NULL;
	m_fSpeed = 1.f;
	m_bBallonOn = false;
	m_bBubbleState = true;
	m_bPushState = false;
	m_bCreateTime = GetTickCount();

	// 블럭 고유변수
	m_iTime = NULL;
	m_eProperty = BLOCK::TILE;
	m_bTeleState = false;
	m_iDrawID = 0;
	m_iOption = BLOCK::TILE;
	m_bStemCreate = false;

	switch (m_iScene)
	{
	case 1:
		Set_Load1();
		break;
	case 2:
		Set_Load2();
		break;
	case 3:
		Set_Load3();
		break;
	}
}

int CBlock::Update()
{
	if (m_bIsDead)
	{
		Create_Acting();
		/*Create_Item();*/
		return OBJ_DEAD;
	}

	switch (m_iScene)
	{
	case 1:
		Set_Load1();
		break;
	case 2:
		Set_Load2();
		break;
	case 3:
		Set_Load3();
		break;
	}

	if (GetAsyncKeyState('U'))
	{
		//m_tInfo.fx -= TILE_SIZE_X;
	}


	return OBJ_LIVE;
}

void CBlock::LateUpdate()
{
	switch (m_eProperty)
	{
	case BLOCK::BASIC:
		break;
	case BLOCK::PUSH:
		list<CObj*>* plistBlock = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);

		if ((*plistBlock).empty())
			break;

		for (auto& pBlock : *plistBlock)
		{
			RECT rc ={};
			if (IntersectRect(&rc, &m_tRect, pBlock->Get_Rect()) /*&& BLOCK::WITH != SCAST<CBlock*>(pBlock)->Get_Property()*/)
			{
				float fRadiusSumX = (m_tInfo.fcx * 0.5f) + (pBlock->Get_Info().fcx * 0.5f);
				float fRadiusSumY = (m_tInfo.fcy * 0.5f) + (pBlock->Get_Info().fcy * 0.5f);

				float fDistX = fabs(m_tInfo.fx - pBlock->Get_Info().fx);
				float fDistY = fabs(m_tInfo.fy - pBlock->Get_Info().fy);

				float fMoveX = 0;
				float fMoveY = 0;
				if (fRadiusSumX > fDistX && fRadiusSumY > fDistY)
				{
					fMoveX = fRadiusSumX - fDistX;
					fMoveY = fRadiusSumY - fDistY;
				}

				if (0 == fMoveX || 0 == fMoveY)
					continue;
				else if (fMoveX || fMoveY && BLOCK::PUSH == m_eProperty)
				{
					if (fMoveX > fMoveY) 
					{
						if (m_tInfo.fy < pBlock->Get_Info().fy)
							fMoveY *= -1.f;

						m_tInfo.fy += fMoveY;
				
					}
					else if(fMoveY > fMoveX)
					{
						if (m_tInfo.fx < pBlock->Get_Info().fx)
							fMoveX *= -1.f;

						m_tInfo.fx += fMoveX;
					}
				}

			}
		}
		break;
	}

	if (true == m_bStemCreate && BLOCK::WITH == m_eProperty)
	{
		if (m_dwCreateTime + 1800 < GetTickCount() )
		{
			m_uPower = SCAST<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_BallonPower();
			CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(0, STEM::CENTER));
			for (size_t i = BALLON::LEFT; i < BALLON::DOWN; ++i)
			{
				m_eStemDeleteDir[i] = false;
			}
			for (size_t i = 1; i < m_uPower + 1; ++i)
			{
				if (false == m_eStemDeleteDir[BALLON::LEFT])
					CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::LEFT));
				if (false == m_eStemDeleteDir[BALLON::UP])
					CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::UP));
				if (false == m_eStemDeleteDir[BALLON::RIGHT])
					CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::RIGHT));
				if (false == m_eStemDeleteDir[BALLON::DOWN])
					CObjMgr::Get_Instance()->AddObject(OBJID::STEM, Create_Stem(i, STEM::DOWN));
			}
			m_bStemCreate = false;
		}
	}
	else
	{
		m_dwCreateTime = GetTickCount();
	}


	if (3 == m_iScene)
	{
		if (BLOCK::THORN == m_iOption || BLOCK::TELEPORT1 == m_iOption || BLOCK::TELEPORT2 == m_iOption || BLOCK::TELEPORT3 == m_iOption  || BLOCK::TELEPORT4 == m_iOption)
		{
			CObj::LateInit();
			CUnit::MoveFrame();
		}
	}
}

void CBlock::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::TileRC_Check();
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if (m_tInfo.fx < 0 || m_tInfo.fx > WINCX)
		return;


	//hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	//GdiTransparentBlt(hDC,//출력할 DC
	//	int(m_tRect.left - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y / 2.f - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
	//	int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
	//	hMemDC,// 복사할 DC 
	//	int((m_tInfo.fcx + m_tFrameSize.x) * m_iDrawID + m_tFrameStart.x), int(m_tInfo.fcy + m_tFrameSize.y) * m_tFrame.iFrameScene + +m_tFrameStart.y,// 출력할 비트맵의 시작 좌표 
	//	int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
	//	RGB(255, 0, 255));// 내가 빼고자하는 색상. 

	if (true == m_bActingCreate)
	{
		if (3 == m_iScene)
		{
			if (BLOCK::THORN == m_iOption || BLOCK::TELEPORT1 == m_iOption || BLOCK::TELEPORT2 == m_iOption || BLOCK::TELEPORT3 == m_iOption || BLOCK::TELEPORT4 == m_iOption)
			{
				hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
				GdiTransparentBlt(hDC,//출력할 DC
					int(m_tRect.left - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + m_tFrameSize.x) * (m_tFrame.iFrameStart)), int(m_tInfo.fcy + m_tFrameSize.y) * m_tFrame.iFrameScene + +m_tFrameStart.y,// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상. 
			}
			else
			{
				hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
				GdiTransparentBlt(hDC,//출력할 DC
					int(m_tRect.left - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
					int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
					hMemDC,// 복사할 DC 
					int((m_tInfo.fcx + m_tFrameSize.x) * m_iDrawID + m_tFrameStart.x), int(m_tInfo.fcy + m_tFrameSize.y) * m_tFrame.iFrameScene + +m_tFrameStart.y,// 출력할 비트맵의 시작 좌표 
					int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
					RGB(255, 0, 255));// 내가 빼고자하는 색상. 
			}
		}
		else
		{
			hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
			GdiTransparentBlt(hDC,//출력할 DC
				int(m_tRect.left - m_tFramePos.x), int(m_tRect.top - m_tFrameSize.y / 2.f - m_tFramePos.y),// 그림을 그릴 시작 좌표 XY
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 그림의 크기 
				hMemDC,// 복사할 DC 
				int((m_tInfo.fcx + m_tFrameSize.x) * m_iDrawID + m_tFrameStart.x), int(m_tInfo.fcy + m_tFrameSize.y) * m_tFrame.iFrameScene + +m_tFrameStart.y,// 출력할 비트맵의 시작 좌표 
				int(m_tInfo.fcx + m_tFrameSize.x), int(m_tInfo.fcy + m_tFrameSize.y),// 출력할 비트 맵의 전체 가로 세로 길이 
				RGB(255, 0, 255));// 내가 빼고자하는 색상. 
		}
	}
	else
	{
		if (NULL != m_iTime && m_bCreateTime + m_iTime < GetTickCount() && false == m_bActingCreate)
		{
			CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
			CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);

			m_bActingCreate = true;
		}
	}

	if (CSceneMgr::SCENEID::SCENE_STAGE0 == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		hMemDC = CBmpMgr::Get_Instance()->FindImage(L"Flopy_Block");
		GdiTransparentBlt(hDC,//출력할 DC
			int(m_tRect.left), int(m_tRect.top - 9),// 그림을 그릴 시작 좌표 XY
			int(m_tInfo.fcx), int(m_tInfo.fcy + 18),// 출력할 그림의 크기 
			hMemDC,// 복사할 DC 
			int((m_tInfo.fcx) * m_iDrawID), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
			int(m_tInfo.fcx), int(m_tInfo.fcy + 18),// 출력할 비트 맵의 전체 가로 세로 길이 
			RGB(255, 0, 255));// 내가 빼고자하는 색상. 
	}
	else if (CSceneMgr::SCENEID::SCENE_EDIT == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		//hMemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
		//GdiTransparentBlt(hDC,//출력할 DC
		//	int(m_tRect.left), int(m_tRect.top),// 그림을 그릴 시작 좌표 XY
		//	int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 그림의 크기 
		//	hMemDC,// 복사할 DC 
		//	int((m_tInfo.fcx) * m_iDrawID), int(m_tInfo.fcy) * m_tFrame.iFrameScene,// 출력할 비트맵의 시작 좌표 
		//	int(m_tInfo.fcx), int(m_tInfo.fcy),// 출력할 비트 맵의 전체 가로 세로 길이 
		//	RGB(255, 0, 255));// 내가 빼고자하는 색상. 

		TCHAR buffer[80];
		wsprintf(buffer, TEXT("%d"), m_iOption);
		TextOut(hDC, m_tRect.left, m_tRect.top, buffer, lstrlen(buffer));
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		Rectangle(hDC, m_tTile_Rc.left, m_tTile_Rc.top, m_tTile_Rc.right, m_tTile_Rc.bottom);
	}

}

void CBlock::Release()
{
}

void CBlock::LateInit()
{
	if (3 == m_iScene)
	{
		if (BLOCK::THORN == m_iOption)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 125;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (BLOCK::TELEPORT1 == m_iOption || BLOCK::TELEPORT2 == m_iOption || BLOCK::TELEPORT3 == m_iOption || BLOCK::TELEPORT4 == m_iOption)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 170;
			m_tFrame.dwFrameTime = GetTickCount();
		}
	}
}

void CBlock::Set_PushDir(BLOCK::DIR _eDir)
{
	switch (_eDir)
	{
	case BLOCK::LEFT:
		m_tInfo.fx -= m_fSpeed;
		break;
	case BLOCK::RIGHT:
		m_tInfo.fx += m_fSpeed;
		break;
	case BLOCK::UP:
		m_tInfo.fy -= m_fSpeed;
		break;
	case BLOCK::DOWN:
		m_tInfo.fy += m_fSpeed;
		break;
	}
}

void CBlock::Create_Acting()
{
	CObj* pObj = CAbstractFactory<CActing>::Create(m_tInfo.fx, m_tInfo.fy);
	CObjMgr::Get_Instance()->AddObject(OBJID::ACTING, pObj);
}

void CBlock::Create_Item()
{
	if (BLOCK::HIDE != m_eProperty && CSceneMgr::SCENEID::SCENE_STAGE0 != CSceneMgr::Get_Instance()->Get_SceneID())
	{
  		CObj* pObj = CAbstractFactory<CItem>::Create(m_tInfo.fx, m_tInfo.fy);
		int Ran = rand() % 1;  // 0~6, 7~11, 12~end
		if (0 == Ran)
		{
			//int i = rand() % 6;
			m_iRan = rand() % 70;


			if (0 <= m_iRan && 6 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(ITEM::DART+1)));
			else if( 7 <= m_iRan && 10 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(3)+ ITEM::FLY));
			else if (11 <= m_iRan && 14 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(4)+ ITEM::GAS));
			else if (15 <= m_iRan && 19 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(4) + ITEM::TURTLE));
			else if (20 <= m_iRan && 21 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(3) + ITEM::BANANA));
			else if(21 <= m_iRan && 23 >= m_iRan)
				SCAST<CItem*>(pObj)->Set_Property(ITEM::PROPERTY(rand() % int(ITEM::GLOVE)));
			

			CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
		}
	}
}

void CBlock::Set_Load1()
{
	switch (m_iOption)
	{
	case BLOCK::BASIC:
		m_eProperty = BLOCK::BASIC;
		m_pFrameKey = L"Basic";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 6;

		if (m_iDrawID > 3)
			m_iDrawID = 0;

		break;
	case BLOCK::PUSH:
		m_eProperty = BLOCK::PUSH;
		m_pFrameKey = L"Push";
		m_tFrameSize.y = 8;

		if (m_iDrawID > 1)
			m_iDrawID = 0;

		break;
	case BLOCK::STONE:
		m_eProperty = BLOCK::STONE;
		m_pFrameKey = L"Stone";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 28;
		m_tFramePos.y = 0;
		m_tFramePos.y = 12;

		if (m_iDrawID > 6)
			m_iDrawID = 0;

		if (6 == m_iDrawID)
			m_tFrameSize.x = 33;

		break;
	case BLOCK::HIDE:
		m_eProperty = BLOCK::HIDE;
		m_pFrameKey = L"Hide";
		m_tFrameSize.y = 19;
		m_tFramePos.y = 3;

		if (m_iDrawID > 1)
			m_iDrawID = 0;

		break;
	case BLOCK::THORN:
		m_eProperty = BLOCK::THORN;
		m_pFrameKey = L"Thorn";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 24;
		m_tFramePos.x = 0;
		m_tFramePos.y = 12;
		m_tFrameStart.x = 0;
		m_tFrameStart.y = 0;

		if (m_iDrawID > 5)
			m_iDrawID = 0;

		if (1 == m_iDrawID)
		{
			m_tFrameSize.x = 10;
			m_tFramePos.x = 5;
		}
		else if (2 == m_iDrawID || 3 == m_iDrawID)
			m_tFrameStart.x = 11;
		else if (4 == m_iDrawID)
			m_tFrameStart.x = 15;
		else if (5 == m_iDrawID)
			m_tFrameStart.x = 20;

		break;
	case BLOCK::DUNKS:
		m_eProperty = BLOCK::DUNKS;
		m_pFrameKey = L"Dunks";
		m_tFrameSize.x = -2;
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT1:
		m_eProperty = BLOCK::TELEPORT1;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT2:
		m_eProperty = BLOCK::TELEPORT2;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT3:
		m_eProperty = BLOCK::TELEPORT3;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT4:
		m_eProperty = BLOCK::TELEPORT4;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::DESTORY:
		m_eProperty = BLOCK::TILE;
		m_pFrameKey = NULL;
		m_iDrawID = 0;
		m_iOption = 0;
		break;
	}
}

void CBlock::Set_Load2()
{
	switch (m_iOption)
	{
	case BLOCK::BASIC:
		m_eProperty = BLOCK::BASIC;
		m_pFrameKey = L"Basic2";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 8;

		if (m_iDrawID > 1)
			m_iDrawID = 0;

		break;
	case BLOCK::PUSH:
		m_eProperty = BLOCK::PUSH;
		m_pFrameKey = L"Push2";
		m_tFrameSize.y = 8;

		if (m_iDrawID > 1)
			m_iDrawID = 0;

		break;
	case BLOCK::STONE:
		m_eProperty = BLOCK::STONE;
		m_pFrameKey = L"Stone2";
		m_tInfo.fcx = 40.f;
		m_tInfo.fcy = 40.f;
		m_tFrameStart.x = 120;
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 72;
		m_tFramePos.y = 36;

		if (m_iDrawID > 11)
			m_iDrawID = 0;

		if (0 == m_iDrawID)
		{
			m_tInfo.fcx = 120;
			m_tInfo.fcy = 110;
			m_tFrameSize.x = 0;
			m_tFrameStart.x = 0;
			m_tFrameSize.y = 0;
			m_tFramePos.y = -4;
		}
		if (9 == m_iDrawID || 8 == m_iDrawID)
		{
			
		}
		else if (9 == m_iDrawID || 10 == m_iDrawID)
		{
			
		}

		break;
	case BLOCK::WITH:
		m_eProperty = BLOCK::WITH;
		m_pFrameKey = L"With2";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 0;
		m_tFramePos.y = 0;
		m_tFramePos.y = 0;
		m_iDrawID = 0;
		break;
	case BLOCK::DESTORY:
		m_eProperty = BLOCK::TILE;
		m_pFrameKey = NULL;
		m_iDrawID = 0;
		m_iOption = 0;
		break;
	}
}

void CBlock::Set_Load3()
{
	switch (m_iOption)
	{
	case BLOCK::BASIC:
		m_eProperty = BLOCK::BASIC;
		m_pFrameKey = L"Basic3";
		m_tFrameSize.x = 0;
		m_tFrameSize.y = 7;

		if (m_iDrawID > 2)
			m_iDrawID = 0;

		break;
	case BLOCK::PUSH:
		m_eProperty = BLOCK::PUSH;
		m_pFrameKey = L"Push3";
		m_tFrameSize.y = 8;

		if (m_iDrawID > 1)
			m_iDrawID = 0;

		break;
	case BLOCK::STONE:
		m_eProperty = BLOCK::STONE;
		m_pFrameKey = L"Stone3";

		if (m_iDrawID > 3)
			m_iDrawID = 0;

		break;
	case BLOCK::THORN:
		m_eProperty = BLOCK::THORN;
		m_pFrameKey = L"Thorn3";
		m_tFrameSize.x = -1;
		m_tFrameSize.y = 28;

		m_iDrawID = 5;

		break;
	case BLOCK::TELEPORT1:
		m_eProperty = BLOCK::TELEPORT1;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT2:
		m_eProperty = BLOCK::TELEPORT2;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT3:
		m_eProperty = BLOCK::TELEPORT3;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::TELEPORT4:
		m_eProperty = BLOCK::TELEPORT4;
		m_pFrameKey = L"Teleport";
		m_iDrawID = 0;
		break;
	case BLOCK::DESTORY:
		m_eProperty = BLOCK::TILE;
		m_pFrameKey = NULL;
		m_iDrawID = 0;
		m_iOption = 0;
		break;
	}
}

CObj* CBlock::Create_Stem(size_t _uPower, STEM::DIR _eDir)
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
			&& BLOCK::WITH != SCAST<CBlock*>(pBlock)->Get_Property())
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

	return pStem;
}