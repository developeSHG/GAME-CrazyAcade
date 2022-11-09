#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::LoadBmp(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWND);

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWND, hDC);

	m_hBmp = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBmp);
	DeleteDC(m_hMemDC);
}
