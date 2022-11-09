#include "stdafx.h"
#include "BmpMgr.h"

#include "MyBitmap.h"

IMPLEMENT_SINGLETON(CBmpMgr)

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

HDC CBmpMgr::FindImage(const TCHAR* pImageKey)
{
	//[]() {};  람다식 내일 알려줌 내일 오전에 알려주면 나영이는 아마 못들을끄야 ? 그치? 지각할테니 

	map<const TCHAR*, CMyBitmap*>::iterator iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rObj)
	{
		return !lstrcmp(pImageKey, rObj.first);
	});

	if (m_mapBmp.end() == iter)
	{
		return nullptr;
	}
	return iter->second->Get_MemDC();
}

void CBmpMgr::InsertImage(const TCHAR * pFilePath, const TCHAR * pImageKey)
{
	map<const TCHAR*, CMyBitmap*>::iterator iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), CMyStrCmp(pImageKey));

	if (iter == m_mapBmp.end())
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->LoadBmp(pFilePath);

		m_mapBmp.emplace(pImageKey, pBmp);
	}
	else
	{
		MessageBox(g_hWND, L"이미 그림이 있음.", L"CBmpMgr::InsertImage()", MB_OK);
	}
}

void CBmpMgr::Release()
{
	for (auto& pPair : m_mapBmp)
	{
		if (pPair.second)
		{
			delete pPair.second;
			pPair.second = nullptr;
		}
	}
	m_mapBmp.clear();
}
