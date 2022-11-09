#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
public:
	CLoading();
	CLoading(int _iStage) { m_iStageActive = _iStage; }
	virtual ~CLoading();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_tTime;
	DWORD m_tLoadingTime;
	float m_fX;
	int m_iStageActive;
};

