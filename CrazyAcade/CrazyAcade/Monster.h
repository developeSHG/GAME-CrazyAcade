#pragma once
#include "Unit.h"
class CMonster :
	public CUnit
{
public:
	CMonster();
	virtual ~CMonster();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();
	virtual void AISystem();					

public:
	const bool& Get_HideState() const { return m_bHideState; }
	const bool& Get_ChetkiState() const { return m_bChetkiState; }

public:
	void SceneChange();
	void Set_HideStatePos(float _x, float _y) { m_bHideState = true; m_tInfo.fx = _x; m_tInfo.fy = _y; m_dwHideTime = GetTickCount(); }
	void Set_HideState(bool _bState) {m_bHideState = _bState;}
	void Set_FrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_AiState() { m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE); }
	void Set_DieState() { m_eNextState = MONSTER::DIE; }
	void Set_Stage(int _iStage) { m_iStage = _iStage; }

private:
	DWORD m_dwAiTime;
	DWORD m_dwBubbleTime;			// 버블타임 지속시간
	bool m_bHideState;
	DWORD m_dwHideTime;
	bool m_bChetkiState;
	POINT m_tChetkiPoint;
	DWORD m_dwDeadTime;
	int m_iStage;

private:
	MONSTER::STATE m_eCurState;
	MONSTER::STATE m_eNextState;
};

