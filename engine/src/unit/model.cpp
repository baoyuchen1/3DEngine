#include"../../include/unit/model.h"
#include"../../include/root.h"
using namespace myrender;
Model::Model(string const &path, bool gamma) : gammaCorrection(gamma)
{
	
	loadModel(path);
}

void myrender::Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void myrender::Model::loadModel(string const & path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

void myrender::Model::processNode(aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}

Mesh myrender::Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	TextureManager* texturemanager = Root::getInstance()->getTextureManager();
	vector<V3F_4_V2F> vertices;
	vector<unsigned int> indices;
	vector<unsigned int> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		V3F_4_V2F vertex;
		glm::vec3 v; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // positions
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;
		vertex.position = v;
		// normals
		v.x = mesh->mNormals[i].x;
		v.y = mesh->mNormals[i].y;
		v.z = mesh->mNormals[i].z;
		vertex.normal = v;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		// tangent
		v.x = mesh->mTangents[i].x;
		v.y = mesh->mTangents[i].y;
		v.z = mesh->mTangents[i].z;
		vertex.tangent = v;
		// bitangent
		v.x = mesh->mBitangents[i].x;
		v.y = mesh->mBitangents[i].y;
		v.z = mesh->mBitangents[i].z;
		vertex.bitangent = v;
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	vector<int> diffuseMaps = texturemanager->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<int> specularMaps = texturemanager->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<int> normalMaps = texturemanager->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", directory);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<int> heightMaps = texturemanager->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", directory);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}
