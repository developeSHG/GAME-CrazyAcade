#include "stdafx.h"
#include "MapMgr.h"

CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
}


CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Initialize()
{
}

int CMapMgr::Update()
{
	return 0;
}

void CMapMgr::LateUpdate()
{
}

void CMapMgr::Render(HDC hDC)
{
}

void CMapMgr::Release()
{
}
