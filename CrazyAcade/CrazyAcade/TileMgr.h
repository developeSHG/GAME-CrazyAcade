#pragma once
class CTileMgr
{
DECLARE_SINGLETON(CTileMgr)

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	const vector<CObj*> Get_Tile() const { return m_vecTile; }

public:
	void PickTile_DrawID(POINT& pt, int iDrawID);
	void PickTile_Option(POINT& pt, int iOption);
	void SaveData(int _iStage);
	bool LoadData(int _iStage);
	void Set_Frame(TCHAR* _pFrame) { m_pFrame = _pFrame; }
	void Set_KindsPlus() { ++iKindsNum; }
	void Set_KindsMinus() { --iKindsNum; }
	void Set_Scene(int _iScene) { m_iScene = _iScene; }
	void Game_Finish();

public:
	enum TILES { TILE, NONE, BASIC, PUSH, STONE, HIDE, THORN, TELEPORT1, TELEPORT2, TELEPORT3, TELEPORT4, DESTROY };

private:
	vector<CObj*> m_vecTile;
	vector<CObj*> m_vecBlock;
	TCHAR* m_pFrame;
	int iKindsNum;
	int m_iScene;
};

