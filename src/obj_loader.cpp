struct vec2 {
    float x;
    float y;

    vec2 operator= (const vec2& v)
    {
      x = v.x;
      y = v.y;
        
      return *this;
    }
};

struct vec3 {
    float x;
    float y;
    float z;

    vec3 operator= (const vec3& v)
    {
      x = v.x;
      y = v.y;
      z = v.z;

      return *this;
    }
};

struct vertex {
    vec3 position;
    vec3 normal;
    vec2 tex_coord;
};

struct OBJ {

    vertex   * vertices;
    uint32_t * indices;
    
    size_t n_vertices;
    size_t n_indices;
    size_t n_textures;

    
    //TODO: Create just a BIG allocation and asign different offsets to the pointers so that we 
    //      dont have to call to VirtualAlloc and VirtualFree multiple times
    void start_obj()
    {
        vertices        = (vertex*)  VirtualAlloc(NULL, 1 << 30, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        indices         = (uint32_t*)VirtualAlloc(NULL, 1 << 30, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    }
    
    void free_all() {
        VirtualFree(vertices, 1 << 30, MEM_RELEASE);
        VirtualFree(indices,  1 << 30, MEM_RELEASE);
    }
    
} OBJ;

internal
struct OBJ* load_bin_file(const char* path)
{
    struct OBJ* obj = ( struct OBJ* )malloc( sizeof( struct OBJ ) );
    obj->start_obj();
    
    HANDLE _file_ = CreateFileA( path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if( _file_ == INVALID_HANDLE_VALUE )
    {
        GetLastError();
        std::cerr << "[FILE] Error opening file" << std::endl;
        return NULL;
    }
    
    char _Mesh_[6];
    int  mesh_id;
    
    if (ReadFile(_file_, _Mesh_, 5, NULL, NULL))
    {
      ReadFile(_file_, &mesh_id, sizeof(int), NULL, NULL);

      ReadFile(_file_, &obj->n_vertices, sizeof(size_t), NULL, NULL);
      ReadFile(_file_, obj->vertices, obj->n_vertices * sizeof(vertex), NULL, NULL);
              
      ReadFile(_file_, &obj->n_indices, sizeof(size_t), NULL, NULL);
      ReadFile(_file_, obj->indices, obj->n_indices * sizeof(uint32_t), NULL, NULL);

      ReadFile(_file_, &obj->n_textures, sizeof(size_t), NULL, NULL);
    }
    
    std::cout << "[INFO] Number of vertices: " << obj->n_vertices << std::endl;
    std::cout << "[INFO] Number of indices:  " << obj->n_indices  << std::endl;
    
    return obj;
}