#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <string>

#define NORMALIZE( max, min, val ) ( 2.0 * ( val - min ) / ( max - min ) ) - 1

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

void normalize_vector( float* vector, size_t vector_len )
{
    float max_x, min_x;
    float max_y, min_y;
    float max_z, min_z;
    
    for( int i = 0; i < vector_len - 3; i++ ) {
        if( vector[i] >= max_x ) {
            max_x = vector[i];
        } else if( vector[i] <= min_x ) {
            min_x = vector[i];
        }
        if( vector[i+1] >= max_y ) {
            max_y = vector[i+1];
        } else if( vector[i+1] <= min_y ) {
            min_y = vector[i+1];
        }
        if( vector[i+2] >= max_z ) {
            max_z = vector[i+2];
        } else if( vector[i+2] <= min_z ) {
            min_z = vector[i+2];
        }
    }
    
    for( int i = 0; i < vector_len - 3; i++ ) {
        vector[i]     = ( 2.0f * ( vector[i]     - min_x ) / ( max_x - min_x ) ) - 1.0f; 
        vector[i + 1] = ( 2.0f * ( vector[i + 1] - min_y ) / ( max_y - min_y ) ) - 1.0f;
        vector[i + 2] = ( 2.0f * ( vector[i + 2] - min_z ) / ( max_z - min_z ) ) - 1.0f;
    }
    
}