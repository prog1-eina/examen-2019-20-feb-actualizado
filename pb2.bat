@echo off
make pb2
copy pb2-mayor-sismicidad\*.csv bin\
copy pb2-mayor-sismicidad\provincias.txt bin\
cd bin
chcp 65001
pb2.exe
cd ..
