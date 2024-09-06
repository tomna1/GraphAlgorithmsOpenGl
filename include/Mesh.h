#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"

class Mesh {
private:
	float *m_vertices;
	unsigned int *m_indices;

	unsigned int m_verticesSize;
	unsigned int m_indicesSize;
};

#endif
