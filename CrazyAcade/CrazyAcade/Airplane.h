#pragma once
#include "Unit.h"
class CAirplane :
	public CUnit
{
public:
	CAirplane();
	virtual ~CAirplane();

	// CUnit��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Create_Item();

private:
	DWORD m_dwTime;
	int m_iCreateItemTime;
};

