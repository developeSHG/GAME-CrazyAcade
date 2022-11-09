#pragma once
#include "Obj.h"
class CStem :
	public CObj
{
public:
	CStem();
	virtual ~CStem();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void LateInit();

public:
	const bool& Get_BossStem() { return m_bBossStem; }

public:
	void SceneChane();
	void Set_Dir(STEM::DIR _eDir) { m_eDir = _eDir; }
	void Set_BossStem() { m_bBossStem = true; }


private:
	STEM::DIR m_eDir;
	DWORD m_dwCreateTime;
	bool m_bBossStem;

};

