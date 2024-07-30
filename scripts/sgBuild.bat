@echo off
setlocal enabledelayedexpansion

REM Initialize variables
set "source_file="
set "output_file="
set "include_dirs=-I"%SG_INC_DIR%""
set "lib_dirs=-L"%SG_LIB_DIR%""
set "libs=-lglfw3 -lglew32 -lopengl32"
set "default_output=yes"

REM Parse command-line arguments
:parse_args
if "%~1"=="" goto done_parse

REM Check for source file
if not defined source_file (
    set "source_file=%~1"
    shift
    goto parse_args
)

REM Check for output file
if /I "%~1"=="-o" (
    set "output_file=%~2"
    set "default_output=no"
    shift
    shift
    goto parse_args
)

REM Check for additional include directories
if /I "%~1"=="-I" (
    set "include_dirs=!include_dirs! -I"%~2""
    shift
    shift
    goto parse_args
)

REM Check for additional library directories
if /I "%~1"=="-L" (
    set "lib_dirs=!lib_dirs! -L"%~2""
    shift
    shift
    goto parse_args
)

REM Check for additional libraries
if /I "%~1"=="-l" (
    set "libs=!libs! -l%~2"
    shift
    shift
    goto parse_args
)

REM Unrecognized argument
shift
goto parse_args

:done_parse
REM Validate source file
if not defined source_file (
    echo simply no source file specified.
    exit /b 1
)

REM Set default output file name if not provided
if "%default_output%"=="yes" (
    REM Extract the base name of the source file without the extension
    for %%F in ("%source_file%") do set "output_file=%%~nF.exe"
)

REM Compile the source file
echo Compiling :: %source_file%
if not exist build mkdir build

xcopy %SG_LIB_DIR% build

gcc -g -D_DEBUG %source_file% %include_dirs% %lib_dirs% %libs% -o build\%output_file%
if errorlevel 1 (
    echo compilation simply failed for %source_file%.
    exit /b 1
)

REM Output the result
echo a simply successful build :: %output_file%
pause

endlocal
