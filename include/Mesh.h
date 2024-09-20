#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

// A mesh represents a single drawable entity. In this case the mesh is 2D
// meaning position data only contains 2 values per vertex.
class Mesh2D {
private:
	// TODO: HAVE THE MESH INCLUDE MORE VERTEX DATA LIKE TEXTURE OR COLOUR DATA.
	// each vec2 is a vertex.
	std::vector<glm::vec2> m_positionData;
	// each index relates to a vertex in m_positionData which will be drawn.
	std::vector<unsigned int> m_indices;

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
	Mesh2D(const std::vector<glm::vec2> &positionData);
	// Creates a 2d mesh with the position and index data, black colour and configures the interal
	// buffers and array correctly
	Mesh2D(const std::vector<glm::vec2> &positionData, const std::vector<unsigned int> &indices);
	~Mesh2D();

	// Delete all current positions vertex data and uses the new positions data.
	// Reconfigures the interal buffers and arrays.
	void UpdatePositionVertices(const std::vector<glm::vec2> &positionData);
	// Deletes all current indices data and uses the new indices data. Reconfigures
	// all internal buffers and array
	void UpdateIndices(const std::vector<unsigned int> &indices);

	// Checks if the currently stored index data is compatible with the
	// currently stored position data.
	bool isValidIndices() const;

	// Returns the amount of indices stored by the mesh.
	size_t GetIndicesCount() const;
	// Returns the amount of vertices stored by the internal vertex array.
	size_t GetVertexCount() const;

	// Returns the ID of the index buffer used by this objects that opengl assigns.
	void BindIndexBuffer() const;
	// Binds the internally stored VAO to be the current VAO used by opengl.
	void BindVAO() const;

	bool operator==(const Mesh2D &rhs) const;
	bool operator!=(const Mesh2D &rhs) const;
};

#endif
