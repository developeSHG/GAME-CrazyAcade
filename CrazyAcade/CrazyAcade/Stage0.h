#pragma once
#include "Scene.h"
class CStage0 :
	public CScene
{
public:
	CStage0();
	virtual ~CStage0();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

