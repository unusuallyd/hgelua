#pragma once

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <hge.h>
#include <hgesprite.h>
#include <lua.hpp>
#include <map>
#include <windows.h>

// macro
#define NULL_INT -1
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 24


// typedef
typedef std::map<int, DWORD> ResMap;
typedef std::map<int, const char* > StrMap;
typedef std::map<int, int> IntMap;

// header file
#include "util.h"
#include "TexManager.h"
#include "SoundManager.h"
#include "HpBar.h"
#include "Predator.h"
#include "2Dfloat.h"
#include "cn\\GfxFont.h"





