#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Block.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
	m_bStartActing = true;
}


CObjMgr::~CObjMgr()
{
	Release();
}

int CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int OBJ_STATE = (*iter)->Update();
			if (OBJ_DEAD == OBJ_STATE)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
			if (m_listObj[i].empty())
				break;

		}
	}

	return 0;
}

void CObjMgr::LateUpdate()

{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->LateUpdate();
			if (m_listObj[i].empty())
				break;
		}
	}
	if (CSceneMgr::SCENEID::SCENE_STAGE0 == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		CCollisionMgr::CollisionPlayerZeroMap(m_listObj[OBJID::PLAYER]);
		CCollisionMgr::CollisionBallonZeroMap(m_listObj[OBJID::BALLON]);
		CCollisionMgr::CollisionStemZeroMap(m_listObj[OBJID::STEM]);
	}
	CCollisionMgr::CollisionPlayerMap(m_listObj[OBJID::PLAYER]);								// 플레이어-게임창 충돌
	CCollisionMgr::CollisionBallonMap(m_listObj[OBJID::BALLON]);								// 물풍선-게임창 충돌
	CCollisionMgr::CollisionMonsterMap(m_listObj[OBJID::MONSTER]);								// 몬스터-게임창 충돌
	//if (CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID())
	//{
		CCollisionMgr::CollisionMap(m_listObj[OBJID::BLOCK]);									// 블럭-게임창 충돌
	//}
	CCollisionMgr::CollisionMap(m_listObj[OBJID::ITEM]);										// 아이템-게임창 충돌
	CCollisionMgr::CollisionPlayerMonster(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);	// 플레이어-몬스터 충돌
	CCollisionMgr::CollisionPlayerBallon(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BALLON]);	// 플레이어-물풍선 충돌
	CCollisionMgr::CollisionPlayerStem(m_listObj[OBJID::PLAYER], m_listObj[OBJID::STEM]);		// 플레이어-물줄기 충돌
	CCollisionMgr::CollisionStem(m_listObj[OBJID::BALLON], m_listObj[OBJID::STEM]);				// 물풍선-물줄기 충돌
	CCollisionMgr::CollisionItemStem(m_listObj[OBJID::ITEM], m_listObj[OBJID::STEM]);			// 아이템-물줄기 충돌
	CCollisionMgr::CollisionPlayerBlock(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BLOCK]);		// 플레이어-블럭 충돌
	CCollisionMgr::CollisionMonsterBlock(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BLOCK]);	// 몬스터-블럭 충돌
	CCollisionMgr::CollisionMonsterBallon(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BALLON]);	// 몬스터-물풍선 충돌
	CCollisionMgr::CollisionMonsterStem(m_listObj[OBJID::MONSTER], m_listObj[OBJID::STEM]);			// 몬스터-물줄기 충돌
	CCollisionMgr::CollisionBallonBlock(m_listObj[OBJID::BALLON], m_listObj[OBJID::BLOCK]);		// 물풍선-블럭 충돌
	CCollisionMgr::CollisionDart(m_listObj[OBJID::DART], m_listObj[OBJID::BLOCK]);				// 다트-블럭 충돌
	CCollisionMgr::CollisionDart(m_listObj[OBJID::DART], m_listObj[OBJID::BALLON]);				// 다트-물풍선 충돌
	CCollisionMgr::CollisionItemBlock(m_listObj[OBJID::ITEM], m_listObj[OBJID::BLOCK]);			// 아이템-블럭 충돌
	//CCollisionMgr::CollisionStemBlock(m_listObj[OBJID::STEM], m_listObj[OBJID::BLOCK]);		// 물줄기-블럭 충돌


	CCollisionMgr::CollisionPlayerBoss(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BOSS]);			// 플레이어, 보스 충돌
	CCollisionMgr::CollisionBossMap(m_listObj[OBJID::BOSS]);										// 보스, 게임맵 충돌
	CCollisionMgr::CollisionBossBlock(m_listObj[OBJID::BOSS], m_listObj[OBJID::BLOCK]);				// 보스, 블럭 충돌
	CCollisionMgr::CollisionBossStem(m_listObj[OBJID::BOSS], m_listObj[OBJID::STEM]);				// 보스 물줄기 충돌
	CCollisionMgr::CollisionBossBallon(m_listObj[OBJID::BOSS], m_listObj[OBJID::BALLON]);				// 보스, 물풍선 충돌
	CCollisionMgr::CollisionItemBoss(m_listObj[OBJID::ITEM], m_listObj[OBJID::BOSS]);				// 아이템, 보스 충돌

	if (CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID() && true == m_bStartActing 
		|| CSceneMgr::SCENEID::SCENE_STAGE2 == CSceneMgr::Get_Instance()->Get_SceneID() && true == m_bStartActing
		|| CSceneMgr::SCENEID::SCENE_STAGE3 == CSceneMgr::Get_Instance()->Get_SceneID() && true == m_bStartActing
		|| CSceneMgr::SCENEID::SCENE_EDIT == CSceneMgr::Get_Instance()->Get_SceneID() && true == m_bStartActing)
	{
		int i = 1;
		for (auto& pBlock : m_listObj[OBJID::BLOCK])
		{
			SCAST<CBlock*>(pBlock)->Set_ActingCreate(i*10+300);
			i++;
		}
		m_bStartActing = false;
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if(OBJ_LIVE == pObj->Get_Dead())
				pObj->Render(hDC);
			if (m_listObj[i].empty())
				break;
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			SAFE_DELETE(pObj)
		}
		m_listObj[i].clear();
	}
}

void CObjMgr::DeleteID(OBJID::ID _eID)
{
	for(auto& pObj : m_listObj[_eID])
	{
		SAFE_DELETE(pObj);
	}
	m_listObj[_eID].clear();
}
