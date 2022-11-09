#pragma once
#include "Scene.h"
class CStage0 :
	public CScene
{
public:
	CStage0();
	virtual ~CStage0();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

