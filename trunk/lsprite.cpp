#include "lhge.h"

/*-------------------------------------------------------------*/
// Sprite
/*-------------------------------------------------------------*/

#define HH2SPR(spr) ((hgeSprite*)(*spr))

hgeSprite* ToAORS(lua_State *L, int index)
{
	lua_pushvalue(L, 1);	
	lua_pushstring(L, "__name");
	lua_gettable(L, -2);
	const char* metaname = luaL_checkstring(L, -1);
	lua_pop(L, 2);
	if (strcmp(metaname, SPRITE) == 0)
	{
		return (hgeSprite*)*toudp(L, 1, SPRITE);
	}
	else if (strcmp(metaname, ANIMATION) == 0 )
	{
		return (hgeSprite*)*toudp(L, 1, ANIMATION);
	}
	else
		return NULL;
}

int lhge_newsprite(lua_State *L)
{
	HHANDLE * tex = toudp(L, 1, TEXTURE);
	hgeSprite * spr = new hgeSprite(*tex,
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5)
		);
	HHANDLE * udp = newudp(L, SPRITE);
	*udp = (HHANDLE)spr;
	return 1;
}

static int sprite_gc(lua_State *L)
{
	hgeSprite * spr = HH2SPR(toudp(L, 1, SPRITE));
	delete spr;
	return 0;
}

static int sprite_tostring(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, SPRITE);
	if (udp == NULL)
		lua_pushliteral(L, "Sprite (NULL)");
	else
		lua_pushfstring(L, "Sprite (%p)", udp);
	return 1;
}

static int sprite_render(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	if (lua_isnoneornil(L, 4))
		spr->Render(
				luaL_checknumber(L, 2),
				luaL_checknumber(L, 3)
			);
	else
		spr->RenderEx(
				luaL_checknumber(L, 2),
				luaL_checknumber(L, 3),
				luaL_checknumber(L, 4),
				luaL_optnumber(L, 5, 1.0),
			    luaL_optnumber(L, 6, 0.0)
		);	
	return 0;
}

static int sprite_renderstretch(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->RenderStretch(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5)
		);
	return 0;
}

static int sprite_render4v(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->Render4V(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5),
			luaL_checknumber(L, 6),
			luaL_checknumber(L, 7),
			luaL_checknumber(L, 8),
			luaL_checknumber(L, 9)
			);
	return 0;
}

static int sprite_settexture(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	HHANDLE * tex = toudp(L, 2, TEXTURE);
	spr->SetTexture(*tex);
	return 0;
}

static int sprite_settexturerect(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	bool adjSize = true;
	if (!lua_isnoneornil(L, 6))
		adjSize = lua_toboolean(L, 6);
	spr->SetTextureRect(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5),
			adjSize
		);
	return 0;
}

static int sprite_setcolor(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->SetColor(
			luaL_checkinteger(L, 2),
			luaL_optinteger(L, 3, -1)
			);
	return 0;
}

static int sprite_setz(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->SetZ(
			luaL_checkinteger(L, 2),
			luaL_optinteger(L, 3, -1)
			);
	return 0;
}	

static int sprite_setblendmode(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->SetBlendMode(
			luaL_checkinteger(L, 2)
			);
	return 0;
}

static int sprite_sethotspot(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->SetHotSpot(
			luaL_checkinteger(L, 2),
			luaL_checkinteger(L, 3)
			);
	return 0;
}

static int sprite_setflip(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	spr->SetFlip(
			lua_toboolean(L, 2),
			lua_toboolean(L, 3),
			lua_toboolean(L, 4)
			);
	return 0;
}

static int sprite_gettexture(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	HHANDLE tex = spr->GetTexture();
	HHANDLE * udp = newudp(L, TEXTURE);
	(*udp) = tex;
	return 1;
}

static int sprite_gettexturerect(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	float x, y, w, h;
	spr->GetTextureRect(&x, &y, &w, &h);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pushnumber(L, w);
	lua_pushnumber(L, h);
	return 4;
}

