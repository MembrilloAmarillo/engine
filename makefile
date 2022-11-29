CC       = clang++
CFLAGS   = -g -Wall -Wextra -pedantic
CXXFLAGS = -std=c++17 
LIBS     = -lGL -lglfw -lGLEW

DEP = ./dependencies/imgui

SRC = main.cpp

OBJ += imgui.o \
	imgui_draw.o \
	imgui_impl_glfw.o \
	imgui_tables.o \
	imgui_widgets.o \
	imgui_impl_glfw.o \
	imgui_impl_opengl3.o

OBJ += main.o

DEP_SRC = $(DEP)/imgui.cpp \
	$(DEP)/imgui_draw.cpp \
	$(DEP)/imgui_tables.cpp \
	$(DEP)/imgui_widgets.cpp \
	$(DEP)/backends/imgui_impl_glfw.cpp \
	$(DEP)/backends/imgui_impl_opengl3.cpp

DEP_INC = $(DEP)/imgui.h $(DEP)/backends/imgui_impl_glfw.h $(DEP)/backends/imgui_impl_opengl3.h

OUT = ss

all: $(OUT)

$(OUT) : $(OBJ)
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(OUT) $^ $(LIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o main.o main.cpp -I$(DEP)

%.o : $(DEP)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $< -I$(DEP)

%.o : $(DEP)/backends/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $< -I$(DEP)


.PHONY: clean

clean:
	rm -rf $(OUT) main.o $(OBJ) *~
