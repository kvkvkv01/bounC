@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 (
    echo Failed to initialize VS environment
    exit /b 1
)
cd /d "%~dp0"
cl /W4 /Fe:bounce.exe *.c user32.lib gdi32.lib
if errorlevel 1 (
    echo Compilation failed
    exit /b 1
)
echo.
echo Build successful! Run bounce.exe to test.
