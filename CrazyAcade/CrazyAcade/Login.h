#pragma once
#include "Scene.h"
class CLogin :
	public CScene
{
public:
	CLogin();
	virtual ~CLogin();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

