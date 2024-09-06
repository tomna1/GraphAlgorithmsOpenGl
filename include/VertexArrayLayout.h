#ifndef VERTEX_ARRAY_LAYOUT_H
#define VERTEX_ARRAY_LAYOUT_H

#include <GL/glew.h>

#include <vector>

/**
* A vertex attribute is one part of a vertex that are stored in the vertex buffer.
* A vertex attribute consits of a type, the amount of components within the attribute
* and whether the data is already normalised or not.
*/
struct VertexAttribute {
	// The type of the attribute (GL_FLOAT, GL_UNSIGNED_INT)
	unsigned int type;
	// The amount of components in the vertex attribute. Must be 1, 2, 3 or 4.
	int count;
	// Specifies whether the data should be normalised or not (GL_FALSE OR GL_TRUE).
	unsigned char normalised;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

/**
* A vertex array layout is used to configure the layout of a vertex array.
* Vertex attributes can be added to the layout and once all attributes are
* added, the layout can be added to a vertex array.
*/
class VertexArrayLayout {
private:
	// The amount of bytes between each consecutive vertex in the vertex buffer.
	unsigned int m_stride;

	// The attributes specified by the layout
	std::vector<VertexAttribute> m_elements;

public:
	VertexArrayLayout();
	~VertexArrayLayout();

	// Returns the elements of the layout.
	std::vector<VertexAttribute> GetElements() const;

	// Gets the stride specified by the vertex layout. The stride is the amount
	// of bytes between each consecutive vertex.
	unsigned int GetStride() const;
	
	// Adds an attribute to the vertex layout. type is type of attribute 
	// (GL_FLOAT, GL_UNSIGNED_CHAR). count is numbers of components in attribute
	// and must be 1, 2, 3 or 4. normalised specifies whether the data should
	// be normalised or not.
	void AddAttribute(unsigned int type, int count, unsigned char normalised);

	// Adds an attribute to this vertex array layout.
	// attibute is the attribute to add.
	void AddAttribute(const VertexAttribute &attribute);
};

#endif
