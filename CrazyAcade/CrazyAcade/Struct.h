#pragma once

typedef struct tagInfo
{
	// 좌표. 
	float fx;
	float fy;
	// 크기 
	float fcx;
	float fcy;
}INFO;

typedef struct tagFrame
{
	int iFrameStart; // 이미지 시작점
	int iFrameEnd;  // 이미지 끝점 
	int iFrameScene; // 이미지 행동. 
	DWORD dwFrameSpeed; // 재생 속도 
	DWORD dwFrameTime; // 재생 시간. 
	int iFrameStartReset;

}FRAME;