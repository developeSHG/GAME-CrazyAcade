#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Logo.h"
#include "Login.h"
#include "MyMenu.h"
#include "Loading.h"
#include "Stage0.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "MyEdit.h"
#include "TileMgr.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID, int _Stage)
{
	// State 패턴 
	//FSM을 기반으로 하는 객체의 상태를 표현 
	/*
	유한 상태 기계는 자신이 취할수 있는 유한한 갯수를 가진다.
	그리고 그중 반드시 하나만 취한다.
	현재 상태는 특정 조건이 되면 다른 상태로 변할 수 있다.

	FSM과 상속과 다형성으로 더욱 확장한 디자인 패턴
	*/
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::SCENE_LOGIN:
			m_pScene = new CLogin;
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case CSceneMgr::SCENE_LOADING:
			m_pScene = new CLoading(_Stage);
			break;
		case CSceneMgr::SCENE_STAGE0:
			m_pScene = new CStage0;
			break;
		case CSceneMgr::SCENE_STAGE1:
			m_pScene = new CStage1;
			break;
		case CSceneMgr::SCENE_STAGE2:
			m_pScene = new CStage2;
			break;
		case CSceneMgr::SCENE_STAGE3:
			m_pScene = new CStage3;
			break;
		case CSceneMgr::SCENE_EDIT:
			m_pScene = new CMyEdit;
			break;
		case CSceneMgr::SCENE_END:
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}