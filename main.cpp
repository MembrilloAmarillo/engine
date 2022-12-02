#include <iostream>
#include <cstdint>

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

#include "shader.cpp"
#include "draw.cpp"

static void glfw_error_callback( int error, const char* description )
{
  fprintf( stderr, "GLFW Error %d: %s\n", error, description );
}

int main()
{  
  glfwSetErrorCallback( glfw_error_callback );

  if( !glfwInit() ) {
    return 1;
  }

  const char* glsl_version = "#version 430";
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

  GLFWwindow* window = glfwCreateWindow( 1280, 720, "Satisfactory Scheme", NULL, NULL );
  if( window == NULL ) {
    return 1;
  }

  glfwMakeContextCurrent( window );
  glfwSwapInterval( 1 ); // vsync

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL( window, true );
  ImGui_ImplOpenGL3_Init( glsl_version );

  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glEnable( GL_CULL_FACE );
  glDisable( GL_MULTISAMPLE );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  float vertex[3*3] = { 0.5, 0.5, 0.0,
			0.0, -0.5, 0.0,
			-0.5, 0.0, 0.0 };

  float colors[4*3] = { 0.9, 0.3, 0.1, 0.0,
			0.3, 0.1, 0.9, 0.0,
			0.1, 0.8, 0.1, 0.0
  };
  
  uint32_t indices[3] = { 2, 1, 0 };

  Shader current_shader( "./shaders/shaders.vert", "./shaders/shaders.frag" );

  current_shader.create_vao( 3 * 3 * sizeof( float ),
			     3 * 1 * sizeof( uint32_t ),
			     4 * 3 * sizeof( float ),
			     vertex, indices, colors );
  current_shader.activate();

  glm::vec3 xyz( 0.0, 0.0, 0.0 );
  glm::vec3 rot( 0.0, 0.0, 0.0 );
  float angle = 0.0f;
  
  while( !glfwWindowShouldClose( window ) ) {

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell
    // if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    //   your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data
    //   to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from
    // your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::ShowMetricsWindow();
    
    ImGui::Begin("Translate Triangle");		 
    ImGui::SliderFloat( "X Axis", &xyz[0], 0.0, 1.0 );
    ImGui::SliderFloat( "Y Axis", &xyz[1], 0.0, 1.0 );
    ImGui::SliderFloat( "Z Axis", &xyz[2], 0.0, 1.0 );
    ImGui::End();

    ImGui::Begin("Rotation Triangle");		 
    ImGui::SliderFloat( "X Axis", &rot[0], 0.0, 1.0 );
    ImGui::SliderFloat( "Y Axis", &rot[1], 0.0, 1.0 );
    ImGui::SliderFloat( "Z Axis", &rot[2], 0.0, 1.0 );
    ImGui::SliderFloat( "Angle", &angle, 0.0, 2.0 * glm::pi<float>()  );
    ImGui::End();
    
    //ImGui::ColorEdit4( "Colors", colors );

    ImGui::Begin( "Triangle parameters" );
    
    if( ImGui::CollapsingHeader( "Color" ) ) {
      ImGui::Text( "Colors of triangle" );
      ImGui::Separator();
      ImGui::Text( "Rotation of triangle" );
    }

    ImGui::End();
    
    ImGui::EndFrame();
    
    
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize( window, &display_w, &display_h );
    glViewport( 0, 0, display_w, display_h );

    glClearColor( clear_color.x * clear_color.w,
		  clear_color.y * clear_color.w,
		  clear_color.z * clear_color.w,
		  clear_color.w );
    
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

    translate_triangle( xyz, current_shader.Program_ID );
    rotate_triangle( rot, angle, current_shader.Program_ID );
    
    glBindVertexArray( current_shader.VAO_ID() );
    glDrawElements( GL_TRIANGLES, sizeof( indices ), GL_UNSIGNED_INT, NULL );
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
  
}
