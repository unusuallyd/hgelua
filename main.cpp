#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <hge.h>
#include <hgesprite.h>
#include <lua.hpp>
#include <windows.h>

#include "lhge.h"
//#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
//#pragma warning(disable:4800)//warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)

HGE * hge;
lua_State * global_L;

int main(int argn, char* argv[])
{
	global_L = luaL_newstate();
	luaL_openlibs(global_L);
	luaopen_hge(global_L);
	hge = hgeCreate(HGE_VERSION);
	if (!hge){ 
		printf("hgeCreate failed!\n");
		return 1;
	}

	//printf("load script file: %s\n", argv[1]);
	if (luaL_dofile(global_L, argv[1]))
	{
		printf("script error: %s\n", lua_tostring(global_L, -1));
		return 1;
	}
	hge->System_Shutdown();
	hge->Release();
	return 0;
}

