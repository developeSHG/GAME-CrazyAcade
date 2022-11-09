#include "stdafx.h"
#include "CollisionMgr.h"

#include "Unit.h"
#include "Player.h"
#include "Boss.h"
#include "Ballon.h"
#include "Stem.h"
#include "Monster.h"
#include "Block.h"
#include "Item.h"
#include "ObjMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//RECT rc = {};
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
	//		{
	//			pDest->Set_Dead();
	//			pSource->Set_Dead();
	//		}
	//	}
	//}
}

void CCollisionMgr::CollisionRectEX(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//float fMoveX = 0.f, fMoveY = 0.f;
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
	//		{
	//			float x = pSource->Get_Info().fx;
	//			float y = pSource->Get_Info().fy;

	//			if (fMoveX > fMoveY)
	//			{
	//				if (y < pDest->Get_Info().fy)
	//					fMoveY *= -1.f;

	//				pSource->Set_Pos(x, y + fMoveY);
	//			}
	//			else
	//			{
	//				if (x < pDest->Get_Info().fx)
	//					fMoveX *= -1.f;

	//				pSource->Set_Pos(x + fMoveX, y);
	//			}

	//		}
	//	}
	//}

}

void CCollisionMgr::CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (CheckSphere(pDest, pSource))
	//		{
	//			pDest->Set_Dead();
	//			pSource->Set_Dead();
	//		}
	//	}
	//}
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	//float fRadiusSum = (pDst->Get_Info().fcx * 0.5f) + (pSrc->Get_Info().fcx * 0.5f);
	//float x = pDst->Get_Info().fx - pSrc->Get_Info().fx;
	//float y = pDst->Get_Info().fy - pSrc->Get_Info().fy;

	//float fDist = sqrtf(x * x + y * y);

	//return fRadiusSum > fDist;
	return false;
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadiusSumX = (pDst->Get_Info().fcx * 0.5f) + (pSrc->Get_Info().fcx * 0.5f);
	float fRadiusSumY = (pDst->Get_Info().fcy * 0.5f) + (pSrc->Get_Info().fcy * 0.5f);

	// fabs 절대값 구해주는 함수. 
	float fDistX = fabs(pDst->Get_Info().fx - pSrc->Get_Info().fx);
	float fDistY = fabs(pDst->Get_Info().fy - pSrc->Get_Info().fy);

	if (fRadiusSumX > fDistX && fRadiusSumY > fDistY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	return false;
}

void CCollisionMgr::CollisionPlayerZeroMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (65 > left)
			fMoveX = left - 65;
		if (170 > top)
			fMoveY = top - 170;
		if (580 < right)
			fMoveX = right - (580);
		if (560 < bottom)
			fMoveY = bottom - (560);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX && PLAYER::SPACEON != SCAST<CPlayer*>(pDest)->Get_PlayerState() || fMoveY && PLAYER::SPACEON != SCAST<CPlayer*>(pDest)->Get_PlayerState())
			pDest->Set_Pos(x - fMoveX, y - fMoveY);
	}
}

void CCollisionMgr::CollisionBallonZeroMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (65 > left)
			fMoveX = left - 65;
		if (170 > top)
			fMoveY = top - 170;
		if (580 < right)
			fMoveX = right - (580);
		if (560 < bottom)
			fMoveY = bottom - (560);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX || fMoveY)
		{
			if (BALLON::NONE == SCAST<CBallon*>(pDest)->Get_ThrowDir())
				pDest->Set_Pos(x - fMoveX, y - fMoveY);
			/*else if (BALLON::LEFT == SCAST<CBallon*>(pDest)->Get_ThrowDir() && 0 - POINT_X > left)
				pDest->Set_Pos(MAP_X + TILE_SIZE_X / 2 + POINT_X / 2, y - fMoveY);
			else if (BALLON::UP == SCAST<CBallon*>(pDest)->Get_ThrowDir() && 0 > top)
				pDest->Set_Pos(x - fMoveX, MAP_Y + (POINT_Y + POINT_X / 2));
			else if (BALLON::RIGHT == SCAST<CBallon*>(pDest)->Get_ThrowDir() && MAP_X + TILE_SIZE_X + POINT_X < right)
				pDest->Set_Pos(0 - TILE_SIZE_X / 2 - POINT_X / 2, y - fMoveY);
			else if (BALLON::DOWN == SCAST<CBallon*>(pDest)->Get_ThrowDir() && MAP_Y + +POINT_Y < bottom)
				pDest->Set_Pos(x - fMoveX, 0 - (POINT_Y + POINT_X / 2));

			SCAST<CUnit*>(pDest)->LateInit();*/
		}
	}
}

