#pragma once
#include "Unit.h"
class CBoss :
	public CUnit
{
public:
	CBoss();
	virtual ~CBoss();

	// CUnit을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();
	virtual void AISystem();

public:
	const bool& Get_ShadowState() { return m_bShadowState; }
	const bool& Get_RealBubbleState() { return m_bRealBubbleState; }

public:
	void Set_AiState() { m_eNextState = BOSS::STATE(rand() % BOSS::BEING); }
	void Set_ShadowMove() { m_iShadowMove = rand() % BOSS::BEING; }
	void Set_DieState() { m_bDieState = true; }
	void Set_Hp() { CObj::LateInit(); }
	void Set_LateInit() { m_bIsInit = false; }

public:
	CObj* BossCreateBallon();
	void CreateMonster();
	void SceneChange();
	

private:
	DWORD m_dwAiTime;
	DWORD m_dwBallonTime;
	int iBallonTime;
	size_t uBallonPower;
	DWORD m_dwBubbleTime;
	DWORD m_dwDeadTime;
	DWORD m_dwCreateMonsterTime;
	DWORD m_dwShadowTime;
	DWORD m_dwAngerShowTime;
	DWORD m_dwAngerTime;
	DWORD m_dwDieTime;
	bool m_bShadowState;
	bool m_bRealBubbleState;
	bool m_bAngerState;
	bool m_bDieState;
	int m_iShadowMove;
	float m_fHp;
	bool m_bHpState;

private:
	BOSS::STATE m_eCurState;
	BOSS::STATE m_eNextState;
};

