#pragma once

typedef struct tagInfo
{
	// ��ǥ. 
	float fx;
	float fy;
	// ũ�� 
	float fcx;
	float fcy;
}INFO;

typedef struct tagFrame
{
	int iFrameStart; // �̹��� ������
	int iFrameEnd;  // �̹��� ���� 
	int iFrameScene; // �̹��� �ൿ. 
	DWORD dwFrameSpeed; // ��� �ӵ� 
	DWORD dwFrameTime; // ��� �ð�. 
	int iFrameStartReset;

}FRAME;