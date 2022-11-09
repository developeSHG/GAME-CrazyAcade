#pragma once

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void CObjMgr::AddObject(OBJID::ID eID, CObj * pObj)
	{
		if(pObj)
			m_listObj[eID].emplace_back(pObj);
	}

public:
	CObj* Get_Player() const { return m_listObj[OBJID::PLAYER].front(); }
	list<CObj*>* Get_Obj(OBJID::ID _eID) { return &(m_listObj[_eID]); }
	const size_t Get_BallonAmount() const { return m_listObj[OBJID::BALLON].size(); }
	void Set_StartActing(bool _Acting) { m_bStartActing = _Acting; }

public:
	void DeleteID(OBJID::ID _eID);

private:
	static CObjMgr* m_pInstance;
	list<CObj*> m_listObj[OBJID::END];
	bool m_bStartActing;
	
};