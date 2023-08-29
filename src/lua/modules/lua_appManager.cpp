#include <A_Config.h>

extern const char *err_invalid_param;

int appmanager_gotoApp(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        lua_pushstring(L, err_invalid_param);
        lua_error(L);
        return 0;
    }
    const char *name = luaL_checkstring(L, 1);
    appManager.gotoApp(name);
    return 0;
}

int appmanager_goBack(lua_State *L)
{
    appManager.goBack();
    return 0;
}

static const luaL_Reg _lualib[] = {
    {"gotoApp", appmanager_gotoApp},
    {"goBack", appmanager_goBack},
    {NULL, NULL},
};

extern "C" int luaopen_appmanager(void)
{
    luaL_newlib(L, _lualib);
    return 1;
}