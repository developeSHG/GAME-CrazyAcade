// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// 멀티미디어 재생에 필요한 헤더와 라이브러리를 추가. 
#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

// 사운드 매니저를 사용하기 위해 추가한 해더들. 
#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;
#include <time.h>
#include <crtdbg.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Include.h"