void CCollisionMgr::CollisionStemZeroMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (65 > left)
			fMoveX = left - 65;
		if (170 > top)
			fMoveY = top - 170;
		if (580 < right)
			fMoveX = right - (580);
		if (560 < bottom)
			fMoveY = bottom - (560);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX || fMoveY)
			pDest->Set_Dead();
	}
}

void CCollisionMgr::CollisionMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{	
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (POINT_X > left)
			fMoveX = left - POINT_X;
		if (POINT_Y > top)
			fMoveY = top - POINT_Y;
		if (MAP_X + POINT_X < right)
			fMoveX = right - (MAP_X + POINT_X);
		if (MAP_Y + POINT_Y < bottom)
			fMoveY = bottom - (MAP_Y + +POINT_Y);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;
		
		if (fMoveX || fMoveY)
			pDest->Set_Pos(x-fMoveX, y-fMoveY);

		//if(fMoveX || fMoveY)
		//	SCAST<CUnit*>(pDest)->LateInit();
	}
}

void CCollisionMgr::CollisionPlayerMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (POINT_X > left)
			fMoveX = left - POINT_X;
		if (POINT_Y > top)
			fMoveY = top - POINT_Y;
		if (MAP_X + POINT_X < right)
			fMoveX = right - (MAP_X + POINT_X);
		if (MAP_Y + POINT_Y < bottom)
			fMoveY = bottom - (MAP_Y + +POINT_Y);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX || fMoveY)
		{
			if(false == SCAST<CPlayer*>(pDest)->Get_LeapCheck() && false == SCAST<CPlayer*>(pDest)->Get_BoardState())
				pDest->Set_Pos(x - fMoveX, y - fMoveY);
		}

		//if(fMoveX || fMoveY)
		//	SCAST<CUnit*>(pDest)->LateInit();
	}
}

void CCollisionMgr::CollisionBallonMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (POINT_X > left)
			fMoveX = left - POINT_X;
		if (POINT_Y > top)
			fMoveY = top - POINT_Y;
		if (MAP_X + POINT_X < right)
			fMoveX = right - (MAP_X + POINT_X);
		if (MAP_Y + POINT_Y < bottom)
			fMoveY = bottom - (MAP_Y + +POINT_Y);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;


		if (fMoveX || fMoveY)
		{
			if (BALLON::NONE == SCAST<CBallon*>(pDest)->Get_ThrowDir())
				pDest->Set_Pos(x - fMoveX, y - fMoveY);
			else if (BALLON::LEFT == SCAST<CBallon*>(pDest)->Get_ThrowDir() && 0-POINT_X > left)
				pDest->Set_Pos(MAP_X+TILE_SIZE_X/2 + POINT_X/2, y - fMoveY);
			else if (BALLON::UP == SCAST<CBallon*>(pDest)->Get_ThrowDir() && 0 > top)
				pDest->Set_Pos(x-fMoveX, MAP_Y + (POINT_Y + POINT_X / 2));
			else if (BALLON::RIGHT == SCAST<CBallon*>(pDest)->Get_ThrowDir() && MAP_X + TILE_SIZE_X  + POINT_X < right)
				pDest->Set_Pos(0 - TILE_SIZE_X/2 - POINT_X/2, y - fMoveY);
			else if (BALLON::DOWN == SCAST<CBallon*>(pDest)->Get_ThrowDir() && MAP_Y + +POINT_Y < bottom)
				pDest->Set_Pos(x - fMoveX, 0 - (POINT_Y + POINT_X / 2));

			SCAST<CUnit*>(pDest)->LateInit();
		}
	}
}

