#pragma once




#include <stdio.h>
#include <assert.h>
#include <hge.h>
#include <hgesprite.h>
#include <lua.hpp>
#include <map>
#include <windows.h>
#include "Predator.h"

#define NULL_INT -1
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// typedef
typedef std::map<int, DWORD> ResMap;
typedef std::map<int, const char* > StrMap;
typedef std::map<int, int> IntMap;

#include "util.h"
#include "TexManager.h"
#include "SoundManager.h"
#include "HpBar.h"



#include "cn\\GfxFont.h"





