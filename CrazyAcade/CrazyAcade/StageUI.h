#pragma once
#include "Obj.h"
class CStageUI :
	public CObj
{
public:
	CStageUI();
	virtual ~CStageUI();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();

private:
	DWORD m_dwGameStartTime;
	DWORD m_dwPosTime;
	bool m_bFade;
	bool m_bFinish;
	bool m_bFinishBmp;
	bool m_bResult;
};

