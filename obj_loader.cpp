struct OBJ {

  std::vector<float> vertices;
  std::vector<float> textures;
  std::vector<float> normals;

  std::vector<uint32_t>  indices;
  std::vector<uint32_t>  texture_indices;
  std::vector<uint32_t>  normals_indices;

  
} OBJ;

struct OBJ* load_obj_file( const char* path )
{
  
  struct OBJ* obj = ( struct OBJ* )malloc( sizeof( struct OBJ ) );

  std::vector<float> vertices;
  std::vector<float> textures;
  std::vector<float> normals;

  std::string sfile = read_from_file( path );

  int i = 0;
  while( i < sfile.size() ) {
    
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
      i++; // skip space
      int j = 0;
      while( sfile[i] != '\n' || sfile[i] != EOF ) {
	if( sfile[i] == ' ' || sfile[i] == '/' ) {
	  if( j == 0 ) {
	    obj->indices.push_back( atoi( temp.c_str() ) );
	  } else if( j == 1 ) {
	    obj->texture_indices.push_back( atoi( temp.c_str() ) );
	  } else {
	    obj->normals_indices.push_back( atoi( temp.c_str() ) );
	  }
	  j += j % 3;
	  temp = "";
	    
	} else {
	  temp += sfile[i];
	}
	i++;
      }
      normals.push_back( atof( temp.c_str() ) );      
    }
    else {
      i++;
    }
  }

  for( uint32_t i = 0; i < obj->indices.size(); i++ ) {
    uint32_t index = obj->indices[i];
    float    value = vertices[ index - 1 ];
    obj->vertices.push_back( value );
  }

  std::cout << "FINISHED" << std::endl;
    
  return obj;
}


