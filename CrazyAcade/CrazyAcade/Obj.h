#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() abstract;
	virtual int Update() abstract;
	virtual void LateUpdate() abstract;
	virtual void Render(HDC hDC) abstract;
	virtual void Release() abstract;

public:
	virtual void LateInit();

public:
	void UpdateRect();


public:
	const RECT* Get_Rect()const { return &m_tRect; }
	INFO& Get_Info() { return m_tInfo; }
	const bool& Get_Dead()const { return m_bIsDead; }
	const RECT& Get_TileRC() const { return m_tTile_Rc; }
	const TCHAR* Get_FrameKey() const { return m_pFrameKey; }

public:
	void Set_Pos(float _x, float _y)
	{
		m_tInfo.fx = _x;
		m_tInfo.fy = _y;
	}
	void Set_Size(float _cx, float _cy)
	{
		m_tInfo.fcx = _cx;
		m_tInfo.fcy = _cy;
	}
	void Set_Dead() { m_bIsDead = OBJ_DEAD; }

public:
	void Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void Set_FrameEndScene(int _iFrameEnd) { m_tFrame.iFrameEnd = _iFrameEnd;}


public:
	void MoveFrame();
	void MoveFrame(int _StartFrame);
	void TileRC_Check();
	
protected:
	INFO m_tInfo;
	RECT m_tRect;
	FRAME m_tFrame;
	POINT m_tFactSize;

	TCHAR* m_pFrameKey;
	POINT m_tFrameSize;
	POINT m_tFramePos;
	POINT m_tFrameStart;
	RECT m_tTile_Rc;				// 내가 어느 타일에 있는지 체크할 데이터;

protected:
	bool m_bIsDead;
	bool m_bIsInit;				// 한번만 실행시킬지 결정할 데이터

};

