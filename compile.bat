@echo off

if exist spasm.exe (
  echo "Starting Compile..."
) else (
  echo "Opening readme..."
  start "" https://github.com/Zeda/Grammer2/blob/master/Readme.md
  exit
         )

cd src

rem Generates the jumptable and grammer2.5.inc file together.
  echo "Generating grammer2.5.inc"
  python ..\tools\jt.py jmptable.z80 grammer2.5.inc
  copy /Y grammer2.5.inc ..\docs\grammer2.5.inc


:app
  set /P c=Compile Grammer?(Y/N)
  if /I "%c%" EQU "Y" (
    echo "Assembling App"
    ..\spasm.exe grammer.z80 ..\bin\grammer.8xk -I ..\z80float\single
    if exist grampkg.z80 goto :grampkg
  )

  if /I "%c%" EQU "N" goto :grampkg
goto :app

:grampkg
  set /P c=Compile Default Package?(Y/N)
  if /I "%c%" EQU "Y" (
    echo "Assembling Default Package"
    ..\spasm.exe grampkg.z80 ..\bin\grampkg.8xv
    if exist experimental\experimental.z80 goto :exppkg
  )

  if /I "%c%" EQU "N" goto :exppkg
goto :grampkg


rem Install experimental package
:exppkg
  set /P c=Compile Experimental Package?(Y/N)
  if /I "%c%" EQU "Y" (
     	echo "Assembling Experimental Package"
   	..\spasm.exe experimental\experimental.z80 ..\bin\EXPRMNTL.8xv -I single
    if exist launch.z80 goto :proglaunch
  )

  if /I "%c%" EQU "N" goto :proglaunch
goto :exppkg


rem Install program launcher
:proglaunch
  set /P c=Compile Program Launcher?(Y/N)
  if /I "%c%" EQU "Y" (
    echo "Assembling Program Launcher"
    ..\spasm.exe launch.z80 ..\bin\g250.8xp
  )
  
  if /I "%c%" EQU "N" goto :exit
goto :proglaunch

:exit
cd..
