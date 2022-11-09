#pragma once
#include "Obj.h"
class CMyCharacter :
	public CObj
{
public:
	CMyCharacter();
	virtual ~CMyCharacter();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

