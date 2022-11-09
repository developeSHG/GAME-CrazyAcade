#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID { SCENE_LOGO, SCENE_LOGIN, SCENE_MENU, SCENE_LOADING, SCENE_STAGE0, SCENE_STAGE1, SCENE_STAGE2,  SCENE_STAGE3, SCENE_EDIT, SCENE_END };

public:
	void SceneChange(SCENEID eSceneID, int _Stage = 0);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	const SCENEID Get_SceneID() const { return m_eCurScene; }

private:
	CScene* m_pScene;
	SCENEID m_eCurScene;
	SCENEID m_eNextScene;
};

