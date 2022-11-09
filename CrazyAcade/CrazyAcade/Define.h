#pragma once

#define WINCX 800				// 클라이언트 창 가로크기
#define WINCY 600				// 클라이언트 창 세로크기

#define MAP_X 600				// 게임 창 가로크기
#define MAP_Y 520				// 게임 창 세로크기
#define POINT_X 20				// 0 X좌표에서 떨어진 지점
#define POINT_Y 40				// 0 Y좌표에서 떨어진 지점

#define SAFE_DELETE(p) if(p) { delete p; p=nullptr; }

#define Thousand 1000
#define GAME_START_TIME 2 * Thousand

// Update함수의 Return 값
#define OBJ_LIVE 0
#define OBJ_DEAD 1

#define SCENE_ACTIVE_FALSE 0
#define SCENE_ACTIVE_TRUE 1

#define MAP_MAX_HEIGHT 13		// 블럭 최대 높이값
#define MAP_MAX_WIDTH 15		// 블럭 최대 가로값

#define BASIC_SPEED 10			// 기본 스피드
#define MAXIMUM_SPEED 15		// 최대 스피드

#define TILE_NUM_Y 13			// 타일 Y 갯수
#define TILE_NUM_X 15			// 타일 X 갯수

#define TILE2_NUM_Y 13			// 타일 Y 갯수
#define TILE2_NUM_X 50			// 타일 X 갯수

#define TILE_SIZE_X 40			// 타일 x사이즈
#define TILE_SIZE_Y 40			// 타일 y사이즈

#define BLOCK_SIZE_X 40			// 블럭 x사이즈
#define BLOCK_SIZE_Y 47			// 블럭 y사이즈

#define EDIT_TILE 12			// 에디터 타일,블럭 종류

#define GRAVITY_POWER 1


#define DECLARE_SINGLETON(Class)		\
private:								\
	Class();							\
	~Class();							\
public:									\
static Class* Get_Instance()			\
{										\
	if (nullptr == m_pInstance)			\
		m_pInstance = new Class;		\
										\
	return m_pInstance;					\
}										\
static void Destroy_Instance()			\
{										\
	if (m_pInstance)					\
	{									\
		delete m_pInstance;				\
		m_pInstance = nullptr;			\
	}									\
}										\
private:								\
	static Class* m_pInstance;		

#define IMPLEMENT_SINGLETON(Class)		\
Class* Class::m_pInstance = nullptr;