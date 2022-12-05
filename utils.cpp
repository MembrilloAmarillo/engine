#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <string>

std::string read_from_file( const char* file_path )
{

    std::string data;
    
    std::ifstream data_file;

    data_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try {
      data_file.open( file_path );

      std::stringstream data_stream;

      data_stream << data_file.rdbuf();

      data_file.close();

      data = data_stream.str();

    } catch( std::ifstream::failure e ) {
      std::cout << "ERROR: Shader file not succesfully read" << std::endl;
    }

    return data;
}
