# ENGINE
For now its a simple 3D object visualizer, but is 
supposed to be a useful game engine at one point
for my own projects

Under development, so it does have 0 things added yet

### Dependencies

- GLFW
- GLEW
- ImGui  (included on dependencies)
- glm    (included on dependencies)
- assimp (included on dependencies)

### How I work with 3D Objects

In the misc directory, there is a cpp file called obj_to_bin.cpp. Use the 
'build.bat' script to build the file and then you can use the exe:
"obj_to_bin.exe path/to/file"

This binary file is the one that will be used for the main program.
The purpose of this is solely to not have assimp on the main program that 
is just pure pain and slow. 

With this you can just convert all the objects you want to use and 
then just load the bin file into the main program.

NOTE: For now It only works with object with a single mesh, no textures
for now.

### Build

For the build of the main program is fairly simple:

Use the set_vc.bat script to enable the msvc compiler and then 
execute the build.bat file.

In case it gives you problems maybe you need to update the paths of GLFW and
GLEW inside the build.bat file.

### Executing

For that just put:
"build\main.exe path/to/bin_obj"