void CCollisionMgr::CollisionPlayerBoss(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()) && false == SCAST<CPlayer*>(pDest)->Get_InvinState() && false == SCAST<CPlayer*>(pDest)->Get_BoardState())
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck() && false == SCAST<CPlayer*>(pDest)->Get_OnItemState() && false == SCAST<CBoss*>(pSource)->Get_RealBubbleState())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
				else if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck() && true == SCAST<CBoss*>(pSource)->Get_RealBubbleState())
					SCAST<CBoss*>(pSource)->Set_DieState();
				else if (true == SCAST<CPlayer*>(pDest)->Get_OnItemState())
				{
					SCAST<CPlayer*>(pDest)->Set_BoardState(true);
				}
				//else if (true == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				//	SCAST<CUnit*>(pDest)->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::CollisionBossMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (POINT_X > left)
			fMoveX = left - POINT_X;
		if (POINT_Y > top)
			fMoveY = top - POINT_Y;
		if (MAP_X + POINT_X < right)
			fMoveX = right - (MAP_X + POINT_X);
		if (MAP_Y + POINT_Y < bottom)
			fMoveY = bottom - (MAP_Y + +POINT_Y);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX || fMoveY)
		{
			pDest->Set_Pos(x - fMoveX, y - fMoveY);

			if(false == SCAST<CBoss*>(pDest)->Get_ShadowState())
				SCAST<CBoss*>(pDest)->Set_AiState();
			else if(true == SCAST<CBoss*>(pDest)->Get_ShadowState())
				SCAST<CBoss*>(pDest)->Set_ShadowMove();
		}
	}
}

void CCollisionMgr::CollisionBossBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				CBlock* pBlock = SCAST<class CBlock*>(pSource);

				float x = pDest->Get_Info().fx;
				float y = pDest->Get_Info().fy;

				if (BLOCK::TILE != pBlock->Get_Property())
				{
					if (BLOCK::HIDE != pBlock->Get_Property() && BLOCK::WITH != pBlock->Get_Property())
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						if (true == pBlock->Get_ActingCreate())
						{
							if (false == SCAST<CBoss*>(pDest)->Get_ShadowState())
								SCAST<CBoss*>(pDest)->Set_AiState();
							else if (true == SCAST<CBoss*>(pDest)->Get_ShadowState())
								SCAST<CBoss*>(pDest)->Set_ShadowMove();
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionBossStem(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CStem*>(pSource)->Get_BossStem())
				{
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
					//SCAST<CBoss*>(pDest)->Set_Hp();
				}
			}
			/*else
				SCAST<CBoss*>(pDest)->Set_LateInit();*/
		}
	}
}

void CCollisionMgr::CollisionMonsterMap(list<CObj*>& rDst)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDest : rDst)
	{
		LONG fMoveX = 0;
		LONG fMoveY = 0;
		LONG left = LONG(pDest->Get_Info().fx - (pDest->Get_Info().fcx / 2.f));
		LONG top = LONG(pDest->Get_Info().fy - (pDest->Get_Info().fcy / 2.f));
		LONG right = LONG(pDest->Get_Info().fx + (pDest->Get_Info().fcx / 2.f));
		LONG bottom = LONG(pDest->Get_Info().fy + (pDest->Get_Info().fcy / 2.f));

		if (POINT_X > left)
			fMoveX = left - POINT_X;
		if (POINT_Y > top)
			fMoveY = top - POINT_Y;
		if (MAP_X + POINT_X < right)
			fMoveX = right - (MAP_X + POINT_X);
		if (MAP_Y + POINT_Y < bottom)
			fMoveY = bottom - (MAP_Y + +POINT_Y);

		float x = pDest->Get_Info().fx;
		float y = pDest->Get_Info().fy;

		if (fMoveX || fMoveY)
		{
			pDest->Set_Pos(x - fMoveX, y - fMoveY);
			SCAST<CMonster*>(pDest)->Set_AiState();
		}
	}
}

