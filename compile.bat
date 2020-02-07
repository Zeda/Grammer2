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

    echo "Assembling App"
    ..\spasm.exe grammer.z80 ..\bin\grammer.8xk -I ..\z80float\single

rem If the second command line argument is -ca then compile everything else.
if "%1"=="-ca" (
    echo "Assembling Default Package"
    ..\spasm.exe grampkg.z80 ..\bin\grampkg.8xv

rem Install experimental package
     	echo "Assembling Experimental Package"
   	..\spasm.exe experimental\experimental.z80 ..\bin\EXPRMNTL.8xv -I single

rem Install program launcher
    echo "Assembling Program Launcher"
    ..\spasm.exe launch.z80 ..\bin\g250.8xp
    
)

cd..