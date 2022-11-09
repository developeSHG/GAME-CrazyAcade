#pragma once
#include "Unit.h"
class CBallon :
	public CUnit
{
public:
	CBallon();
	virtual ~CBallon();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();

public:
	CObj* Create_Stem(size_t _uPower, STEM::DIR _eDir);
	void Overlap();					// 서로겹칩 충돌방지

public:
	const bool& Get_TeleState() const { return m_bTeleState; }
	const bool& Get_ThrowState() const { return m_bThrowState; }
	const BALLON::DIR& Get_ThrowDir() const { return m_eThrowDir; }
	const bool& Get_DirCheck() const { return m_bDirCheck; }
	const bool& Get_WithState() const { return m_bWithState; }
	const bool& Get_BossBallon() const { return m_bBossBallon; }

public:
	void Set_TeleState(const bool& _bState) { m_bTeleState = _bState; }
	void Set_ThrowDir(const BALLON::DIR& _eDir) { m_eThrowDir = _eDir; CObj::UpdateRect(); m_bThrowState = true; }
	void Set_Power(size_t _uPower) { m_uPower = _uPower; }
	void Set_Timer(bool _bTimer) { m_bTimerState = _bTimer; }
	void Set_TankPush(BALLON::DIR _eDir) { m_eDir = _eDir; }
	void Set_WithState(bool _bState) { m_bWithState = _bState; }
	void Set_BossBallon() { m_bBossBallon = true; }

public:
	void ThrowActive();

private:
	DWORD m_dwCreateTime;
	size_t m_uPower;
	BALLON::DIR m_eDir;								// 밀릴 방향
	bool m_bDirCheck;								// 한번밀리고 더이상 밀리지않게 하기위해 체크할 데이터
	BALLON::DIR m_eThrowDir;						// 던져질 방향
	bool m_bThrowState;
	float m_fThrowOriginY;
	float m_fDistX;
	float fThrowJump;
	bool m_bThrowChange;
	bool m_bTeleState;								// 텔레포트를 탔는지 안탔는지, 확인해서 다시 초기화할 데이터
	bool m_eStemDeleteDir[BALLON::DIR::DOWN+1];		// 블럭충돌 삭제방향
	bool m_bTimerState;
	bool m_bWithState;
	bool m_bBossBallon;

};

