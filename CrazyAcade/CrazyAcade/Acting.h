#pragma once
#include "Obj.h"
class CActing :
	public CObj
{
public:
	CActing();
	virtual ~CActing();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

