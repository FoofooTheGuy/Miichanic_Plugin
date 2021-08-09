@echo off
title Easy CTRPF 0.7.0 builder
echo.Trying to use the lib in the folder (C:)
copy libctrpf.a C:\devkitPro\libctrpf\lib
make re
pause
