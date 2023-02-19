#include <iostream>
#include <string>
#include <vector>
#include <fstream>

extern "C" {
#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <fileapi.h>
};

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ==================================================================================================== //

struct vec3 {
    float x;
    float y;
    float z;
    
    vec3 operator =( const vec3& v )
    {
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }
};

struct vec2 {
    float x;
    float y;
    
    vec2 operator =( const vec2& v )
    {
        x = v.x;
        y = v.y;
        
        return *this;
    }
};

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

// ==================================================================================================== //

struct Texture {
	uint32_t id;
	std::string type;
};

// ==================================================================================================== //

std::ostream& operator<<(std::ostream& os, const glm::vec2& v);
std::ostream& operator<<(std::ostream& os, const glm::vec3& v);
std::ostream& operator<<(std::ostream& os, const Vertex& v);
std::ostream& operator<<(std::ostream& os, const Texture& v);

// ==================================================================================================== //

struct Mesh {
	std::vector<Vertex>   vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture>  textures;
    
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices  = indices;
		this->textures = textures;
	}
};

// ==================================================================================================== //

class Model {
    public:
    
	Model(char *path)
	{
		loadModel(path);
	}
	std::vector<Mesh> meshes;
	std::string directory;
    
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

// ==================================================================================================== //

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() <<std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
    
	processNode(scene->mRootNode, scene);
}

// ==================================================================================================== //

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// process all the node's meshes (if any)
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
		meshes.push_back(processMesh(mesh, scene));			
	}
	// then do the same for each of its children
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

// ==================================================================================================== //

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex>   vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture>  textures;
    
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// process vertex positions, normals and texture coordinates
		vec3 vect;
		vect.x = mesh->mVertices[i].x;
		vect.y = mesh->mVertices[i].y;
		vect.z = mesh->mVertices[i].z;
        
		vec3 vectn;
		vectn.x = mesh->mNormals[i].x;
		vectn.y = mesh->mNormals[i].y;
		vectn.z = mesh->mNormals[i].z;
        
		if (mesh->mTextureCoords[0])
		{
			vec2 vect2;
			vect2.x = mesh->mTextureCoords[0][i].x;
			vect2.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vect2;
		}
		else
		{
			vertex.TexCoords = vec2{0.0f, 0.0f};
		}
        
		vertex.Position = vect;
		vertex.Normal   = vectn;
        
		vertices.push_back(vertex);
	}
    
	// process indices
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}  
    
	// process material
#if 0
	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                                                aiTextureType_DIFFUSE, "texture_diffuse");
        
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
		std::vector<Texture> specularMaps = loadMaterialTextures(material, 
                                                                 aiTextureType_SPECULAR, "texture_specular");
        
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
#endif 
	return Mesh(vertices, indices, textures);
	
}

#if 0
// ==================================================================================================== //
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}
	return textures;
}
// ==================================================================================================== //
#endif

// ==================================================================================================== //

void write_format( const Model& M )
{
    HANDLE _file_ = CreateFileA( "New_File.bin", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    
    if( _file_ == INVALID_HANDLE_VALUE )
    {
        GetLastError();
        
        return;
    }
    
    // TODO: Probably specify how much space we need to read from each variable
    // For example something like:
    /*
Mesh 1
500 [the 500 values]
500 [the 500 values]
*/
    
    for( int i = 0; i < M.meshes.size(); i++ )
    {
        WriteFile( _file_, "Mesh ", 5, NULL, NULL );
        WriteFile( _file_, &i, sizeof( int ), NULL, NULL );
        
        size_t v_size = M.meshes[i].vertices.size();
        size_t i_size = M.meshes[i].indices.size();
        size_t t_size = M.meshes[i].textures.size();

				uint32_t * indices = (uint32_t *)M.meshes[i].indices.data();
        
        WriteFile( _file_, &v_size, sizeof(size_t), NULL, NULL );
        WriteFile( _file_, M.meshes[i].vertices.data(), M.meshes[i].vertices.size() * sizeof( Vertex ), NULL, NULL );
        
        WriteFile( _file_, &i_size, sizeof(size_t), NULL, NULL );
        WriteFile( _file_, indices ,M.meshes[i].indices.size() * sizeof( uint32_t ), NULL, NULL );
        
        WriteFile( _file_, &t_size, sizeof(size_t), NULL, NULL );
        WriteFile( _file_, M.meshes[i].textures.data() ,M.meshes[i].textures.size() * sizeof( Texture ), NULL, NULL );
    }
    
}

// ==================================================================================================== //

int main( int argc, char** argv )
{
    if( argc < 2 )
    {
        fprintf( stderr, "Provide .obj file format\n" );
        
        return 1;
    }
    
    Model M(argv[1]);
    
    write_format( M );
    
    fprintf( stdout, "Finished exporting\n" );
    
    return 0;
}

// ==================================================================================================== //

std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    os << "[ " << v.x << ", " << v.y << " ]";
    
    return os;
}

// ==================================================================================================== //

std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    
    return os;
}

// ==================================================================================================== //

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    os << "[ " << v.Position << ", " << v.Normal << ", " << v.TexCoords << " ]";
    
    return os;
}

// ==================================================================================================== //

std::ostream& operator<<(std::ostream& os, const Texture& v)
{
    os << "[ " << v.id << ", " << v.type << " ]";
    
    return os;
}

// ==================================================================================================== //

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ ";
    
    for (auto& x : v)
    {
        os << x << ", ";
    }
    
    os << " ]" << std::endl;
    
    return os;
}


// ==================================================================================================== //