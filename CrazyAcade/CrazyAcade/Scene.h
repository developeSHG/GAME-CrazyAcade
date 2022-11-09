#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() abstract;
	virtual int Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void Render(HDC hDC) abstract;
	virtual void Release() abstract;

public:
	void CreateAirplane();

protected:
	DWORD m_dwAirplaneCoolTime;
	int m_iAirplane_Dir;
	int m_iCreateMonster = 1;
};