void CCollisionMgr::CollisionPlayerMonster(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()) && false == SCAST<CPlayer*>(pDest)->Get_InvinState() && false == SCAST<CPlayer*>(pDest)->Get_BoardState())
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() &&  false == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck() && false == SCAST<CPlayer*>(pDest)->Get_OnItemState())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
				else if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && true == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
					SCAST<CMonster*>(pSource)->Set_DieState();
				else if (true == SCAST<CPlayer*>(pDest)->Get_OnItemState())
				{
					SCAST<CPlayer*>(pDest)->Set_BoardState(true);
				}
				//else if (true == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CUnit*>(pSource)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				//	SCAST<CUnit*>(pDest)->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::CollisionPlayerBallon(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	bool b = false;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(SCAST<CUnit*>(pDest), SCAST<CUnit*>(pSource), &fMoveX, &fMoveY))
			{
				// 물풍선 생성시점에 플레이어가 풍선과 마찰 올라가있으며 밀기상태가 아닐때, 또는 한번이상 밀려서 못밀려야할때
				if (false == SCAST<CUnit*>(pDest)->Get_PushState() && false == SCAST<CUnit*>(pSource)->Get_BallonOn() || true == SCAST<CBallon*>(pSource)->Get_DirCheck())
				{
					if(false == SCAST<CPlayer*>(pDest)->Get_LeapCheck() && PLAYER::SPACEON != SCAST<CPlayer*>(pDest)->Get_PlayerState())
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
				}
				// 플레이어가 물풍선을 밀수있는 상태일때 
				else if (true == SCAST<CUnit*>(pDest)->Get_PushState() && false == SCAST<CUnit*>(pSource)->Get_BallonOn() && false == SCAST<CBallon*>(pSource)->Get_DirCheck())
				{
					if (false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
						SCAST<CUnit*>(pSource)->Set_PushState(true);
				}
			}
			// 플레이어가 물풍선에 접촉해있지 않을때 물풍선위에 플레이어상태와 물풍선을 취소
			else if (true == SCAST<CUnit*>(pSource)->Get_BallonOn() && false == SCAST<CBallon*>(pSource)->Get_DirCheck())
			{
				SCAST<CUnit*>(pDest)->Set_BallonOnState(false);
				SCAST<CUnit*>(pSource)->Set_BallonOnState(false);
			}
		}
	}
	if (rSrc.empty())
	{
		if (!rDst.empty())
			SCAST<CUnit*>(rDst.front())->Set_BallonOnState(false);
	}
}

