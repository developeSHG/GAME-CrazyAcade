#include "stdafx.h"
#include "MainGame.h"

#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "Mouse.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWND);

	// 흰 배경화면 (백버퍼)
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/BackGround.bmp", L"BackGround");

	// 로고
	ImageLoad_Logo();

	// 로그인
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Login.bmp", L"Back_Login");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Button/Start.bmp", L"Button_Start");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Button/Edit.bmp", L"Button_Edit");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Button/Exit.bmp", L"Button_Exit");

	// 매뉴
	ImageLoad_Menu();

	// 로딩
	ImageLoad_Loading();

	// 게임 스테이지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Stage1.bmp", L"Back_Stage1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Stage2.bmp", L"Back_Stage2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Stage3.bmp", L"Back_Stage3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Game_Start.bmp", L"Game_Start");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/PlayerPos.bmp", L"PlayerPos");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Clear.bmp", L"Clear");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Lose.bmp", L"Lose");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Finish.bmp", L"Finish");

	// 스테이지0 Flopy
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Flopy/Tile.bmp", L"Flopy_Tile");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Flopy/Block.bmp", L"Flopy_Block");

	// 스테이지1 Camp
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Basic.bmp", L"Basic");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Push.bmp", L"Push");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Stone.bmp", L"Stone");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Hide.bmp", L"Hide");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Thorn.bmp", L"Thorn");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Camp/Dunks.bmp", L"Dunks");

	// 스테이지2 Factory
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Factory/Tile.bmp", L"Tile2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Factory/Basic.bmp", L"Basic2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Factory/Push.bmp", L"Push2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Factory/Stone.bmp", L"Stone2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Factory/With.bmp", L"With2");

	// 스테이지3 Mine
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Tile.bmp", L"Tile3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Basic.bmp", L"Basic3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Push.bmp", L"Push3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Stone.bmp", L"Stone3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Thorn.bmp", L"Thorn3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Mine/Teleport.bmp", L"Teleport");

	// 블럭연기
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Game/Acting.bmp", L"Acting");

	// 플레이어 
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Walk_Front.bmp", L"Walk_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Walk_Left.bmp", L"Walk_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Walk_Right.bmp", L"Walk_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Walk_Back.bmp", L"Walk_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Ba_Walk_Front.bmp", L"Ba_Walk_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Ba_Walk_Left.bmp", L"Ba_Walk_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Ba_Walk_Right.bmp", L"Ba_Walk_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Ba_Walk_Back.bmp", L"Ba_Walk_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Wing_Walk_Front.bmp", L"Wing_Walk_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Wing_Walk_Left.bmp", L"Wing_Walk_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Wing_Walk_Right.bmp", L"Wing_Walk_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Wing_Walk_Back.bmp", L"Wing_Walk_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Bubble1.bmp", L"Bubble1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Bubble2.bmp", L"Bubble2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Bubble3.bmp", L"Bubble3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Bubble_Needle.bmp", L"Bubble_Needle");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Win.bmp", L"Win");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Die1.bmp", L"Die1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Die2.bmp", L"Die2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Tank_Front.bmp", L"Tank_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Tank_Left.bmp", L"Tank_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Tank_Right.bmp", L"Tank_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Tank_Back.bmp", L"Tank_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Space_Front.bmp", L"Space_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Space_Left.bmp", L"Space_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Space_Right.bmp", L"Space_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Space_Back.bmp", L"Space_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Owl_Front.bmp", L"Owl_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Owl_Left.bmp", L"Owl_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Owl_Right.bmp", L"Owl_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Owl_Back.bmp", L"Owl_Back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Turtle_Front.bmp", L"Turtle_Front");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Turtle_Left.bmp", L"Turtle_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Turtle_Right.bmp", L"Turtle_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Player/Turtle_Back.bmp", L"Turtle_Back");

	// 물풍선 이미지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Ballon/Ballon1.bmp", L"Ballon1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Ballon/Ballon2.bmp", L"Ballon2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Ballon/Ballon3.bmp", L"Ballon3");

	// 물줄기 이미지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/Center.bmp", L"Stem_Center");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/Left.bmp", L"Stem_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/Right.bmp", L"Stem_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/Up.bmp", L"Stem_Up");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/Down.bmp", L"Stem_Down");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/LeftLast.bmp", L"Stem_LeftLast");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/RightLast.bmp", L"Stem_RightLast");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/UpLast.bmp", L"Stem_UpLast");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Stem/DownLast.bmp", L"Stem_DownLast");

	// 몬스터 이미지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Boss.bmp", L"Stage1_Boss");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Stage1_Monster1.bmp", L"Stage1_Monster1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Stage1_Monster2.bmp", L"Stage1_Monster2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Stage1_Monster3.bmp", L"Stage1_Monster3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Stage1_Monster4.bmp", L"Stage1_Monster4");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage1/Stage1_Monster5.bmp", L"Stage1_Monster5");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage2/Stage2_Monster1.bmp", L"Stage2_Monster1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage2/Stage2_Monster2.bmp", L"Stage2_Monster2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage2/Stage2_Monster3.bmp", L"Stage2_Monster3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage2/Stage2_Monster4.bmp", L"Stage2_Monster4");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Monster/Stage3/Boss.bmp", L"Boss");

		
	// 아이템 이미지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Water.bmp", L"Water");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Turtle.bmp", L"Turtle");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Timer.bmp", L"Timer");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/TimerBallon.bmp", L"TimerBallon");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Space.bmp", L"Space");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Shoes.bmp", L"Shoes");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Shield.bmp", L"Shield");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/ShieldAni.bmp", L"ShieldAni");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Roller.bmp", L"Roller");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Power.bmp", L"Power");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Owl.bmp", L"Owl");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Needle.bmp", L"Needle");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Glove.bmp", L"Glove");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Gas.bmp", L"Gas");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Tank.bmp", L"Tank");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Dart.bmp", L"Dart");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/DartShot_Left.bmp", L"DartShot_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/DartShot_Right.bmp", L"DartShot_Right");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/DartShot_Down.bmp", L"DartShot_Down");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/DartShot_Up.bmp", L"DartShot_Up");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Fly.bmp", L"Fly");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Devil.bmp", L"Devil");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Banana.bmp", L"Banana");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/BlackBallon.bmp", L"BlackBallon");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Item/Wing.bmp", L"Wing");

	// 비행기 이미지
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Airplane/Airplane_Left.bmp", L"Airplane_Left");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Airplane/Airplane_Right.bmp", L"Airplane_Right");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CSoundMgr::Get_Instance()->Initialize();
	// 씬 체인지
	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);
	//CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
	//CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
	
	// 마우스 생성
	CObjMgr::Get_Instance()->AddObject(OBJID::MOUSE, CAbstractFactory<CMouse>::Create());
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
}

