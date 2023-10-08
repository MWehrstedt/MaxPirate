@echo off
ECHO === Start Compile crows.gb ===

mkdir -p obj

SET COMP_STRING=
SET GAME_TITLE=" CROWS   "
SET GAME_RESULT=crows.gb

SETLOCAL EnableDelayedExpansion

REM resource files
ECHO -- Compiling resource files --
for /f %%f in ('dir res\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o res\%%~nf.c -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

REM source files
ECHO -- Compiling source files --
for /f %%f in ('dir src\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o src\%%~nf.c -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% -Wm-yn%GAME_TITLE% -Wl-yt0x19 -Wl-j -Wm-yoA -autobank -Wb-ext=.rel -Wb-v -debug

ECHO %COMP_STRING%
ECHO === End Compile crows.gb ===

IF "%~1"=="-nostart" GOTO SCRIPTEND

ECHO -- Start ROM in BGB --
..\..\Tools\bgb\bgb.exe obj\crows.gb

:SCRIPTEND