void CCollisionMgr::CollisionPlayerBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY) && false == SCAST<CPlayer*>(pDest)->Get_BoardState() && PLAYER::SPACEON != SCAST<CPlayer*>(pDest)->Get_PlayerState())
			{
				CBlock* pBlock = SCAST<class CBlock*>(pSource);

				float x = pDest->Get_Info().fx;
				float y = pDest->Get_Info().fy;

				if (BLOCK::TILE != pBlock->Get_Property()
					&& BLOCK::PUSH != pBlock->Get_Property()
					&& BLOCK::HIDE != pBlock->Get_Property()
					&& BLOCK::THORN != pBlock->Get_Property()
					&& BLOCK::TELEPORT1 != pBlock->Get_Property()
					&& BLOCK::TELEPORT2 != pBlock->Get_Property()
					&& BLOCK::TELEPORT3 != pBlock->Get_Property()
					&& BLOCK::TELEPORT4 != pBlock->Get_Property()
					&& BLOCK::WITH != pBlock->Get_Property())
				{
					if (false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
				}
				else if (BLOCK::PUSH == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					if (pDest->Get_Rect()->right <= pBlock->Get_Rect()->left)
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						pBlock->Set_PushDir(BLOCK::RIGHT);
					}
					else if (pDest->Get_Rect()->left >= pBlock->Get_Rect()->right)
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						pBlock->Set_PushDir(BLOCK::LEFT);
					}
					else if (pDest->Get_Rect()->top >= pBlock->Get_Rect()->bottom)
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						pBlock->Set_PushDir(BLOCK::UP);
					}
					else if (pDest->Get_Rect()->bottom <= pBlock->Get_Rect()->top)
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						pBlock->Set_PushDir(BLOCK::DOWN);
					}
				}
				else if (BLOCK::HIDE == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					if (x > pBlock->Get_Rect()->left - 10.f && x < pBlock->Get_Rect()->right + 10.f 
						&& y > pBlock->Get_Rect()->top - 10.f && y < pBlock->Get_Rect()->bottom + 10.f)
					{
						SCAST<CPlayer*>(pDest)->Set_HideState(pBlock->Get_Info().fx, pBlock->Get_Info().fy);
					}
				}
				else if (BLOCK::THORN == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					if (x > pBlock->Get_Rect()->left + 19.f && x < pBlock->Get_Rect()->right - 19.f)
					{
						if (true == SCAST<CUnit*>(pDest)->Get_BubbleState())
						{
							//pDest->Set_Pos(100, 100);
							// 죽음
						}
					}
					else if (5 != SCAST<CBlock*>(pBlock)->Get_DrawID())
					{
							Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
					}
				}
				else if (BLOCK::TELEPORT1 == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					list<CObj*>* plistObj1 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj1)
					{
						if (BLOCK::TELEPORT2 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
						}
					}
				}
				else if (BLOCK::TELEPORT2 == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					list<CObj*>* plistObj2 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj2)
					{
						if (BLOCK::TELEPORT1 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);		
						}
					}
				}
				else if (BLOCK::TELEPORT3 == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					list<CObj*>* plistObj3 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj3)
					{
						if (BLOCK::TELEPORT4 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
						}
					}
				}
				else if (BLOCK::TELEPORT4 == pBlock->Get_Property() && false == SCAST<CPlayer*>(pDest)->Get_LeapCheck())
				{
					list<CObj*>* plistObj4 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj4)
					{
						if (BLOCK::TELEPORT3 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
						}
					}
				}
			}
			// 텔레포트 초기화 (시작)
			else if (BLOCK::TELEPORT1 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			else if (BLOCK::TELEPORT2 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			else if (BLOCK::TELEPORT3 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			else if (BLOCK::TELEPORT4 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			// 텔레포트 초기화 (끝)
		}
	}
}

void CCollisionMgr::CollisionMonsterBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY) && false == SCAST<CMonster*>(pDest)->Get_ChetkiState() )
			{
				CBlock* pBlock = SCAST<class CBlock*>(pSource);

				float x = pDest->Get_Info().fx;
				float y = pDest->Get_Info().fy;

				if (BLOCK::TILE != pBlock->Get_Property())
				{
					if (BLOCK::HIDE != pBlock->Get_Property() &&  BLOCK::WITH != pBlock->Get_Property())
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						if (true == pBlock->Get_ActingCreate())
						{
							SCAST<CMonster*>(pDest)->Set_AiState();
						}
					}
					else if (BLOCK::HIDE == pBlock->Get_Property())
					{
						if (x > pBlock->Get_Rect()->left - 5.f && x < pBlock->Get_Rect()->right + 5.f
							&& y > pBlock->Get_Rect()->top - 5.f && y < pBlock->Get_Rect()->bottom + 5.f)
						{
							if(false == SCAST<CMonster*>(pDest)->Get_HideState())
								SCAST<CMonster*>(pDest)->Set_HideStatePos(pBlock->Get_Info().fx, pBlock->Get_Info().fy);
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionMonsterBallon(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				if(false == SCAST<CBallon*>(pSource)->Get_ThrowState() && false == SCAST<CBallon*>(pSource)->Get_BossBallon() || false == SCAST<CBallon*>(pSource)->Get_ThrowState() &&  true == SCAST<CBallon*>(pSource)->Get_BossBallon())
					Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
			}
		}
	}
}

