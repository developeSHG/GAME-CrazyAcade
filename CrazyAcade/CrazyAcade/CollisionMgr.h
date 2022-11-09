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
	static void CollisionPlayerZeroMap(list<CObj*>& rDst);							// Ʃ�丮�� ���浹
	static void CollisionBallonZeroMap(list<CObj*>& rDst);							// Ʃ�丮�� ���浹
	static void CollisionStemZeroMap(list<CObj*>& rDst);							// Ʃ�丮�� ���浹
	static void CollisionMap(list<CObj*>& rDst);									// ���Ӹ� �浹
	static void CollisionPlayerMap(list<CObj*>& rDst);								// �÷��̾�-���Ӹ� �浹
	static void CollisionBallonMap(list<CObj*>& rDst);								// ��ǳ��, ���Ӹ� �浹
	static void CollisionMonsterMap(list<CObj*>& rDst);								// ����, ���Ӹ� �浹
	static void CollisionPlayerMonster(list<CObj*>& rDst, list<CObj*>& rSrc);		// �÷��̾�, ���� �浹
	static void CollisionPlayerBallon(list<CObj*>& rDst, list<CObj*>& rSrc);		// �÷��̾�, ��ǳ�� �浹
	static void CollisionPlayerBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// �÷��̾�, �� �浹
	static void CollisionMonsterBlock(list<CObj*>& rDst, list<CObj*>& rSrc);		// ����, �� �浹
	static void CollisionMonsterBallon(list<CObj*>& rDst, list<CObj*>& rSrc);		// ����, ��ǳ�� �浹
	static void CollisionBallonBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// ��ǳ��, �� �浹
	static void CollisionStemBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// ���ٱ�, �� �浹
	static void CollisionPlayerStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// �÷��̾� , ���ٱ� �浹
	static void CollisionStem(list<CObj*>& rDst, list<CObj*>& rSrc);				// �÷��̾� ��� ���ٱ� �浹
	static void CollisionMonsterStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// ���� ���ٱ� �浹
	static void CollisionItemStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// ������, ���ٱ� �浹
	static void CollisionDart(list<CObj*>& rDst, list<CObj*>& rSrc);				// ��Ʈ, ���ٱ� �浹
	static void CollisionItemBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// ������, �� �浹

	static void CollisionPlayerBoss(list<CObj*>& rDst, list<CObj*>& rSrc);			// �÷��̾�, ���� �浹
	static void CollisionBossMap(list<CObj*>& rDst);								// ����, ���Ӹ� �浹
	static void CollisionBossBlock(list<CObj*>& rDst, list<CObj*>& rSrc);			// ����, �� �浹
	static void CollisionBossStem(list<CObj*>& rDst, list<CObj*>& rSrc);			// ���� ���ٱ� �浹
	static void CollisionBossBallon(list<CObj*>& rDst, list<CObj*>& rSrc);			// ����, ��ǳ�� �浹
	static void CollisionItemBoss(list<CObj*>& rDst, list<CObj*>& rSrc);			// ������, ���� �浹

public:
	static void Set_Blocked(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY); // ���, �� �浹
};

