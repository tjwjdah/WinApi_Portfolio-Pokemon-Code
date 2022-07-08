﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <algorithm>

// Library
#pragma comment(lib, "msimg32")


// Header
#include <assert.h>
#include <vector>
#include <list>
#include <map>
#include <math.h>
#include <string>
#include <commdlg.h>

#include <time.h>

// sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


using std::vector;
using std::list;
using std::map;
using std::string;
using std::wstring;

using std::make_pair;


#include "define.h"
#include "struct.h"
#include "func.h"

#include "Objects.h"




