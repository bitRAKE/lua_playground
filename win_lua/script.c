#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define change_dir _chdir
#else
#include <unistd.h>
#define change_dir chdir
#endif

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

static char* last_path_separator(char* path) {
	char* slash = strrchr(path, '/');
	char* backslash = strrchr(path, '\\');

	if (slash == NULL) return backslash;
	if (backslash == NULL) return slash;
	return slash > backslash ? slash : backslash;
}

static int dofile_from_argument(lua_State* L, const char* argument) {
	char path[FILENAME_MAX];
	snprintf(path, sizeof(path), "%s", argument);

	char* file = path;
	char* separator = last_path_separator(path);
	if (separator != NULL) {
		*separator = '\0';
		file = separator + 1;
		if (change_dir(path) != 0) {
			fprintf(stderr, "could not enter test directory: %s\n", path);
			return 1;
		}
	}

	if (luaL_dofile(L, file) != LUA_OK) {
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[]) {
	lua_State* L = luaL_newstate();
	if (L == NULL) {
		fprintf(stderr, "failed to create Lua state\n");
		return 1;
	}
	luaL_openlibs(L);

	printf("argc = %d\n", argc);
	int result = 0;
	for (int ndx = 0; ndx != argc; ++ndx) {
		printf("argv[%d] --> %s\n", ndx, argv[ndx]);
		if (ndx > 0 && dofile_from_argument(L, argv[ndx]) != 0) {
			result = 1;
			break;
		}
	}

	lua_close(L);
	return result;
}
