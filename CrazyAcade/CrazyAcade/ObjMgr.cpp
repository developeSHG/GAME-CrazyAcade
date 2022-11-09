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
	CCollisionMgr::CollisionPlayerMap(m_listObj[OBJID::PLAYER]);								// �÷��̾�-����â �浹
	CCollisionMgr::CollisionBallonMap(m_listObj[OBJID::BALLON]);								// ��ǳ��-����â �浹
	CCollisionMgr::CollisionMonsterMap(m_listObj[OBJID::MONSTER]);								// ����-����â �浹
	//if (CSceneMgr::SCENEID::SCENE_STAGE1 == CSceneMgr::Get_Instance()->Get_SceneID())
	//{
		CCollisionMgr::CollisionMap(m_listObj[OBJID::BLOCK]);									// ��-����â �浹
	//}
	CCollisionMgr::CollisionMap(m_listObj[OBJID::ITEM]);										// ������-����â �浹
	CCollisionMgr::CollisionPlayerMonster(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);	// �÷��̾�-���� �浹
	CCollisionMgr::CollisionPlayerBallon(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BALLON]);	// �÷��̾�-��ǳ�� �浹
	CCollisionMgr::CollisionPlayerStem(m_listObj[OBJID::PLAYER], m_listObj[OBJID::STEM]);		// �÷��̾�-���ٱ� �浹
	CCollisionMgr::CollisionStem(m_listObj[OBJID::BALLON], m_listObj[OBJID::STEM]);				// ��ǳ��-���ٱ� �浹
	CCollisionMgr::CollisionItemStem(m_listObj[OBJID::ITEM], m_listObj[OBJID::STEM]);			// ������-���ٱ� �浹
	CCollisionMgr::CollisionPlayerBlock(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BLOCK]);		// �÷��̾�-�� �浹
	CCollisionMgr::CollisionMonsterBlock(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BLOCK]);	// ����-�� �浹
	CCollisionMgr::CollisionMonsterBallon(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BALLON]);	// ����-��ǳ�� �浹
	CCollisionMgr::CollisionMonsterStem(m_listObj[OBJID::MONSTER], m_listObj[OBJID::STEM]);			// ����-���ٱ� �浹
	CCollisionMgr::CollisionBallonBlock(m_listObj[OBJID::BALLON], m_listObj[OBJID::BLOCK]);		// ��ǳ��-�� �浹
	CCollisionMgr::CollisionDart(m_listObj[OBJID::DART], m_listObj[OBJID::BLOCK]);				// ��Ʈ-�� �浹
	CCollisionMgr::CollisionDart(m_listObj[OBJID::DART], m_listObj[OBJID::BALLON]);				// ��Ʈ-��ǳ�� �浹
	CCollisionMgr::CollisionItemBlock(m_listObj[OBJID::ITEM], m_listObj[OBJID::BLOCK]);			// ������-�� �浹
	//CCollisionMgr::CollisionStemBlock(m_listObj[OBJID::STEM], m_listObj[OBJID::BLOCK]);		// ���ٱ�-�� �浹


	CCollisionMgr::CollisionPlayerBoss(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BOSS]);			// �÷��̾�, ���� �浹
	CCollisionMgr::CollisionBossMap(m_listObj[OBJID::BOSS]);										// ����, ���Ӹ� �浹
	CCollisionMgr::CollisionBossBlock(m_listObj[OBJID::BOSS], m_listObj[OBJID::BLOCK]);				// ����, �� �浹
	CCollisionMgr::CollisionBossStem(m_listObj[OBJID::BOSS], m_listObj[OBJID::STEM]);				// ���� ���ٱ� �浹
	CCollisionMgr::CollisionBossBallon(m_listObj[OBJID::BOSS], m_listObj[OBJID::BALLON]);				// ����, ��ǳ�� �浹
	CCollisionMgr::CollisionItemBoss(m_listObj[OBJID::ITEM], m_listObj[OBJID::BOSS]);				// ������, ���� �浹

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
