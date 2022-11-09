#pragma once

#define WINCX 800				// Ŭ���̾�Ʈ â ����ũ��
#define WINCY 600				// Ŭ���̾�Ʈ â ����ũ��

#define MAP_X 600				// ���� â ����ũ��
#define MAP_Y 520				// ���� â ����ũ��
#define POINT_X 20				// 0 X��ǥ���� ������ ����
#define POINT_Y 40				// 0 Y��ǥ���� ������ ����

#define SAFE_DELETE(p) if(p) { delete p; p=nullptr; }

#define Thousand 1000
#define GAME_START_TIME 2 * Thousand

// Update�Լ��� Return ��
#define OBJ_LIVE 0
#define OBJ_DEAD 1

#define SCENE_ACTIVE_FALSE 0
#define SCENE_ACTIVE_TRUE 1

#define MAP_MAX_HEIGHT 13		// �� �ִ� ���̰�
#define MAP_MAX_WIDTH 15		// �� �ִ� ���ΰ�

#define BASIC_SPEED 10			// �⺻ ���ǵ�
#define MAXIMUM_SPEED 15		// �ִ� ���ǵ�

#define TILE_NUM_Y 13			// Ÿ�� Y ����
#define TILE_NUM_X 15			// Ÿ�� X ����

#define TILE2_NUM_Y 13			// Ÿ�� Y ����
#define TILE2_NUM_X 50			// Ÿ�� X ����

#define TILE_SIZE_X 40			// Ÿ�� x������
#define TILE_SIZE_Y 40			// Ÿ�� y������

#define BLOCK_SIZE_X 40			// �� x������
#define BLOCK_SIZE_Y 47			// �� y������

#define EDIT_TILE 12			// ������ Ÿ��,�� ����

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