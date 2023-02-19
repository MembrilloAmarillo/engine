/* STD */
#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

/* DEPENDENCIES */
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define internal static
#define local    static
#define global   static

#include "utils.h"
#include "draw.h"

/* SRC */
#include "utils.cpp"
#include "obj_loader.cpp"
#include "shader.cpp"
#include "draw.cpp"