void CMainGame::Render()
{
	HDC hMemDC = CBmpMgr::Get_Instance()->FindImage(L"BackGround");
	HDC hBack = CBmpMgr::Get_Instance()->FindImage(L"BackGround");
	BitBlt(hBack, // 복사받을 DC
		0,// 그림 출력할 위치 X 
		0,// 그림 출력할 위치 Y
		WINCX,// 그림 크기 X
		WINCY,// 그림 크기 Y
		hMemDC,// 복사할 DC 
		0,// 그림에서 출력할 X 좌표 
		0,// 그림에서 출력할 Y 좌표
		SRCCOPY);
	CSceneMgr::Get_Instance()->Render(hBack);
	//Render_Fps(hBack);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWND, m_hDC);
	CKeyMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
}

void CMainGame::Render_Fps(HDC _hDC)
{
	static UINT oldTime = GetTickCount();
	static float FrameCount;
	static float Fps = 0;

	int nowTime, delTime;
	TCHAR szFps[12];
	memset(szFps, 0, sizeof(szFps));

	nowTime = GetTickCount();
	delTime = nowTime - oldTime;
	++FrameCount;

	if (delTime > 999)
	{
		FrameCount = (FrameCount * 1000) / delTime;
		oldTime = nowTime;
		Fps = FrameCount;
		FrameCount = 0;
	}
	
	TCHAR info[32] = L"";
	swprintf_s(info, L"%f", Fps);
	TextOut(_hDC, 0, 0, info, lstrlen(info));
}

