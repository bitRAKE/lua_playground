lua_playground
==============

Small Windows/Visual Studio experiment for embedding Lua from C and running the
upstream Lua test scripts through a locally built Lua DLL.

Repository layout
-----------------

- `.gitmodules` / `lua` - upstream Lua source checkout used by the Visual Studio
  projects. Initialize it with `git submodule update --init --recursive` after
  cloning this repository.
- `win_lua/win_lua.sln` - Visual Studio 2019 solution containing two projects:
  - `win_lua/lua_dll.vcxproj` builds the upstream Lua sources as `lua54.dll`
    and `lua54.lib`.
  - `win_lua/script.vcxproj` builds the `script` console executable and links it
    against the generated Lua import library.
- `win_lua/script.lua` - small smoke-test script copied next to the executable by
  the project post-build step.
- `win_lua/test.cmd` - convenience wrapper for running files from the upstream
  `lua/testes` directory through `script`.
- `win_lua/test_results.txt` - historical notes about which upstream Lua tests
  passed under several x64 configurations.

Build and smoke test
--------------------

1. Clone with submodules, or initialize the Lua submodule after cloning:

   ```cmd
   git submodule update --init --recursive
   ```

2. Open `win_lua\win_lua.sln` in Visual Studio 2019 or newer.
3. Build the desired configuration, for example `x64|Debug` or `x64|Release`.
   The solution builds `lua54.dll` first, then the dependent `script` executable.
4. From the matching output directory, run the smoke-test script copied by the
   post-build event:

   ```cmd
   script script.lua
   ```

5. To run selected upstream Lua tests, execute `test.cmd` from `win_lua` after
   building. For example:

   ```cmd
   test bitwise.lua calls.lua
   ```

   The wrapper expands those names against `..\lua\testes\` and invokes the
   built `script` executable for each file.

Notes
-----

- `script.c` keeps plain script names relative to the current output directory, so
  `script script.lua` works as a quick smoke test. When a script argument
  includes a directory, the launcher changes to that directory before executing
  the file basename; this keeps upstream Lua tests close to their expected
  runtime layout.
- The Lua test suite was originally designed for non-Windows environments, so
  some tests are expected to be partial or configuration-dependent; see
  `win_lua/test_results.txt` for the existing result notes.

References
----------

- Upstream Lua repository and activity: https://github.com/lua/lua
- Introduction to using Lua from C: https://github.com/tylerneylon/APIsWithLua
