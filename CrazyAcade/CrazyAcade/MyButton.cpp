#include "stdafx.h"
#include "MyButton.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "MyBanner.h"


CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.fcx = 60.f;
	m_tInfo.fcy = 78.f;
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_bIsDead = OBJ_LIVE;
	m_pFrameKey = nullptr;

	// 버튼 고유변수
	m_bActive = true;
	m_iDrawID = 0;
}

int CMyButton::Update()
{
	return 0;
}

void CMyButton::LateUpdate()
{
	CObj::UpdateRect();

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (PtInRect(&m_tRect, pt) && CSceneMgr::Get_Instance()->SCENEID::SCENE_LOGIN == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			// 로그인 (시작
			if (!lstrcmp(m_pFrameKey, L"Button_Start"))
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				return;
			}
			else if (!lstrcmp(m_pFrameKey, L"Button_Edit"))
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
				return;
			}
			else if (!lstrcmp(m_pFrameKey, L"Button_Exit"))
			{
				DestroyWindow(g_hWND);
			}
			// 로그인 (끝)
			CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);

		}
		m_iDrawID = 1;
	}
	else if(CSceneMgr::Get_Instance()->SCENEID::SCENE_LOGIN == CSceneMgr::Get_Instance()->Get_SceneID())
		m_iDrawID = 0;

	if (PtInRect(&m_tRect, pt) && CSceneMgr::Get_Instance()->SCENEID::SCENE_MENU == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		if (!lstrcmp(m_pFrameKey, L"BlueBox1") && true == m_bActive)
		{
			for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
			{
				if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey())
					pObj->Set_FrameKey(L"Map_Select1");
			}
		}
		if (!lstrcmp(m_pFrameKey, L"BlueBox2") && true == m_bActive)
		{
			for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
			{
				if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey())
					pObj->Set_FrameKey(L"Map_Select3");
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// 메뉴 (시작)
			if (!lstrcmp(m_pFrameKey, L"Dao_Button"))
			{
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->front()->Set_FrameKey(L"Dao_Select");
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->back()->Set_FrameKey(L"Dao_Banner");
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI))
					if (L"Color_Check" == pObj->Get_FrameKey())
						pObj->Set_Pos(693.f, 293.f);
			}
			else if (!lstrcmp(m_pFrameKey, L"Digini_Button"))
			{
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->front()->Set_FrameKey(L"Digini_Select");
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->back()->Set_FrameKey(L"Digini_Banner");
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI))
					if (L"Color_Check" == pObj->Get_FrameKey())
						pObj->Set_Pos(730.f, 293.f);
			}
			else if (!lstrcmp(m_pFrameKey, L"Bazzi_Button") || !lstrcmp(m_pFrameKey, L"Red"))
			{
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->front()->Set_FrameKey(L"Bazzi_Select");
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->back()->Set_FrameKey(L"Bazzi_Banner");
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI))
					if (L"Color_Check" == pObj->Get_FrameKey())
						pObj->Set_Pos(515.f, 293.f);
			}
			else if (!lstrcmp(m_pFrameKey, L"Uni_Button"))
			{CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->front()->Set_FrameKey(L"Uni_Select");
				
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->back()->Set_FrameKey(L"Uni_Banner");
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI))
					if (L"Color_Check" == pObj->Get_FrameKey())
						pObj->Set_Pos(550.f, 293.f);
			}
			else if (!lstrcmp(m_pFrameKey, L"Black"))
			{
				CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI)->front()->Set_FrameKey(L"Bazzi_Select2");

				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI))
					if (L"Color_Check" == pObj->Get_FrameKey())
						pObj->Set_Pos(765.f, 293.f);
			}
			else if (!lstrcmp(m_pFrameKey, L"Start_Button"))
			{
				
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Camp" == pObj->Get_FrameKey() && true == SCAST<CMyBanner*>(pObj)->Get_Active())
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
						CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOADING, 1);
						return;
					}
					else if (L"Map_Factory" == pObj->Get_FrameKey() && true == SCAST<CMyBanner*>(pObj)->Get_Active())
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
						CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOADING, 2);
						return;
					}
					else if(L"Map_Factory" != pObj->Get_FrameKey() && L"Map_Camp" != pObj->Get_FrameKey())
					{
						CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
						CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOADING, 3);
						return;
					}
				}
			}
			else if (!lstrcmp(m_pFrameKey, L"Map_Button"))
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey()
						|| L"Map_Select2" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey() || L"Map_Select4" == pObj->Get_FrameKey()
						|| L"Map_SelectButton1" == pObj->Get_FrameKey() || L"Map_SelectButton2" == pObj->Get_FrameKey()
						|| L"BlueBox1" == pObj->Get_FrameKey() || L"BlueBox2" == pObj->Get_FrameKey())
						SCAST<CMyBanner*>(pObj)->Set_Active(true);
				}
			}
			else if (!lstrcmp(m_pFrameKey, L"Map_SelectButton1"))
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Select2" == pObj->Get_FrameKey() && true == SCAST<CMyBanner*>(pObj)->Get_Active())
					{
						for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
						{
							if (L"Map_Camp" == pObj->Get_FrameKey())
								SCAST<CMyBanner*>(pObj)->Set_Active(true);
							if (L"Map_Factory" == pObj->Get_FrameKey())
								SCAST<CMyBanner*>(pObj)->Set_Active(false);
						}
					}
					else if (L"Map_Select4" == pObj->Get_FrameKey() && true == SCAST<CMyBanner*>(pObj)->Get_Active())
					{
						for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
						{
							if (L"Map_Factory" == pObj->Get_FrameKey())
								SCAST<CMyBanner*>(pObj)->Set_Active(true);
							if (L"Map_Camp" == pObj->Get_FrameKey())
								SCAST<CMyBanner*>(pObj)->Set_Active(false);
						}
					}
					if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey()
						|| L"Map_Select2" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey() || L"Map_Select4" == pObj->Get_FrameKey()
						|| L"Map_SelectButton1" == pObj->Get_FrameKey() || L"Map_SelectButton2" == pObj->Get_FrameKey()
						|| L"BlueBox1" == pObj->Get_FrameKey() || L"BlueBox2" == pObj->Get_FrameKey())
						SCAST<CMyBanner*>(pObj)->Set_Active(false);


					if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey()
						|| L"Map_Select2" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey() || L"Map_Select4" == pObj->Get_FrameKey())
						pObj->Set_FrameKey(L"Map_Select");
				}
			}
			else if (!lstrcmp(m_pFrameKey, L"Map_SelectButton2"))
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey() 
						|| L"Map_Select2" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey() || L"Map_Select4" == pObj->Get_FrameKey()
						|| L"Map_SelectButton1" == pObj->Get_FrameKey() || L"Map_SelectButton2" == pObj->Get_FrameKey()
						|| L"BlueBox1" == pObj->Get_FrameKey() || L"BlueBox2" == pObj->Get_FrameKey())
						SCAST<CMyBanner*>(pObj)->Set_Active(false);

					if (L"Map_Select" == pObj->Get_FrameKey() || L"Map_Select1" == pObj->Get_FrameKey()
						|| L"Map_Select2" == pObj->Get_FrameKey() || L"Map_Select3" == pObj->Get_FrameKey() || L"Map_Select4" == pObj->Get_FrameKey())
						pObj->Set_FrameKey(L"Map_Select");
				}
			}
			else if (!lstrcmp(m_pFrameKey, L"BlueBox1") && true == m_bActive)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Select1" == pObj->Get_FrameKey())
						pObj->Set_FrameKey(L"Map_Select2");
				}
			}
			else if (!lstrcmp(m_pFrameKey, L"BlueBox2") && true == m_bActive)
			{
				CSoundMgr::Get_Instance()->MyPlaySound(L"Button.wav", CSoundMgr::UI);
				for (auto& pObj : *CObjMgr::Get_Instance()->Get_Obj(OBJID::MENU_UI2))
				{
					if (L"Map_Select3" == pObj->Get_FrameKey())
						pObj->Set_FrameKey(L"Map_Select4");
				}
			}
			// 메뉴 (끝)

		}
		m_iDrawID = 0;
	}
	else if (CSceneMgr::Get_Instance()->SCENEID::SCENE_MENU == CSceneMgr::Get_Instance()->Get_SceneID())
		m_iDrawID = 1;

}

void CMyButton::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC MemDC = CBmpMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (true == m_bActive)
	{
		if (L"Button_Start" == m_pFrameKey || L"Button_Exit" == m_pFrameKey)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left), int(m_tRect.top),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				MemDC,
				int(m_tInfo.fcx * m_iDrawID), 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(107, 108, 110));
		}
		else if (L"Map_SelectButton1" == m_pFrameKey || L"Map_SelectButton2" == m_pFrameKey)
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left), int(m_tRect.top),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				MemDC,
				int(m_tInfo.fcx * m_iDrawID), 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(253, 255, 255));
		}
		else if(L"BlueBox1" == m_pFrameKey || L"BlueBox2" == m_pFrameKey)
		{
			//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		}
		else
		{
			GdiTransparentBlt(hDC,
				int(m_tRect.left), int(m_tRect.top),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				MemDC,
				int(m_tInfo.fcx * m_iDrawID), 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(255, 255, 255));
		}
	}
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMyButton::Release()
{
}
