#pragma once
#ifndef MESH_H
#define MESH_H
#include"../render/shader.h"
#include"../constant/engine_constant.h"
#include"modelbase.h"
using namespace std;
namespace myrender
{
	class Mesh {
	public:

		/*  Functions  */
		// constructor
		Mesh(vector<V3F_4_V2F> vertices, vector<unsigned int> indices, vector<unsigned int> textures);

		// render the mesh
		void Draw(Shader shader);

		unsigned int GetVAO();
		vector<V3F_4_V2F> GetVertices();
		vector<unsigned int> GetIndices();
		vector<unsigned int> GetTexture();
	private:
		/*  Render data  */
		unsigned int _VBO, _EBO;
		/*  Mesh Data  */
		unsigned int _VAO;
		vector<V3F_4_V2F> _vertices;
		vector<unsigned int> _indices;
		vector<unsigned int> _textures;
		/*  Functions    */
		// initializes all the buffer objects/arrays
		void setupMesh();

	};
}

#endif