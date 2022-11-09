#pragma once
class CMapMgr
{
private:
	CMapMgr();
	~CMapMgr();

public:
	static CMapMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMapMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();


private:
	static CMapMgr* m_pInstance;
};

