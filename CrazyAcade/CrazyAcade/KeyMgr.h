#pragma once

#define VK_MAX 0xff

class CKeyMgr
{
DECLARE_SINGLETON(CKeyMgr)

public:
	bool KeyPressing(int iKey);
	bool KeyDown(int iKey);
	bool KeyUp(int iKey);
	void KeyUpdate();

private:
	bool m_bKeyState[VK_MAX];
};

