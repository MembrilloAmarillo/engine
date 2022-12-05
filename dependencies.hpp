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

/* DEPENDENCIES */
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_internal.h"
#include "dependencies/imgui/backends/imgui_impl_glfw.h"
#include "dependencies/imgui/backends/imgui_impl_opengl3.h"

/* SRC */
#include "utils.cpp"
#include "shader.cpp"
#include "draw.cpp"
#include "obj_loader.cpp"
