@echo off
if "%~1"=="" (
    echo Usage: test ^<lua-test-name^> [more-test-names...]
    echo Example: test bitwise.lua calls.lua
    exit /b 1
)

for %%G in (%*) do script "..\lua\testes\%%~G"
