@echo off
REM Build script for chilling project using gcc on Windows

gcc src\main.c src\open.c src\keywords.c src\signals.c src\state.c -o redstone.exe

if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

echo Build complete. Run redstone.exe <filename> to execute.
