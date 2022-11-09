#pragma once
#include "Obj.h"
class CLoadingUI :
	public CObj
{
public:
	CLoadingUI();
	virtual ~CLoadingUI();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_Timer(DWORD _utime) { m_dwCoolTime = _utime; };
	void Set_Point(LONG _x, LONG _y) { m_tPoint.x = _x; m_tPoint.y = _y; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }

private:
	DWORD m_dwTime;
	DWORD m_dwCoolTime;
	POINT m_tPoint;
	float m_fSpeed;
};

