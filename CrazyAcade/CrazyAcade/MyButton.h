#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const bool& Get_Active() const { return m_bActive; }
	void Set_Active(const bool _bActive) { m_bActive = _bActive; }

private:
	bool m_bActive;
	int m_iDrawID;
};

