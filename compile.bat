@echo off
if exist spasm.exe (
  echo "Starting Compile..."
) else (
  echo "Opening readme..."
  start "" https://github.com/Zeda/Grammer2/blob/master/Readme.md
  exit
)

cd src

echo "Generating grammer2.5.inc"
python jt.py jmptable.z80 grammer2.5.inc
copy /Y grammer2.5.inc ..\docs\grammer2.5.inc

echo "Assembling Default Package"
..\spasm.exe grampkg.z80 ..\bin\grampkg.8xv

echo "Assembling App"
..\spasm.exe grammer.z80 ..\bin\grammer.8xk -I ..\z80float\single

rem Check for an experimental package
if exist experimental\experimental.z80 (
  echo "Assembling Experimental Package"
  ..\spasm.exe experimental\experimental.z80 ..\bin\EXPRMNTL.8xv -I single
)

cd..
