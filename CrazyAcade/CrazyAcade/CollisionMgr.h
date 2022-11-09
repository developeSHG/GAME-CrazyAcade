#pragma once
class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionRectEX(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc);

public:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);

public:
	static void CollisionPlayerZeroMap(list<CObj*>& rDst);							// 튜토리얼 맵충돌
	static void CollisionBallonZeroMap(list<CObj*>& rDst);							// 튜토리얼 맵충돌
	static void CollisionStemZeroMap(list<CObj*>& rDst);							// 튜토리얼 맵충돌
	static void CollisionMap(list<CObj*>& rDst);									// 게임맵 충돌
	static void CollisionPlayerMap(list<CObj*>& rDst);								// 플레이어-게임맵 충돌
	static void CollisionBallonMap(list<CObj*>& rDst);								// 물풍선, 게임맵 충돌
	static void CollisionMonsterMap(list<CObj*>& rDst);								// 몬스터, 게임맵 충돌
	static void CollisionPlayerMonster(list<CObj*>& rDst, list<CObj*>& rSrc);		// 플레이어, 몬스터 충돌
	static void CollisionPlayerBallon(list<CObj*>& rDst, list<CObj*>& rSrc);		// 플레이어, 물풍선 충돌
	static void CollisionPlayerBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// 플레이어, 블럭 충돌
	static void CollisionMonsterBlock(list<CObj*>& rDst, list<CObj*>& rSrc);		// 몬스터, 블럭 충돌
	static void CollisionMonsterBallon(list<CObj*>& rDst, list<CObj*>& rSrc);		// 몬스터, 물풍선 충돌
	static void CollisionBallonBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// 물풍선, 블럭 충돌
	static void CollisionStemBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// 물줄기, 블럭 충돌
	static void CollisionPlayerStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// 플레이어 , 물줄기 충돌
	static void CollisionStem(list<CObj*>& rDst, list<CObj*>& rSrc);				// 플레이어 등등 물줄기 충돌
	static void CollisionMonsterStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// 몬스터 물줄기 충돌
	static void CollisionItemStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// 아이템, 물줄기 충돌
	static void CollisionDart(list<CObj*>& rDst, list<CObj*>& rSrc);				// 다트, 물줄기 충돌
	static void CollisionItemBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// 아이템, 블럭 충돌

	static void CollisionPlayerBoss(list<CObj*>& rDst, list<CObj*>& rSrc);			// 플레이어, 보스 충돌
	static void CollisionBossMap(list<CObj*>& rDst);								// 보스, 게임맵 충돌
	static void CollisionBossBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// 보스, 블럭 충돌
	static void CollisionBossStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// 보스 물줄기 충돌
	static void CollisionBossBallon(list<CObj*>& rDst, list<CObj*>& rSrc);			// 보스, 물풍선 충돌
	static void CollisionItemBoss(list<CObj*>& rDst, list<CObj*>& rSrc);			// 아이템, 보스 충돌

public:
	static void Set_Blocked(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY); // 대상, 블럭 충돌
};

