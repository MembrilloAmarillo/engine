@echo off

@set INC=/I..\dependencies\glm\ /I..\dependencies\assimp\include

@set LIBS=/LIBPATH:..\dependencies\assimp\lib\Release gdi32.lib shell32.lib assimp-vc143-mt.lib

cl /nologo /W4 /Zi /MD %INC% obj_to_bin.cpp /link %LIBS%
