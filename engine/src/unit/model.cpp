#include"../../include/unit/model.h"
#include"../../include/root.h"
using namespace myrender;
Model::Model(STRING const &path, bool gamma) : gammaCorrection(gamma)
{
	_shader=Shader("./resource/shader/shader.vs", "./resource/shader/shader.fs");
	loadModel(path);
	auto render = Root::getInstance()->getRender();
	this->_ID = render->AddModel(this);
}

void myrender::Model::SetShader(const STRING & shadername)
{
	auto render = Root::getInstance()->getRender();
	Shader* shader = render->GetShaderByName(shadername);
	if (shader != nullptr)
	{
		_shader = (*shader);
	}
}

void myrender::Model::SetPosition(const VEC3 & pos)
{
	_position = pos;
}

void myrender::Model::SetPosition(const float & x, const float & y, const float & z)
{
	_position = VEC3(x, y, z);
}

void myrender::Model::SetScale(const VEC3 & scale)
{
	_scale = scale;
}

void myrender::Model::SetScale(const float & x, const float & y, const float & z)
{
	_scale = VEC3(x, y, z);
}

VEC3 myrender::Model::GetPosition()
{
	return _position;
}

VEC3 myrender::Model::GetScale()
{
	return _scale;
}

void myrender::Model::Draw()
{

	for (unsigned int i = 0; i < _meshes.size(); i++)
		_meshes[i].Draw(_shader);
}

void myrender::Model::Destory()
{
	auto render = Root::getInstance()->getRender();
	render->RemoveModel(this->_ID);
	delete this;

}

Shader myrender::Model::GetShader()
{
	return _shader;
}

vector<Mesh> myrender::Model::GetMesh()
{
	return _meshes;
}

myrender::Model::~Model()
{

}

myrender::Model::Model()
{
}

void myrender::Model::loadModel(STRING const & path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene;
	auto render = Root::getInstance()->getRender();
	_meshes = render->GetMesh(path);
	int a = path.find_last_of('.');
	int b = path.find_last_of('/');
	_directory = path.substr(0, b);
	_name = path.substr(b+1,a-b-1);
	if (!_meshes.empty())
	{
		return;
	}
	render->SetMeshMap(path, this);
	scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	

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
		_meshes.push_back(this->processMesh(mesh, scene));
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
	vector<int> diffuseMaps = texturemanager->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", _directory);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<int> specularMaps = texturemanager->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", _directory);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<int> normalMaps = texturemanager->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", _directory);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<int> heightMaps = texturemanager->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", _directory);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

myrender::PBRModel::PBRModel(STRING const & path, bool gamma)
{
	_shader = Shader("./resource/shader/shader.vs", "./resource/shader/shader.fs");
	loadModel(path);
	auto render = Root::getInstance()->getRender();
	this->_ID = render->AddModel(this);
}

void myrender::PBRModel::Draw()
{
	this->Model::Draw();
}

Mesh myrender::PBRModel::processMesh(aiMesh * mesh, const aiScene * scene)
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

	STRING temp = _directory + "/Textures/" + _name;
	_albedoMap = texturemanager->SetTexture(temp +"_A.tga","albedo");
	textures.push_back(_albedoMap);
	_normalMap = texturemanager->SetTexture(temp + "_N.tga","normalMap");
	textures.push_back(_normalMap);
	_metallicMap = texturemanager->SetTexture(temp + "_M.tga","metallic");
	textures.push_back(_metallicMap);
	_roughnessMap = texturemanager->SetTexture(temp + "_R.tga","roughness");
	textures.push_back(_roughnessMap);
	_aoMap = texturemanager->SetTexture(temp + "_AO.tga","ao");
	textures.push_back(_aoMap);
	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}