static int sprite_getcolor(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	lua_pushinteger(L, spr->GetColor(luaL_optinteger(L, 2, 0)));
	return 1;
}

static int sprite_getz(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	lua_pushnumber(L, spr->GetZ(luaL_optinteger(L, 2, 0)));
	return 1;
}

static int sprite_getblendmode(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	lua_pushinteger(L, spr->GetBlendMode());
	return 1;
}

static int sprite_gethotspot(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	float x, y;
	spr->GetHotSpot(&x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int sprite_getflip(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	bool bx, by;
	spr->GetFlip(&bx, &by);
	lua_pushboolean(L, bx);
	lua_pushboolean(L, by);
	return 2;
}

static int sprite_getwidth(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	lua_pushnumber(L, spr->GetWidth());
	return 1;
}

static int sprite_getheight(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	lua_pushnumber(L, spr->GetHeight());
	return 1;
}

static int sprite_getboundingbox(lua_State *L)
{
	hgeSprite * spr = ToAORS(L, 1);
	if (lua_gettop(L) == 4) // normal
	{
		hgeRect* rect = spr->GetBoundingBox(
				luaL_checknumber(L, 2),
				luaL_checknumber(L, 3),
				(hgeRect*)(*toudp(L, 4, RECT))
				);
		HHANDLE * udp = newudp(L, RECT);
		*udp = (HHANDLE)rect;
	}
	else
	{
		hgeRect* rect = spr->GetBoundingBoxEx(
				luaL_checknumber(L, 2),
				luaL_checknumber(L, 3),
				luaL_checknumber(L, 4),
				luaL_checknumber(L, 5),
				luaL_checknumber(L, 6),
				(hgeRect*)(*toudp(L, 7, RECT))
				);
		HHANDLE * udp = newudp(L, RECT);
		*udp = (HHANDLE)rect;
	}
	return 1;
}

static const luaL_Reg spritelib[] = {
	{"__gc", sprite_gc},
	{"__tostring", sprite_tostring},
	{"Render", sprite_render},// 	Renders sprite to the screen.
	{"RenderStretch", sprite_renderstretch},// 	Renders stretched sprite.
	{"Render4V", sprite_render4v},// 	Renders sprite into arbitrary quad on the screen.
	{"SetTexture", sprite_settexture},// 	Sets the texture to use for the sprite.
	{"SetTextureRect", sprite_settexturerect},// 	Sets the texture region to use for the sprite.
	{"SetColor", sprite_setcolor},// 	Sets tint and alpha for the specified vertex or entire sprite.
	{"SetZ", sprite_setz},// 	Sets Z-order for the specified vertex or entire sprite.
	{"SetBlendMode", sprite_setblendmode},// 	Sets the sprite blending mode.
	{"SetHotSpot", sprite_sethotspot},// 	Sets the sprite anchor point.
	{"SetFlip", sprite_setflip},// 	Flips the sprite horizontally and/or vertically.
	{"GetTexture", sprite_gettexture},// 	Returns the current sprite texture.
	{"GetTextureRect", sprite_gettexturerect},// 	Returns the current texture region used for the sprite.
	{"GetColor", sprite_getcolor},// 	Returns color of the specified sprite vertex.
	{"GetZ", sprite_getz},// 	Returns Z-order of the specified sprite vertex.
	{"GetBlendMode", sprite_getblendmode},// 	Returns the current sprite blending mode.
	{"GetHotSpot", sprite_gethotspot},// 	Returns the sprite anchor point.
	{"GetFlip", sprite_getflip},// 	Returns the current sprite flipping.
	{"GetWidth", sprite_getwidth},// 	Returns the sprite width.
	{"GetHeight", sprite_getheight},// 	Returns the sprite height.
	{"GetBoundingBox", sprite_getboundingbox},// 	Returns the sprite bounding box.
	{NULL, NULL}
};

void luaopen_sprite(lua_State *L)
{
	create_meta(L, SPRITE, spritelib);
}
