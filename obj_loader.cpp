struct OBJ {

  float* vertices;
  float* textures;
  float* normals;

  uint32_t*  indices;
  uint32_t*  texture_indices;
  uint32_t*  normals_indices;

  size_t n_vertices;
  size_t n_textures;
  size_t n_normals;
  size_t n_indices;
  size_t n_texture_indices;
  size_t n_normals_indices;
  
} OBJ;

struct OBJ* load_obj_file( const char* path )
{
  
  struct OBJ* obj = ( struct OBJ* )malloc( sizeof( struct OBJ ) );

  std::vector<float> vertices;
  std::vector<float> textures;
  std::vector<float> normals;
#if 1
  std::vector<uint32_t> indices;
  std::vector<uint32_t> texture_indices;
  std::vector<uint32_t> normals_indices;
#endif
  
  std::string sfile = read_from_file( path );

  std::cout << "Start reading object         : " << path << std::endl;

  int i = 0;
  while( i < sfile.size() ) {

    if( sfile[i] == '#' ) {
      while( sfile[i] != '\n' ) {
	i++;
      }
    }
    
    if( sfile[i] == 'v' ) {
      i++;
      if( sfile[i] == 't' ) {
	std::string temp = "";
	i += 2; // skip space
	while( sfile[i] != '\n' ) {
	  if( sfile[i] == ' ' ) {
	    textures.push_back( atof( temp.c_str() ) );
	    temp = "";
	    
	  } else {
	    temp += sfile[i];
	  }
	  i++;
	}
	textures.push_back( atof( temp.c_str() ) );
      }
      else if( sfile[i] == 'n' ) {
	std::string temp = "";
	i += 2; // skip space
	while( sfile[i] != '\n' ) {
	  if( sfile[i] == ' ' ) {
	    normals.push_back( atof( temp.c_str() ) );
	    temp = "";
	    
	  } else {
	    temp += sfile[i];
	  }
	  i++;
	}
	normals.push_back( atof( temp.c_str() ) );
      }
      else {
	std::string temp = "";
	i++;
	while( sfile[i] != '\n' ) {
	  if( sfile[i] == ' ' ) {
	    vertices.push_back( atof( temp.c_str() ) );
	    temp = "";
	    
	  } else {
	    temp += sfile[i];
	  }
	  i++;
	}
	vertices.push_back( atof( temp.c_str() ) );
      }
    }
    else if( sfile[i] == 'f' ) {
      std::string temp = "";
      i += 2; // skip space
      int j = 0;
      while( sfile[i] != '\n' && i < sfile.size() ) {
	if( sfile[i] == ' ' || sfile[i] == '/' ) {
	  if( j == 0 ) {
	    indices.insert( indices.end(), atoi( temp.c_str() ) );
	  } else if( j == 1 ) {
	    texture_indices.insert( texture_indices.end(), atoi( temp.c_str() ) );
	  } else {
	    normals_indices.insert( normals_indices.end(), atoi( temp.c_str() ) );
	  }

	  if( j == 2 ) j = 0; else j++;
	  
	  temp = "";
	    
	} else {
	  temp += sfile[i];
	}
	i++;
      }
      // Last value of line is for index of normal vertex

      normals_indices.insert( normals_indices.end(), atoi( temp.c_str() ) );      
    }
    else { // Random value
      i++;
    }
  }
  
#if 0
  for( size_t j = 0; j < obj->indices.size(); j++ ) {
    uint32_t index = obj->indices[j];
    float    value = vertices[ index - 1 ];
    obj->vertices.push_back( value );
  }
  
#else

  obj->n_vertices        = vertices.size();       
  obj->n_textures        = textures.size();       
  obj->n_normals         = normals.size();        
  obj->n_indices         = indices.size();        
  obj->n_texture_indices = texture_indices.size();
  obj->n_normals_indices = normals_indices.size();
  
  obj->vertices        = ( float* )malloc( indices.size() * sizeof( float ) );
  obj->textures        = ( float* )malloc( textures.size() * sizeof( float ) );
  obj->normals         = ( float* )malloc( normals.size() * sizeof( float ) );
  obj->indices         = ( uint32_t* )malloc( indices.size() * sizeof( uint32_t ) );
  obj->texture_indices = ( uint32_t* )malloc( texture_indices.size() * sizeof( uint32_t ) );
  obj->normals_indices = ( uint32_t* )malloc( normals_indices.size() * sizeof( uint32_t ) );

  memmove( obj->indices, &*indices.begin(), indices.size() * sizeof( uint32_t ) );

  memmove( obj->texture_indices, &*( texture_indices.begin() ), texture_indices.size() * sizeof( uint32_t ) );
  
  memmove( obj->normals_indices, &*normals_indices.begin(), normals_indices.size() * sizeof( uint32_t ) );
  
  memmove( obj->vertices, &*( vertices.begin() ), vertices.size() * sizeof( float ) );

  memmove( obj->textures, &*( textures.begin() ), textures.size() * sizeof( float ) );

  memmove( obj->normals, &*( normals.begin() ), normals.size() * sizeof( float ) );
  
#endif
  
  std::cout << "[INFO] Size of vertex array  : " <<  obj->n_vertices << std::endl;
  std::cout << "[INFO] Size of index array   : " <<  obj->n_indices << std::endl;
  std::cout << "[INFO] Size of normal array  : " <<  obj->n_normals << std::endl;
  std::cout << "[INFO] Size of texture array : " <<  obj->n_textures << std::endl;
  
  std::cout << "Finished reading object      : " << path << std::endl;
    
  return obj;
}


