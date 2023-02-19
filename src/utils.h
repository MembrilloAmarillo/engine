/* date = December 12th 2022 0:51 am */

#ifndef UTILS_H
#define UTILS_H

#define NORMALIZE( max, min, val ) ( 2.0 * ( val - min ) / ( max - min ) ) - 1

std::string read_from_file( const char* file_path );

void normalize_vector( float* vector, size_t vector_len );

#endif //UTILS_H
