//Needs header
#include "Loader.h"

//In namespace
namespace Loader
{
	GLuint loadTexture(const char* path)
	{
		//Find the next index
		Graphics::current_tex_index++;

		//Generate a new texture object
		Texture temp;
		temp.file_path = path;
		temp.value = &Graphics::current_tex_index;

		Graphics::all_textures[Graphics::current_tex_index] = temp;

		//Done
		return Graphics::current_tex_index;
	}

	Mesh loadModel(const char* path)
	{
		//Load models
		IndexedModel model = OBJModel(std::string(path)).ToIndexedModel();

		//Fix the array formatting - temp
		std::vector<GLfloat> vec_verts;

		//Very temporary
		for (int i = 0; i < model.positions.size(); i++)
		{
			//Set individually because data format is:
			//X - Y - Z - S - T
			vec_verts.push_back(model.positions[i].x);
			vec_verts.push_back(model.positions[i].y);
			vec_verts.push_back(model.positions[i].z);

			vec_verts.push_back(model.texCoords[i].x);
			vec_verts.push_back(1.0f - model.texCoords[i].y);
		}

		//Stores vert C array
		GLfloat* verticies = new GLfloat[vec_verts.size()];
		for (int i = 0; i < vec_verts.size(); i++) verticies[i] = vec_verts[i];

		//Create index C array
		GLushort* indicies = new GLushort[model.indices.size()];
		for (int i = 0; i < model.indices.size(); i++) indicies[i] = model.indices[i];

		//Find size of a dynamic array
		int vertex_byte_size = sizeof(GLfloat) * vec_verts.size();
		int indicies_byte_size = sizeof(GLushort) * model.indices.size();

		//Create
		Mesh mesh;
		mesh.Init(vertex_byte_size, verticies, indicies_byte_size, indicies);

		//Return
		return mesh;
	}

	void Play(const char* path, bool loop)
	{
		//Plays the sound
		SoundManager::Engine->play2D(path, loop);
	}

	void Play(const char* path, bool loop, vec3df position)
	{
		//Plays the sound
		SoundManager::Engine->play3D(path, position, loop);
	}
}