void CCollisionMgr::CollisionBallonBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				CBlock* pBlock = SCAST<CBlock*>(pSource);

				float x = pDest->Get_Info().fx;
				float y = pDest->Get_Info().fy;

				if (BLOCK::HIDE != pBlock->Get_Property()
					&& BLOCK::THORN != pBlock->Get_Property()
					&& BLOCK::DUNKS != pBlock->Get_Property()
					&& BLOCK::TELEPORT1 != pBlock->Get_Property()
					&& BLOCK::TELEPORT2 != pBlock->Get_Property()
					&& BLOCK::TELEPORT3 != pBlock->Get_Property()
					&& BLOCK::TELEPORT4 != pBlock->Get_Property()
					&& BLOCK::WITH != pBlock->Get_Property())
				{
					if (false == SCAST<CBallon*>(pDest)->Get_ThrowState())
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						SCAST<CUnit*>(pDest)->LateInit();			// 물풍선 속도 0 초기화함수
					}
				}
				else if (BLOCK::HIDE == pBlock->Get_Property())
				{
					if (x > pBlock->Get_Rect()->left + 15.f && x < pBlock->Get_Rect()->right - 15.f)
					{
						pDest->Set_Pos(pBlock->Get_Info().fx, pBlock->Get_Info().fy);
						SCAST<CUnit*>(pDest)->LateInit();
						//SCAST<CUnit*>(pDest)->Set_ZeroSize();
					}
					
				}
				else if (BLOCK::THORN == pBlock->Get_Property())
				{
					RECT rc = {};
					if (0 == SCAST<CBlock*>(pBlock)->Get_DrawID() && pDest->Get_Rect()->top == pBlock->Get_Rect()->bottom
						|| 1 == SCAST<CBlock*>(pBlock)->Get_DrawID() 
						|| 2 == SCAST<CBlock*>(pBlock)->Get_DrawID() && pDest->Get_Rect()->bottom == pBlock->Get_Rect()->top
						|| 3 == SCAST<CBlock*>(pBlock)->Get_DrawID() && pDest->Get_Rect()->right == pBlock->Get_Rect()->left
						|| 4 == SCAST<CBlock*>(pBlock)->Get_DrawID() && pDest->Get_Rect()->left == pBlock->Get_Rect()->right)
					{
						SCAST<CUnit*>(pDest)->Set_BubbleState(true);
					}
					else if (5 == SCAST<CBlock*>(pBlock)->Get_DrawID() && IntersectRect(&rc, &pDest->Get_TileRC(), &pBlock->Get_TileRC()))
					{
						pDest->Set_Pos(pBlock->Get_Info().fx, pBlock->Get_Info().fy);
						SCAST<CUnit*>(pDest)->Set_BubbleState(true);
					}
					else if(5 != SCAST<CBlock*>(pBlock)->Get_DrawID())
					{
						Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
						SCAST<CUnit*>(pDest)->LateInit();
					}
				}
				else if (BLOCK::TELEPORT1 == pBlock->Get_Property())
				{
					list<CObj*>* plistObj1 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj1)
					{
						if (BLOCK::TELEPORT2 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState()
							&& false == SCAST<CBallon*>(pDest)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
							SCAST<CBallon*>(pDest)->Set_TeleState(true);
						}
					}
				}
				else if (BLOCK::TELEPORT2 == pBlock->Get_Property())
				{
					list<CObj*>* plistObj2 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj2)
					{
						if (BLOCK::TELEPORT1 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState()
							&& false == SCAST<CBallon*>(pDest)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
							SCAST<CBallon*>(pDest)->Set_TeleState(true);
						}	
					}
				}
				else if (BLOCK::TELEPORT3 == pBlock->Get_Property())
				{
					list<CObj*>* plistObj3 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj3)
					{
						if (BLOCK::TELEPORT4 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState()
							&& false == SCAST<CBallon*>(pDest)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
							SCAST<CBallon*>(pDest)->Set_TeleState(true);
						}
					}
				}
				else if (BLOCK::TELEPORT4 == pBlock->Get_Property())
				{
					list<CObj*>* plistObj4 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BLOCK);
					for (auto& pExit : *plistObj4)
					{
						if (BLOCK::TELEPORT3 == SCAST<CBlock*>(pExit)->Get_Property() && false == SCAST<CBlock*>(pBlock)->Get_TeleState()
							&& false == SCAST<CBallon*>(pDest)->Get_TeleState())
						{
							pDest->Set_Pos(pExit->Get_Info().fx, pExit->Get_Info().fy);
							SCAST<CBlock*>(pExit)->Set_TeleState(true);
							SCAST<CBallon*>(pDest)->Set_TeleState(true);
						}
					}
				}
				else if (BLOCK::WITH == pBlock->Get_Property())
				{
					for (auto pBlock : rSrc)
					{
						if(BLOCK::WITH == SCAST<CBlock*>(pBlock)->Get_Property())
							SCAST<CBlock*>(pBlock)->Set_StemCreate();
					}	
					
				}
			}
			// 텔레포트 초기화 (시작)
			else if (BLOCK::TELEPORT1 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					if (true == SCAST<CBallon*>(pDest)->Get_TeleState())
						SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			else if (BLOCK::TELEPORT2 == SCAST<CBlock*>(pSource)->Get_Property() &&  true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					if (true == SCAST<CBallon*>(pDest)->Get_TeleState())
						SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}		
			else if (BLOCK::TELEPORT3 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					if (true == SCAST<CBallon*>(pDest)->Get_TeleState())
						SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			else if (BLOCK::TELEPORT4 == SCAST<CBlock*>(pSource)->Get_Property() && true == SCAST<CBlock*>(pSource)->Get_TeleState())
			{
				RECT rc = {};
				if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
				{
					if (true == SCAST<CBallon*>(pDest)->Get_TeleState())
						SCAST<CBlock*>(pSource)->Set_TeleState(false);
				}
			}
			// 텔레포트 초기화 (끝)
		}
	}
}

