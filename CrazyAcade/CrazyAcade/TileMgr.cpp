#include "stdafx.h"
#include "TileMgr.h"

#include "Block.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)
CTileMgr::CTileMgr()
	: iKindsNum(TILE)
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILE_NUM_Y; ++i)
	{
		for (int j = 0; j < TILE_NUM_X; ++j)
		{
			float fx = (j * TILE_SIZE_X) + (TILE_SIZE_X * 0.5f);
			float fy = (i * TILE_SIZE_Y) + (TILE_SIZE_Y * 0.5f);

			CObj* pObj = CAbstractFactory<CTile>::Create_Tile(fx + POINT_X, fy + POINT_Y);
			pObj->Initialize();
			m_vecTile.emplace_back(pObj);
		}
	}

	for (int i = 0; i < TILE_NUM_Y; ++i)
	{
		for (int j = 0; j < TILE_NUM_X; ++j)
		{
			float fx = (j * TILE_SIZE_X) + (TILE_SIZE_X * 0.5f);
			float fy = (i * TILE_SIZE_Y) + (TILE_SIZE_Y * 0.5f);

			CObj* pObj = CAbstractFactory<CBlock>::Create(fx + POINT_X, fy + POINT_Y);
			SCAST<CBlock*>(pObj)->Set_Option(BLOCK::TILE);
			m_vecBlock.emplace_back(pObj);
		}
	}	
}

void CTileMgr::Update()
{
	for (auto& Tile : m_vecTile)
	{
		Tile->Update();
	}
	//if (CSceneMgr::SCENEID::SCENE_EDIT == CSceneMgr::Get_Instance()->Get_SceneID())
	//{
		for (auto& Block : m_vecBlock)
		{
			Block->Update();
		}
	//}
}

void CTileMgr::LateUpdate()
{
	for (auto& Tile : m_vecTile)
	{
		Tile->LateUpdate();
	}
	for (auto& Block : m_vecBlock)
	{
		Block->LateUpdate();
	}
}

void CTileMgr::Render(HDC hDC)
{
	for (auto& pTile : m_vecTile)
	{
	 	pTile->Render(hDC);
	}
	//if (CSceneMgr::SCENEID::SCENE_EDIT == CSceneMgr::Get_Instance()->Get_SceneID())
	//{
		for (auto& Block : m_vecBlock)
		{
			Block->Render(hDC);
		}

		switch (m_iScene)
		{
		case 1:
			{
				TCHAR* buffer[80] = {
					L"TILE", L"BASIC", L"PUSH", L"STONE", L"HIDE", L"THORN", L"DUNKS", L"TELEPORT1", L"TELEPORT2", L"TELEPORT3", L"TELEPORT4", L"12: DESTROY"
				};
				TCHAR Num[20];
				TextOut(hDC, 660, 150, L"현재 설정값 : ", 8);
				wsprintf(Num, TEXT("%d"), iKindsNum);
				TextOut(hDC, 760, 150, Num, lstrlen(Num));

				for (int i = 0; i <= EDIT_TILE; ++i)
				{
					wsprintf(Num, TEXT("%d"), i);
					TextOut(hDC, 660, 170 + (i * 20), Num, lstrlen(Num));
					TextOut(hDC, 690, 170 + (i * 20), buffer[i], lstrlen(buffer[i]));
				}

				if (iKindsNum > EDIT_TILE)
				{
					iKindsNum = 0;
				}
			}
			break;
		case 2:
			{
				TCHAR* buffer[80] = {
					L"TILE", L"BASIC", L"PUSH", L"STONE", L"11: WITH", L"12: DESTROY"
				};
				TCHAR Num[20];
				TextOut(hDC, 660, 150, L"현재 설정값 : ", 8);
				wsprintf(Num, TEXT("%d"), iKindsNum);
				TextOut(hDC, 760, 150, Num, lstrlen(Num));

				for (int i = 0; i < 6; ++i)
				{
					wsprintf(Num, TEXT("%d"), i);
					TextOut(hDC, 660, 170 + (i * 20), Num, lstrlen(Num));
					TextOut(hDC, 690, 170 + (i * 20), buffer[i], lstrlen(buffer[i]));
				}

				if (iKindsNum > EDIT_TILE)
				{
					iKindsNum = 0;
				}
			}
			break;
		case 3:
		{
			TCHAR* buffer[80] = {
				L"TILE", L"BASIC", L"PUSH", L"STONE", L"5: THORN", L"7: TELEPORT1", L"8: TELEPORT2", L"9: TELEPORT3", L"10: TELEPORT4", L"12: DESTROY"
			};
			TCHAR Num[20];
			TextOut(hDC, 660, 150, L"현재 설정값 : ", 8);
			wsprintf(Num, TEXT("%d"), iKindsNum);
			TextOut(hDC, 760, 150, Num, lstrlen(Num));

			for (int i = 0; i < 10; ++i)
			{
				wsprintf(Num, TEXT("%d"), i);
				TextOut(hDC, 660, 170 + (i * 20), Num, lstrlen(Num));
				TextOut(hDC, 690, 170 + (i * 20), buffer[i], lstrlen(buffer[i]));
			}

			if (iKindsNum > EDIT_TILE)
			{
				iKindsNum = 0;
			}
		}
		break;
		}
	//}
}

