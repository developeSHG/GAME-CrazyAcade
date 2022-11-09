#pragma once
#include "Unit.h"
class CShield :
	public CUnit
{
public:
	CShield();
	virtual ~CShield();

	// CUnit��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const bool& Get_Active() { return m_bActive; }

private:
	DWORD m_dwTime;
	bool m_bActive;
};

