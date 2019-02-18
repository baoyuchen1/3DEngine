#include"../../include/unit/mesh.h"
#include"../../include/root.h"
using namespace myrender;
Mesh::Mesh(vector<V3F_4_V2F> vertices, vector<unsigned int> indices, vector<unsigned int> textures)
{
	{
		this->_vertices = vertices;
		this->_indices = indices;
		this->_textures = textures;

		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}
}
void Mesh::Draw(Shader shader)
{
	// bind appropriate textures
	std::map<STRING, int> textureindexmap;
	for (GLuint i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
										  // retrieve texture number (the N in diffuse_textureN)
		string number;
		TextureManager* texturemanager = Root::getInstance()->getTextureManager();
		Texture* texture = texturemanager->GetTextureByID(_textures[i]);
		string name = texture->GetTextureType();
		if (name.empty())
			continue;
		if (textureindexmap.find(name) == textureindexmap.end())
		{
			textureindexmap[name] = 1;	
		}
		number = std::to_string(textureindexmap[name]++);

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.GetID(), (name).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureIndex());
	}

	// draw mesh
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

unsigned int Mesh::GetVAO()
{
	return _VAO;
}

vector<V3F_4_V2F> Mesh::GetVertices()
{
	return _vertices;
}

vector<unsigned int> Mesh::GetIndices()
{
	return _indices;
}

vector<unsigned int> Mesh::GetTexture()
{
	return _textures;
}

void Mesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(V3F_4_V2F), &_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_4_V2F), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_4_V2F), (void*)offsetof(V3F_4_V2F, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_4_V2F), (void*)offsetof(V3F_4_V2F, texCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_4_V2F), (void*)offsetof(V3F_4_V2F, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_4_V2F), (void*)offsetof(V3F_4_V2F, bitangent));

	glBindVertexArray(0);
}