void CTileMgr::Release()
{
	for (auto& pTile : m_vecTile)
	{
		SAFE_DELETE(pTile);
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	for (auto& pBlock : m_vecBlock)
	{
		SAFE_DELETE(pBlock);
	/*	if(BLOCK::TILE == SCAST<CBlock*>(pBlock)->Get_Option())
			SAFE_DELETE(pBlock);*/
	}
	m_vecBlock.clear();
	m_vecBlock.shrink_to_fit();
}

void CTileMgr::PickTile_DrawID(POINT & pt, int iDrawID)
{
	int x = pt.x / TILE_SIZE_X;
	int y = pt.y / TILE_SIZE_Y;
	int iIndex = x + (TILE_NUM_X * y);

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
	{
		return;
	}

	if (TILE == iKindsNum)
	{
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	}
	else
	{
		dynamic_cast<CBlock*>(m_vecBlock[iIndex])->Set_DrawID(iDrawID);
		//dynamic_cast<CBlock*>(m_vecBlock[iIndex])->Set_Option(iKindsNum);
		dynamic_cast<CBlock*>(m_vecBlock[iIndex])->Set_ActingCreate(true);
	}
}

void CTileMgr::PickTile_Option(POINT & pt, int iOption)
{
	int x = pt.x / TILE_SIZE_X;
	int y = pt.y / TILE_SIZE_Y;
	int iIndex = x + (TILE_NUM_X * y);

	if (TILE == iKindsNum)
	{
		//dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	}
	else
	{
		dynamic_cast<CBlock*>(m_vecBlock[iIndex])->Set_Option(iKindsNum);
		dynamic_cast<CBlock*>(m_vecBlock[iIndex])->Set_ActingCreate(true);
	}
}

void CTileMgr::SaveData(int _iStage)
{
	HANDLE hFile = nullptr;
	switch (_iStage)
	{
	case 1:
		hFile = CreateFile(L"../Data/Stage1.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, nullptr);
		break;
	case 2:
		hFile = CreateFile(L"../Data/Stage2.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, nullptr);
		break;
	case 3:
		hFile = CreateFile(L"../Data/Stage3.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, nullptr);
		break;
	}

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWND, L"Save NO", L"CTileMgr::SaveData()", MB_OK);
		return;
	}
	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		iDrawID = SCAST<CTile*>(pTile)->Get_DrawID();
		iOption = SCAST<CTile*>(pTile)->Get_Option();

		/*pTile->Get_Info().fx += WINCX;*/

		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);
	}
	//WriteFile(hFile, 0, 0, &dwByte, nullptr);
	for (auto& pBlock : m_vecBlock)
	{
	/*	if (BLOCK::NONE == SCAST<CBlock*>(pBlock)->Get_Option())
		{*/
			iDrawID = SCAST<CBlock*>(pBlock)->Get_DrawID();
			iOption = SCAST<CBlock*>(pBlock)->Get_Option();

			WriteFile(hFile, &pBlock->Get_Info(), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);
		//}
	}
	CloseHandle(hFile);
	MessageBox(g_hWND, L"Save OK", L"CTileMgr::SaveData()", MB_OK);
}

bool CTileMgr::LoadData(int _iStage)
{
	HANDLE hFile = nullptr;
	switch (_iStage)
	{
	case 0:
		hFile = CreateFile(L"../Data/Stage0.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case 1:
		hFile = CreateFile(L"../Data/Stage1.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case 2:
		hFile = CreateFile(L"../Data/Stage2.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case 3:
		hFile = CreateFile(L"../Data/Stage3.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	}

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWND, L"Load NO", L"CTileMgr::SaveData()", MB_OK);
		return false;
	}

	int iDrawID = 0, iOption = 0;
	INFO tInfo{};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		CObj* pObj = CAbstractFactory<CTile>::Create_Tile(tInfo.fx, tInfo.fy);
		
		SCAST<CTile*>(pObj)->Set_DrawID(iDrawID);
		SCAST<CTile*>(pObj)->Set_Option(iOption);
		SCAST<CTile*>(pObj)->Set_Scene(_iStage);
		pObj->Initialize();

		m_vecTile.emplace_back(pObj);

		if (m_vecTile.size() == 195 && 1 == _iStage)
			break;
		else if (m_vecTile.size() == 195 && 2 == _iStage)
			break;
		else if (m_vecTile.size() == 195 && 3 == _iStage)
			break;
	}

	if (0 == _iStage)
	{
		CloseHandle(hFile);
		return true;
	}

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		CObj* pObj = CAbstractFactory<CBlock>::Create(tInfo.fx, tInfo.fy);
		dynamic_cast<CBlock*>(pObj)->Set_DrawID(iDrawID);
		SCAST<CBlock*>(pObj)->Set_Scene(_iStage);

		/*  Edit Mode  */
		//dynamic_cast<CBlock*>(pObj)->Set_Option(BLOCK::TILE);
		/*  Game Mode  */
		dynamic_cast<CBlock*>(pObj)->Set_Option(iOption);
		
		/*  Edit Mode  */
		//m_vecBlock.emplace_back(pObj);
		/*  Game Mode  */
		if (BLOCK::TILE != iOption && CSceneMgr::SCENEID::SCENE_EDIT != CSceneMgr::Get_Instance()->Get_SceneID())
			CObjMgr::Get_Instance()->AddObject(OBJID::BLOCK, pObj);
	}

	if (2 != _iStage)
	{
		CloseHandle(hFile);
		return true;
	}

	//switch (_iStage)
	//{
	//case 2:
	//	hFile = CreateFile(L"../Data/Stage2-1.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	//	break;
	//}
	//if (INVALID_HANDLE_VALUE == hFile)
	//{
	//	MessageBox(g_hWND, L"Load NO", L"CTileMgr::SaveData()", MB_OK);
	//	return false;
	//}
	//iDrawID = 0, iOption = 0;
	//tInfo = {};
	//dwByte = 0;
	//while (true)
	//{
	//	ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
	//	ReadFile(hFile, &iDrawID, sizeof(iDrawID), &dwByte, nullptr);
	//	ReadFile(hFile, &iOption, sizeof(iOption), &dwByte, nullptr);

	//	if (0 == dwByte)
	//	{
	//		break;
	//	}
	//	for (int i = 1; i < 5; ++i)
	//	{
	//		CObj* pObj = CAbstractFactory<CTile>::Create_Tile(tInfo.fx + i*WINCX, tInfo.fy);
	//		SCAST<CTile*>(pObj)->Set_DrawID(iDrawID);
	//		SCAST<CTile*>(pObj)->Set_Option(iOption);

	//		m_vecTile.emplace_back(pObj);
	//	}


	//	if (m_vecTile.size() == 195 && 1 == _iStage)
	//		break;
	//	else if (m_vecTile.size() == 195 && 2 == _iStage)
	//		break;
	//}

	CloseHandle(hFile);
	//MessageBox(g_hWND, L"Load OK", L"CTileMgr::SaveData()", MB_OK);
	return true;
}

void CTileMgr::Game_Finish()
{
	for (auto& pTile : m_vecTile)
	{
		SCAST<CTile*>(pTile)->Create_Acting();
	}
}
