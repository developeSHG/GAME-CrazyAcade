#pragma once

class CMyBitmap;

class CBmpMgr
{
DECLARE_SINGLETON(CBmpMgr)

public:
	HDC FindImage(const TCHAR* pImageKey);

public:
	void InsertImage(const TCHAR* pFilePath, const TCHAR* pImageKey);
	void Release();

private:
	map<const TCHAR*, CMyBitmap*> m_mapBmp;
};

