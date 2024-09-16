#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

// TODO: COULD CREATE A MESH INTERFACE WHICH ALL MESH CLASSES DERIVE FROM. 
// CURRENTLY ONLY NEED 2D MESHES THOUGH SO MAYBE WASTE OF TIME.

// A mesh represents a single drawable entity. In this case the mesh is 2D
// meaning position data only contains 2 values per vertex.
class Mesh2D {
private:
	// TODO: HAVE THE MESH INCLUDE MORE VERTEX DATA LIKE TEXTURE OR COLOUR DATA.
	// each vec2 is a vertex.
	std::vector<glm::vec2> m_positionData;
	// each index relates to a vertex in m_positionData which will be drawn.
	std::vector<unsigned int> m_indices;
	// Normalised rgb value relating to the colour of the entire object.
	glm::vec3 m_colour;

	// The vertex buffer contains the raw vertex data;
	GLuint m_vbID;
	// A configured va should configure the raw vertex data into at least one
	// vertex attribute per vertex;
	GLuint m_vaID;
	// The index buffer contains the indices of which vertices should be used to 
	// draw the mesh.
	GLuint m_ibID;

public:
	// Creates empty mesh with no vertex data.
	Mesh2D();
	// Creates a 2d mesh with position data and black colour. The mesh can be drawn with just position
	// data and no indices.
	Mesh2D(std::vector<glm::vec2> &positionData);
	// Creates a 2d mesh with the position and index data, black colour and configures the interal
	// buffers and array correctly
	Mesh2D(std::vector<glm::vec2> &positionData, std::vector<unsigned int> &indices);
	// Creates a 2d mesh with the position and index data and configures the interal
	// buffers and array correctly. Sets colour to specified colour.
	Mesh2D(std::vector<glm::vec2> &positionData, std::vector<unsigned int> &indices, glm::vec3 colour);
	~Mesh2D();

	// Delete all current positions vertex data and uses the new positions data.
	// Reconfigures the interal buffers and arrays.
	void UpdatePositionVertices(std::vector<glm::vec2> &positionData);
	// Deletes all current indices data and uses the new indices data. Reconfigures
	// all internal buffers and array
	void UpdateIndices(std::vector<unsigned int> &indices);
	// Sets the colour of the mesh to the specified colour. Notes a mesh can
	// only have 1 colour.
	void UpdateColour(glm::vec3 colour);

	// Checks if the currently stored index data is compatible with the
	// currently stored position data.
	bool isValidIndices() const;

	// Returns the amount of indices stored by the mesh.
	unsigned int GetIndicesCount() const;
	// Returns the amount of vertices stored by the internal vertex array.
	unsigned int GetVertexCount() const;

	// Returns the ID of the vertex array used by this object that openGL assigns.
	GLuint GetVertexArrayID() const;
	// Returns the ID of the index buffer used by this objects that opengl assigns.
	GLuint GetIndexBufferID() const;

	glm::vec3 GetColour() const;
};

#endif
