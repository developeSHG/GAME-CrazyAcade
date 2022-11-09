#pragma once
#include "Unit.h"
class CBallon :
	public CUnit
{
public:
	CBallon();
	virtual ~CBallon();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();

public:
	CObj* Create_Stem(size_t _uPower, STEM::DIR _eDir);
	void Overlap();					// ���ΰ�Ĩ �浹����

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
	BALLON::DIR m_eDir;								// �и� ����
	bool m_bDirCheck;								// �ѹ��и��� ���̻� �и����ʰ� �ϱ����� üũ�� ������
	BALLON::DIR m_eThrowDir;						// ������ ����
	bool m_bThrowState;
	float m_fThrowOriginY;
	float m_fDistX;
	float fThrowJump;
	bool m_bThrowChange;
	bool m_bTeleState;								// �ڷ���Ʈ�� ������ ��������, Ȯ���ؼ� �ٽ� �ʱ�ȭ�� ������
	bool m_eStemDeleteDir[BALLON::DIR::DOWN+1];		// ���浹 ��������
	bool m_bTimerState;
	bool m_bWithState;
	bool m_bBossBallon;

};

