#pragma once
#include "Unit.h"
class CPlayer :
	public CUnit
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SceneChange();
	virtual void LateInit();
	virtual CObj* Create_Ballon();				// 물풍선 생성함수

public:
	const bool& Get_LeapCheck() const { return m_bLeapCheck; }
	const bool& Get_ShieldState() const { return m_bShieldState; }
	const bool& Get_BoardState() const { return m_bBoardState; }
	const bool& Get_OnItemState() const { return m_bOnItem; }
	const size_t& Get_BallonPower() const { return m_uBallonPower; }
	const bool& Get_InvinState() const { return m_bInvinState; }
	const bool& Get_DieState() const { return m_bDieState; }
	const ITEM::PROPERTY& Get_OnItem() const { return m_eOnItem; }
	const PLAYER::STATE& Get_PlayerState() const { return m_eNextState; }

public:
	void Set_HideState(float _x, float _y) { m_bHideState = true; m_tInfo.fx = _x; m_tInfo.fy = _y; }

public:
	void WalkActive();
	void ThrowActive(CObj* _pBallon);
	void BlockLeapCheck();
	void LeapActive(int _iBlockNum);
	void Set_Item();
	void Use_Item();
	void Board_Item();
	void Set_BoardState(bool _bState) { m_bBoardState = _bState; }
	void Set_OnItemState(bool _bState) { m_bOnItem = _bState; }
	void Summons_Item();

private:
	DWORD m_dwBallonCoolTime;
	size_t m_iBallonMaxNum;			// 물풍선 최대갯수
	DWORD m_dwBubbleTime;			// 버블타임 지속시간
	bool m_bHideState;
	DWORD m_dwHideTime;
	bool m_bLeapActive;
	bool m_bLeapCheck;
	float m_fLeapActivePos;
	int iLeapBlockNum;					// 뛰어넘어갈 블럭갯수
	float m_fJumpPower;
	TCHAR* m_pBallonFrame;
	TCHAR* m_pItemFrame;
	size_t m_uBallonPower;
	bool m_bThrowState;
	bool m_bShieldState;
	bool m_bNeedleState;
	bool m_bTimerState;
	size_t m_iTimerBallonNum;
	bool m_bBananaState;
	bool m_bWingState;
	int m_iOrder;
	bool m_bBoardState;
	float m_fBoardJumpPower;
	ITEM::PROPERTY m_eOnItem;
	bool m_bOnItem;
	int m_iSummonsItem;
	DWORD m_dwInvinTime;
	bool m_bInvinState;
	bool m_bDieState;

private:
	PLAYER::STATE m_eCurState;
	PLAYER::STATE m_eNextState;
};

