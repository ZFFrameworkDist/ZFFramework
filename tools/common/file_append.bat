@echo off
setlocal

set WORK_DIR=%~dp0
set DST_PATH=%~1%
set SRC_PATH=%~2%

if not defined DST_PATH goto :usage
if not defined SRC_PATH goto :usage
goto :run
:usage
echo usage:
echo   file_append.bat DST_PATH SRC_PATH
exit /b 1
:run

more "%SRC_PATH%" >> "%DST_PATH%.tmp"

