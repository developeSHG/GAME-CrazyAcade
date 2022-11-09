#pragma once
#include "Unit.h"
class CBlock :
	public CUnit
{
public:
	CBlock();
	virtual ~CBlock();

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
	const BLOCK::PROPERTY& Get_Property() const { return m_eProperty; }
	const bool& Get_TeleState() const { return m_bTeleState; }

public:
	void Set_ActingCreate(int _iTime) { m_iTime = _iTime; }
	void Set_BlockPro(const BLOCK::PROPERTY& _eProperty) { m_eProperty = _eProperty;}
	void Set_TeleState(const bool& _bState) { m_bTeleState = _bState; }
	void Set_PushDir(BLOCK::DIR _eDir);
	void Create_Acting();
	void Create_Item();

public:
	const int Get_DrawID() const { return m_iDrawID; }
	const int Get_Option() const { return m_iOption; }

public:
	void Set_DrawID(int iDrawID) { m_iDrawID += iDrawID; }
	void Set_Option(int iOption) { m_iOption = iOption; }
	void Set_Scene(int _iScene) { m_iScene = _iScene; }
	void Set_StemCreate() { m_bStemCreate = true;  }

public:
	CObj* Create_Stem(size_t _uPower, STEM::DIR _eDir);

public:
	void Set_Load1();
	void Set_Load2();
	void Set_Load3();

private:
	int m_iTime;
	BLOCK::PROPERTY m_eProperty;
	bool m_bTeleState;			// 텔레포트를 탔는지 안탔는지, 확인해서 다시 초기화할 데이터
	int m_iDrawID;
	int m_iOption;
	HDC hMemDC;
	static int m_iRan;
	int m_iScene;
	bool m_bStemCreate;
	size_t m_uPower;
	bool m_eStemDeleteDir[BALLON::DIR::DOWN + 1];		// 블럭충돌 삭제방향
	DWORD m_dwCreateTime;
};

