#pragma once
#ifndef MODEL_H
#define MODEL_H

#include"mesh.h"
#include"../render/shader.h"
#include"../constant/includefile.h"
using namespace std;

namespace myrender
{
	class Model
	{
	public:
		/*  Functions   */
		// constructor, expects a filepath to a 3D model.
		Model(string const &path, bool gamma = false);
		void SetShader(const STRING& shadername);
		void SetPosition(const VEC3& pos);
		void SetPosition(const float& x, const float& y, const float& z);
		void SetScale(const VEC3& scale);
		void SetScale(const float& x, const float& y, const float& z);
		VEC3 GetPosition();
		VEC3 GetScale();
		// draws the model, and thus all its meshes
		void Draw();
		void Destory();
		Shader GetShader();
		vector<Mesh> GetMesh();
	protected:
		~Model();
	private:
		/*  Model Data */
		bool gammaCorrection;
		Shader _shader;
		vector<int> _textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		vector<Mesh> _meshes;
		
		string _directory;
		int    _ID;
		VEC3 _position;
		VEC3 _scale;
		/*  Functions   */
		// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(string const &path);

		// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode *node, const aiScene *scene);

		Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	};
}
#endif