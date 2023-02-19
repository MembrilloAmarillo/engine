class Shader {

public:

  unsigned int Program_ID;

	uint32_t array_ID  ;
	uint32_t buffer_ID ;
	uint32_t index_ID  ;
	uint32_t color_ID  ;
	uint32_t texture_ID;
	uint32_t normal_ID ;
	uint32_t attrib_ID ;
	uint32_t stride    ;
  
  Shader( const char* vertex_path, const char* frag_path )
  {
    if( glewInit() != GLEW_OK ) {
      std::cerr << "ERROR opening glew instance" << std::endl;
    }
    
    std::string vert_code = read_from_file( vertex_path );
    std::string frag_code = read_from_file( frag_path );

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

  void create_vao(size_t size_v,
                  size_t size_i,
                  vertex   *vertices,
                  uint32_t *indices
                  )
  {

		array_ID   = 0;
		buffer_ID  = 0;
		index_ID   = 0;
		color_ID   = 0;
		texture_ID = 0;
		normal_ID  = 0;
		attrib_ID  = 0;
		stride     = sizeof(vertex);

    glGenVertexArrays( 1, &array_ID );
    glBindVertexArray( array_ID );

    create_vbo( vertices, buffer_ID, size_v, 0 );

    //stride = 4; RGBA
    attrib_ID += 1;

		create_vbo( vertices, color_ID, size_v, sizeof(vec3) );

		attrib_ID += 1;

		create_vbo( vertices, texture_ID, size_v, 2 * sizeof(vec3) );

    assert( array_ID   != 0 );
    assert( buffer_ID  != 0 );
    assert( color_ID   != 0 );
		assert( texture_ID != 0 );

    create_ibo( indices, size_i);

    assert( index_ID != 0 );
  }
  
  void create_vbo( vertex* vertices, uint32_t& vbo, size_t size_v, size_t offset )
  {
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    glBufferData(
		 GL_ARRAY_BUFFER,
		 size_v * sizeof(vertex),
		 vertices,
		 GL_STATIC_DRAW
		 );
    
    glVertexAttribPointer(
			  attrib_ID,
			  4,
			  GL_FLOAT,
			  GL_FALSE,
			  stride,
				(void*)(offset)
			  );
    
    glEnableVertexAttribArray( attrib_ID );
  }

  void create_ibo( uint32_t* indices, size_t size_v )
  {
    glGenBuffers( 1, &index_ID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_ID );
    glBufferData(
		 GL_ELEMENT_ARRAY_BUFFER,
		 size_v * sizeof(uint32_t),
		 indices,
		 GL_STATIC_DRAW
		 );
  }

  uint32_t VAO_ID() const { return array_ID; } 
};
