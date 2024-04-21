@echo off
rmdir /S /Q .\build
mkdir .\build
cmake -G "MinGW Makefiles" -S ".\src" -B ".\build" -D CMAKE_PREFIX_PATH="C:\Qt\6.7.0\mingw_64" -D BUILD_SHARED_LIBS=TRUE

