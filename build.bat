@echo off

if not exist "bin" (
    mkdir bin
)

if exist "src\main.cpp" (
    g++ src\main.cpp -o bin\TrashGenerator.exe
) else (
    echo [-] Error! Source code not found.
)
