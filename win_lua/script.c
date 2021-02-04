#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

int main(int argc, char* argv[]) {
	chdir("../../../../lua/testes");
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	printf("argc = %d\n", argc);
	for (int ndx = 0; ndx != argc; ++ndx) {
		printf("argv[%d] --> %s\n", ndx, argv[ndx]);
		if (ndx > 0) {
			luaL_dofile(L, argv[ndx]);
		}
	}

	return 0;
}