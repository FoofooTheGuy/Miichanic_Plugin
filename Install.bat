::stole some code from Home Menu Tool By Arch9SK7 for this
@echo off
mode con:cols=78 lines=25

:START
::First page
set TID=
title Miichanic's Tool Box Installer v1.00
echo.
echo.  __________________________________________________________________________
echo. ^|                                                                          ^|
echo. ^|              Welcome to the Miichanic's Tool Box Installer!              ^|
echo. ^|                                                                          ^|
echo. ^|__________________________________________________________________________^|
echo.
echo.
echo.Step 1: Drag and drop the .3gx file into this terminal and then press Enter:
echo.
set /p File=
echo.
echo.Step 2: Select the region you want to install the plugin for,
echo.or quit the installation:
echo.
echo.[1] Japan   (0004001000020700)
echo.[2] USA     (0004001000021700)
echo.[3] Europe  (0004001000022700)
echo.[4] China   (0004001000026700)
echo.[5] Korea   (0004001000027700)
echo.[6] Taiwan  (0004001000028700)
echo.[X] Cancel installation
echo.

set /p choiche=

if %choiche%==1 (
set TID=0004001000020700
goto CREATE
) else if %choiche%==2 (
set TID=0004001000021700
goto CREATE
) else if %choiche%==3 (
set TID=0004001000022700
goto CREATE
) else if %choiche%==4 (
set TID=0004001000026700
goto CREATE
) else if %choiche%==5 (
set TID=0004001000027700
goto CREATE
) else if %choiche%==6 (
set TID=0004001000028700
goto CREATE
) else if %choiche%==x (
goto EOF
) else if %choiche%==X (
goto EOF
) else goto START

:CREATE
::copy to sd card (not for ftp i think) taken from Home Menu Tool
echo Looking for valid SD Card
for /f "tokens=1,2,3,4" %%a in ('wmic logicaldisk get caption^,drivetype^,filesystem^,volumename') do (
	if "%%b"=="2" if "%%c"=="FAT32" if exist "%%a\Nintendo 3DS\" set SDDrive=%%a&set SDName=%%d
)
if "%SDDrive%"=="" (
	echo.
	echo Unable to find SD Card
	pause>nul
	goto START
)
cd %~dp0
md %SDDrive%\luma\plugins\%TID% 2> nul
if NOT exist "%File%" (
echo Copying %File% to %SDName% [%SDDrive%]
copy "%File%" "%SDDrive%\luma\plugins\%TID%\"
) else (
echo Copying %File% to %SDName% [%SDDrive%]
copy "%File%" "%SDDrive%\luma\plugins\%TID%\" )
echo.Completed, press any button to exit
pause>nul
goto EOF

:EOF
echo. Closing the window...