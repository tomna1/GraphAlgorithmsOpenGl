#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "IndexBuffer.h"

class Mesh {
private:

	// A configured va should contain all information about the vertex data of the mesh.
	VertexArray m_va;
	// The index buffer is used to draw the mesh.
	IndexBuffer m_ib;

public:
	Mesh(VertexArray &va, IndexBuffer &ib);
};

#endif
