#pragma once
#include "Unit.h"
class CInven :
	public CUnit
{
public:
	CInven();
	virtual ~CInven();

	// CUnit을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const ITEM::PROPERTY& Get_Property() const { return m_eProperty; }
	const int& Get_Order() const { return m_iOrder; }
	const bool& Get_Active() const { return m_bActive; }

public:
	void Set_Property(ITEM::PROPERTY _eProperty) { m_eProperty = _eProperty; }
	void Set_Order(int _iOrder) { m_iOrder = _iOrder; }
	void Set_OrderMius() { --m_iOrder; }
	void Set_Active(bool _bActive) { m_bActive = _bActive; }
	

private:
	ITEM::PROPERTY m_eProperty;
	int m_iOrder;
	bool m_bActive;
};

