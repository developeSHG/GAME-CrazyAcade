#pragma once
#include "Unit.h"
class CDart :
	public CUnit
{
public:
	CDart();
	virtual ~CDart();

	// CUnit을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_Dir(PLAYER::STATE _eDir) { m_eDir = _eDir; }

private:
	PLAYER::STATE m_eDir;
};

