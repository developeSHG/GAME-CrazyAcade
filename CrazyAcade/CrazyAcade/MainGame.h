#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void Render_Fps(HDC _hDC);

public:
	void ImageLoad_Logo();
	void ImageLoad_Menu();
	void ImageLoad_Loading();


private:
	HDC m_hDC;
};

