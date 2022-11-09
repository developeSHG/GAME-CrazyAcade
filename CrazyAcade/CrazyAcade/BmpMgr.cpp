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
	//[]() {};  ���ٽ� ���� �˷��� ���� ������ �˷��ָ� �����̴� �Ƹ� ���������� ? ��ġ? �������״� 

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
		MessageBox(g_hWND, L"�̹� �׸��� ����.", L"CBmpMgr::InsertImage()", MB_OK);
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
