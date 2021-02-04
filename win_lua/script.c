#include <filesystem>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

int main() {
	_chdir("C:/Y/lua/lua_benchmarking");
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "simplerunner.lua");
	return 0;
}