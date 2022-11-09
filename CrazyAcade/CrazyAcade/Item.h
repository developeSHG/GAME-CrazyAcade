#pragma once
#include "Unit.h"
class CItem :
	public CUnit
{
public:
	CItem();
	virtual ~CItem();

public:
	// CUnit을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const ITEM::PROPERTY& Get_Property() const { return m_eProperty; }
	const bool& Get_CreateCheck() const { return m_bCreateCheck; }

public:
	void Set_Property(ITEM::PROPERTY _eValue) { m_eProperty = _eValue; }
	void Set_CreateCheck() { m_bCreateCheck = true; }

private:
	ITEM::PROPERTY m_eProperty;
	bool m_bInPlace;
	float m_fPos;
	DWORD m_dwCreateTime;
	bool m_bCreateCheck;
};

