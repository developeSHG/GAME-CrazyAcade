#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	enum STAGE { STAGE_ONE, STAGE_TWO, STAGE_THREE };
	enum KINDS { TILE, BLOCK };
	enum BLOCK_PROPERTY{ BASIC, PUSH, STONE, HIDE, THORN, TELEPORT1, TELEPORT2, TELEPORT3, TELEPORT4 };

};