void CMainGame::ImageLoad_Logo()
{
	// 로고
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/1.bmp", L"Logo1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/2.bmp", L"Logo7");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/3.bmp", L"Logo8");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/4.bmp", L"Logo9");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/5.bmp", L"Logo10");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/6.bmp", L"Logo11");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/7.bmp", L"Logo12");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/8.bmp", L"Logo13");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/9.bmp", L"Logo14");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/10.bmp", L"Logo15");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/11.bmp", L"Logo16");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/12.bmp", L"Logo17");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/13.bmp", L"Logo18");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/14.bmp", L"Logo19");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/15.bmp", L"Logo20");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/16.bmp", L"Logo21");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/17.bmp", L"Logo22");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/18.bmp", L"Logo23");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/19.bmp", L"Logo24");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/User/20.bmp", L"Logo25");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/11.bmp", L"LogoN1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/12.bmp", L"LogoN2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/13.bmp", L"LogoN3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/14.bmp", L"LogoN4");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/15.bmp", L"LogoN5");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/16.bmp", L"LogoN6");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/17.bmp", L"LogoN7");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/18.bmp", L"LogoN8");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/19.bmp", L"LogoN9");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/20.bmp", L"LogoN10");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/21.bmp", L"LogoN11");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/22.bmp", L"LogoN12");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/23.bmp", L"LogoN13");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/24.bmp", L"LogoN14");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/25.bmp", L"LogoN15");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/26.bmp", L"LogoN16");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/27.bmp", L"LogoN17");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/28.bmp", L"LogoN18");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/29.bmp", L"LogoN19");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/30.bmp", L"LogoN20");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/31.bmp", L"LogoN21");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/32.bmp", L"LogoN22");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/33.bmp", L"LogoN23");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/34.bmp", L"LogoN24");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/35.bmp", L"LogoN25");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/36.bmp", L"LogoN26");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/37.bmp", L"LogoN27");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/38.bmp", L"LogoN28");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/39.bmp", L"LogoN29");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/40.bmp", L"LogoN30");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/41.bmp", L"LogoN31");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/42.bmp", L"LogoN32");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/43.bmp", L"LogoN33");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/44.bmp", L"LogoN34");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/45.bmp", L"LogoN35");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/46.bmp", L"LogoN36");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/47.bmp", L"LogoN37");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/48.bmp", L"LogoN38");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/49.bmp", L"LogoN39");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/50.bmp", L"LogoN40");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/51.bmp", L"LogoN41");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/52.bmp", L"LogoN42");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/53.bmp", L"LogoN43");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/54.bmp", L"LogoN44");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/55.bmp", L"LogoN45");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/56.bmp", L"LogoN46");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/57.bmp", L"LogoN47");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/58.bmp", L"LogoN48");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/59.bmp", L"LogoN49");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/60.bmp", L"LogoN50");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/61.bmp", L"LogoN51");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/62.bmp", L"LogoN52");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/63.bmp", L"LogoN53");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/64.bmp", L"LogoN54");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/65.bmp", L"LogoN55");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/66.bmp", L"LogoN56");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/67.bmp", L"LogoN57");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/68.bmp", L"LogoN58");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/69.bmp", L"LogoN59");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/70.bmp", L"LogoN60");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/71.bmp", L"LogoN61");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/72.bmp", L"LogoN62");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/73.bmp", L"LogoN63");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/74.bmp", L"LogoN64");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/75.bmp", L"LogoN65");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/76.bmp", L"LogoN66");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/77.bmp", L"LogoN67");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/78.bmp", L"LogoN68");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/79.bmp", L"LogoN69");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/80.bmp", L"LogoN70");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/81.bmp", L"LogoN71");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/82.bmp", L"LogoN72");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Nexon/83.bmp", L"LogoN73");
}

void CMainGame::ImageLoad_Menu()
{
	// 메뉴 UI 1
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Menu.bmp", L"Back_Menu");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Dao.bmp", L"Dao_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Dao_Banner.bmp", L"Dao_Banner");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Digini.bmp", L"Digini_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Digini_Banner.bmp", L"Digini_Banner");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Bazzi.bmp", L"Bazzi_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Bazzi_Banner.bmp", L"Bazzi_Banner");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Uni.bmp", L"Uni_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Uni_Banner.bmp", L"Uni_Banner");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Button/Start_Button.bmp", L"Start_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Random.bmp", L"Random_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Dao_Select.bmp", L"Dao_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Digini_Select.bmp", L"Digini_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Bazzi_Select.bmp", L"Bazzi_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Bazzi_Select2.bmp", L"Bazzi_Select2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Uni_Select.bmp", L"Uni_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Color_Check.bmp", L"Color_Check");

	// 메뉴 UI 2
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Button.bmp", L"Map_Button");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Select.bmp", L"Map_Select");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Select1.bmp", L"Map_Select1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Select2.bmp", L"Map_Select2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Select3.bmp", L"Map_Select3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Select4.bmp", L"Map_Select4");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_SelectButton1.bmp", L"Map_SelectButton1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_SelectButton2.bmp", L"Map_SelectButton2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Camp.bmp", L"Map_Camp");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Map_Factory.bmp", L"Map_Factory");
}

void CMainGame::ImageLoad_Loading()
{
	// 로딩
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/BackGround/Back_Loding.bmp", L"Back_Loading");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading1.bmp", L"UI_Loading1");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading2.bmp", L"UI_Loading2");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading3.bmp", L"UI_Loading3");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading4.bmp", L"UI_Loading4");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading5.bmp", L"UI_Loading5");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/UI_Loading6.bmp", L"UI_Loading6");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/Loading.bmp", L"Loading");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/UI/LoadingPoint.bmp", L"LoadingPoint");
}
