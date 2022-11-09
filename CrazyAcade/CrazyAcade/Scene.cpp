#include "stdafx.h"
#include "Scene.h"

#include "Airplane.h"
#include "ObjMgr.h"

CScene::CScene()
{
	m_dwAirplaneCoolTime = GetTickCount();
}


CScene::~CScene()
{
	
}

void CScene::CreateAirplane()
{
	if (m_dwAirplaneCoolTime + 8500 < GetTickCount())
	{
		CObj* pObj = CAbstractFactory<CAirplane>::Create();
		CObjMgr::Get_Instance()->AddObject(OBJID::AIRPLANE, pObj);
		m_dwAirplaneCoolTime = GetTickCount();
	}
}
