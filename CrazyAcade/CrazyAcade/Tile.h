#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const int Get_DrawID() const { return m_iDrawID; }
	const int Get_Option() const { return m_iOption; }

public:
	void Set_DrawID(int iDrawID) { m_iDrawID += iDrawID; }
	void Set_Option(int iOption) { m_iOption = 0; }
	void Set_Scene(int _iScene) { m_iScene = _iScene; }

public:
	void Create_Acting();

private:
	int m_iDrawID;
	int m_iOption;
	HDC hMemDC;
	int m_iScene;
	bool m_bFinish;
};

