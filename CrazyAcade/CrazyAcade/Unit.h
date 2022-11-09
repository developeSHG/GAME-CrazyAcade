#pragma once
#include "Obj.h"
class CUnit :
	public CObj
{
public:
	CUnit();
	virtual ~CUnit();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() abstract;
	virtual int Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void Render(HDC hDC) abstract;
	virtual void Release() abstract;

public:
	virtual CObj* Create_Ballon() { return 0; }			// 물풍선 생성함수
	virtual void AISystem() {}

public:
	const bool& Get_ActingCreate() const { return m_bActingCreate; }
	const float& Get_Speed()const { return m_fSpeed; }
	const bool& Get_BallonOn() const { return m_bBallonOn; }
	const bool& Get_BubbleState() const { return m_bBubbleState; }
	const bool& Get_PushState() const { return m_bPushState; }

public:
	void Set_ZeroSize() { m_tInfo.fcx = 0; m_tInfo.fcy = 0; }
	void Set_Speed(const float& _fSpeed) { m_fSpeed = _fSpeed; }
	void Set_PlusSpeed(const float& _fSpeed) { m_fSpeed += _fSpeed; }
	void Set_BallonOnState(const bool& _bState) { m_bBallonOn = _bState; }
	void Set_BubbleState(const bool& _bState) { m_bBubbleState = _bState; }
	void Set_PushState(const bool& _bState) { m_bPushState = _bState; }
	void Set_ActingCreate(const bool& _bState) { m_bActingCreate = _bState; }


protected:
	DWORD m_dwGameStartTime;		// 게임스타트 후 진행할수있음
	float m_fSpeed;
	bool m_bBallonOn;			// 물풍선 생성 후 위에 위치해있는지 체크할 데이터
	bool m_bBubbleState;		// 버블상태인지 체크할 데이터 , 또는 물줄기를 맞을건지 체크
	bool m_bPushState;			// 밀수있는건지 또 미는지 체크할 데이터
	DWORD m_bCreateTime;
	bool m_bActingCreate;
};

