@echo off
mingw32-make pb1
copy pb1-combinar-ficheros\*.csv bin\
cd bin
chcp 65001
pb1.exe
cd ..
