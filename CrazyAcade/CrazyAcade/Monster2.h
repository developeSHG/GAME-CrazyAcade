#pragma once
#include "Unit.h"
class CMonster2 :
	public CUnit
{
public:
	CMonster2();
	virtual ~CMonster2();

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

public:
	void KindsCheck();
	void SceneChange();
	void Set_HideState(float _x, float _y) { m_bHideState = true; m_tInfo.fx = _x; m_tInfo.fy = _y; m_dwHideTime = GetTickCount(); }
	void Set_FrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_AiState() { m_eNextState = MONSTER::STATE(rand() % MONSTER::BUBBLE); }

private:
	DWORD m_dwAiTime;
	DWORD m_dwBubbleTime;			// 버블타임 지속시간
	bool m_bHideState;
	DWORD m_dwHideTime;

private:
	MONSTER::STATE m_eCurState;
	MONSTER::STATE m_eNextState;
};

