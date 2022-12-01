#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

class Shader {

public:

  unsigned int Program_ID;

  Shader( const char* vertex_path, const char* frag_path )
  {
    if( glewInit() != GLEW_OK ) {
      std::cerr << "ERROR opening glew instance" << std::endl;
    }
    std::string vert_code;
    std::string frag_code;
    
    std::ifstream vertex_file;
    std::ifstream frag_file;

    vertex_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    frag_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    
    try {
      vertex_file.open( vertex_path );
      frag_file.open( frag_path );       

      std::stringstream vert_stream, frag_stream;

      vert_stream << vertex_file.rdbuf();
      frag_stream << frag_file.rdbuf();

      vertex_file.close();
      frag_file.close();

      vert_code = vert_stream.str();
      frag_code = frag_stream.str();

    } catch( std::ifstream::failure e ) {
      std::cout << "ERROR: Shader file not succesfully read" << std::endl;
    }

    const char* c_vert_code = vert_code.c_str();
    const char* c_frag_code = frag_code.c_str();

    unsigned int vertex, fragment;
    int success;
    char info_log[512];

    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &c_vert_code, NULL );
    glCompileShader( vertex );
    glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
    if( !success ) {
      glGetShaderInfoLog( vertex, 512, NULL, info_log );
      std::cout << "ERROR: shader vertex compilation failed\n" << info_log << std::endl;
    }
    
    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &c_frag_code, NULL );
    glCompileShader( fragment );
    glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
    if( !success ) {
      glGetShaderInfoLog( fragment, 512, NULL, info_log );
      std::cout << "ERROR: shader fragment compilation failed\n" << info_log << std::endl;
    }

    Program_ID = glCreateProgram();
    glAttachShader( Program_ID, vertex );
    glAttachShader( Program_ID, fragment );
    glLinkProgram( Program_ID );
    glGetProgramiv( Program_ID, GL_LINK_STATUS, &success );
    if( !success ) {
      glGetProgramInfoLog( Program_ID, 512, NULL, info_log );
      std::cout << "Error shader program linking failed\n" << info_log << std::endl;
    }

    glDeleteShader( vertex );
    glDeleteShader( fragment );

  }

  void activate()
  {
    glUseProgram( Program_ID );
  }

private:
  
};