void CCollisionMgr::CollisionStemBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				CBlock* pBlock = SCAST<CBlock*>(pSource);
				
				if (BLOCK::BASIC == pBlock->Get_Property()
					|| BLOCK::HIDE == pBlock->Get_Property()
					|| BLOCK::PUSH == pBlock->Get_Property())
				{
					//pDest->Set_Dead();
					SCAST<CBlock*>(pSource)->Create_Item();
					pSource->Set_Dead();
				}
			
			}
		}
	}
}

void CCollisionMgr::CollisionPlayerStem(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()) && false == SCAST<CPlayer*>(pDest)->Get_BoardState() && false == SCAST<CPlayer*>(pDest)->Get_InvinState())
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CPlayer*>(pDest)->Get_ShieldState() && false == SCAST<CPlayer*>(pDest)->Get_OnItemState())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
				else if (true == SCAST<CPlayer*>(pDest)->Get_OnItemState())
				{
					SCAST<CPlayer*>(pDest)->Set_BoardState(true);
				}
			}
		}
	}
}

void CCollisionMgr::Set_Blocked(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float x = pDst->Get_Info().fx;
	float y = pDst->Get_Info().fy;

	if (*pMoveX > *pMoveY)
	{
		if (y < pSrc->Get_Info().fy)
			*pMoveY *= -1.f;

		pDst->Set_Pos(x, y + *pMoveY);
	}
	else
	{
		if (x < pSrc->Get_Info().fx)
			*pMoveX *= -1.f;

		pDst->Set_Pos(x + *pMoveX, y);
	}
}

void CCollisionMgr::CollisionStem(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
			}
		}
	}
}

void CCollisionMgr::CollisionMonsterStem(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && false == SCAST<CStem*>(pSource)->Get_BossStem())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
			}
		}
	}
}

void CCollisionMgr::CollisionBossBallon(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	float Teleport1_x = 0.f, Teleport1_y = 0.f;
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				if (false == SCAST<CBallon*>(pSource)->Get_ThrowState() && false == SCAST<CBallon*>(pSource)->Get_BossBallon())
				{
					if (false == SCAST<CBoss*>(pDest)->Get_ShadowState())
						SCAST<CBoss*>(pDest)->Set_AiState();
					else if (true == SCAST<CBoss*>(pDest)->Get_ShadowState())
						SCAST<CBoss*>(pDest)->Set_ShadowMove();
				}
			}
		}
	}
}

void CCollisionMgr::CollisionItemBoss(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && true == SCAST<CItem*>(pDest)->Get_CreateCheck())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
			}
		}
	}
}

void CCollisionMgr::CollisionItemStem(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->Get_TileRC(), &pSource->Get_TileRC()))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && true == SCAST<CItem*>(pDest)->Get_CreateCheck())
					SCAST<CUnit*>(pDest)->Set_BubbleState(true);
			}
		}
	}
}

void CCollisionMgr::CollisionDart(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			RECT rc = {};
			if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
			{
				pDest->Set_Dead();
				SCAST<CUnit*>(pSource)->Set_BubbleState(true);
			}
		}
	}
}

void CCollisionMgr::CollisionItemBlock(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				if (false == SCAST<CUnit*>(pDest)->Get_BubbleState() && true == SCAST<CItem*>(pDest)->Get_CreateCheck())
					Set_Blocked(pDest, pSource, &fMoveX, &fMoveY);
			}
		}
	}
}
