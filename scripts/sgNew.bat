@echo off

set PROJECT_NAME=%~1

if not exist %CD%\%PROJECT_NAME% mkdir %CD%\%PROJECT_NAME%
if not exist %CD%\%PROJECT_NAME%\src mkdir %CD%\%PROJECT_NAME%\src
if not exist %CD%\%PROJECT_NAME%\assets mkdir %CD%\%PROJECT_NAME%\assets
if not exist %CD%\%PROJECT_NAME%\include mkdir %CD%\%PROJECT_NAME%\include

echo.
echo A simple project directory was created :: %CD%\%PROJECT_NAME%
echo.
pause
