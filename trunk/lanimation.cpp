#include "lhge.h"


/*-------------------------------------------------------------*/
// Animation
/*-------------------------------------------------------------*/

#define HH2ANIM(anim) (hgeAnimation*)(*anim)

int lhge_newanimation(lua_State *L)
{
	hgeAnimation* anim = new hgeAnimation(
			*toudp(L, 1, TEXTURE),
			luaL_checkinteger(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5),
			luaL_checknumber(L, 6),
			luaL_checknumber(L, 7)
			);
	HHANDLE * udp = newudp(L, ANIMATION);
	*udp = (HHANDLE)anim;
	return 1;
}

static int animation_gc(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	delete anim;
	return 0;
}

static int animation_tostring(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, ANIMATION);
	if (udp == NULL)
		lua_pushliteral(L, "Animation (NULL)");
	else
		lua_pushfstring(L, "Animation (%p)", udp);
	return 1;
}

static int animation_play(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->Play();
	return 0;
}

static int animation_stop(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->Stop();
	return 0;
}

static int animation_resume(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->Resume();
	return 0;
}

static int animation_update(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->Update(luaL_checknumber(L, 2));
	return 0;
}

static int animation_isplaying(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	lua_pushboolean(L, anim->IsPlaying());
	return 1;
}

static int animation_setmode(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->SetMode(luaL_checkinteger(L, 2));
	return 0;
}

static int animation_setspeed(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->SetSpeed(luaL_checknumber(L, 2));
	return 0;
}

static int animation_setframe(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->SetFrame(luaL_checkinteger(L, 2));
	return 0;
}

static int animation_setframes(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	anim->SetFrames(luaL_checkinteger(L, 3));
	return 0;
}

static int animation_getmode(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	lua_pushinteger(L, anim->GetMode());
	return 1;
}

static int animation_getspeed(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	lua_pushnumber(L, anim->GetSpeed());
	return 1;
}

static int animation_getframe(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	lua_pushinteger(L, anim->GetFrame());
	return 1;
}

static int animation_getframes(lua_State *L)
{
	hgeAnimation * anim = HH2ANIM(toudp(L, 1, ANIMATION));
	lua_pushinteger(L, anim->GetFrames());
	return 1;
}

static const luaL_Reg animationlib[] = {
	{"__gc", animation_gc},
	{"__tostring", animation_tostring},
	{"Play", animation_play},
	{"Stop", animation_stop},
	{"Resume", animation_resume},
	{"Update", animation_update},
	{"IsPlaying", animation_isplaying},
	{"SetMode", animation_setmode},
	{"SetSpeed", animation_setspeed},
	{"SetFrame", animation_setframe},
	{"SetFrames", animation_setframes},
	{"GetMode", animation_getmode},
	{"GetSpeed", animation_getspeed},
	{"GetFrame", animation_getframe},
	{"GetFrames", animation_getframes},
	{NULL, NULL}
};

static const ConstValue animationMode[] = {
	{HGEANIM_REV, "HGEANIM_REV"}, // - Reverse the animation
	{HGEANIM_PINGPONG, "HGEANIM_PINGPONG"}, // - Use ping-pong cycle
	{HGEANIM_LOOP, "HGEANIM_LOOP"}, // - Loop the animation
	{NULL, "NULL"}
};

void luaopen_animation(lua_State *L)
{
	lhge_register_const(L, animationMode);
	create_meta(L, ANIMATION, animationlib);
	luaL_getmetatable(L, SPRITE);
	lua_setmetatable(L, -2);
}
