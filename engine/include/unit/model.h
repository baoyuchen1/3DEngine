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
		Model(STRING const &path, bool gamma = false);
		void SetShader(const STRING& shadername);
		void SetPosition(const VEC3& pos);
		void SetPosition(const float& x, const float& y, const float& z);
		void SetScale(const VEC3& scale);
		void SetScale(const float& x, const float& y, const float& z);
		VEC3 GetPosition();
		VEC3 GetScale();
		// draws the model, and thus all its meshes
		virtual void Draw();
		void Destory();
		Shader GetShader();
		vector<Mesh> GetMesh();
	protected:
		virtual ~Model();
		Model();
		/*  Model Data */
		bool gammaCorrection;
		Shader _shader;
		vector<Mesh> _meshes;
		
		STRING _directory;
		STRING _name;
		int    _ID;
		VEC3 _position;
		VEC3 _scale;
		/*  Functions   */
		// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		virtual void loadModel(STRING const &path);

		// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		virtual void processNode(aiNode *node, const aiScene *scene);

		virtual Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	};
	class PBRModel :public Model
	{
	public:
		PBRModel (STRING const &path, bool gamma = false);
		virtual void Draw();
	private:

		virtual Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		unsigned int _albedoMap;
		unsigned int _normalMap;
		unsigned int _metallicMap;
		unsigned int _roughnessMap;
		unsigned int _aoMap;
	};
}
#endif