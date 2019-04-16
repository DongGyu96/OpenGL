// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <gl/glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Vfw.h>
#include <iostream>
#include <string.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

#define PI 3.141592f / 180.f

// fmod
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")
using namespace FMOD;


// 음악 번호 soundnum

#define LogoBgm 0
#define GameBgm 1
#define BoostS  2
#define GUN 3
#define METEOR 4