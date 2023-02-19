@echo off

mkdir build
pushd build

@set SRC=..\src\main.cpp ..\dependencies\imgui\imgui*.cpp ..\dependencies\imgui\backends\imgui_impl_opengl3.cpp ..\dependencies\imgui\backends\imgui_impl_glfw.cpp 

@set INC=/I..\dependencies\imgui /I..\dependencies\imgui\backends /I..\dependencies\glm\ /I..\..\glew\include\ /I..\..\glfw\include\

@set LIBS=/LIBPATH:..\..\glew\lib\Release\x64 /LIBPATH:..\..\glfw\lib-vc2022 glew32s.lib glfw3.lib opengl32.lib gdi32.lib shell32.lib
cl /nologo /W4 /Zi /MD %INC% %SRC% /link %LIBS%

popd
