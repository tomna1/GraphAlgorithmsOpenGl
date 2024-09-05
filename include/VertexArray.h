#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>

#include "VertexBuffer.h"
#include "VertexArrayLayout.h"

class VertexArray {
private:
	// The unique ID given to this vertex array by opengl.
	unsigned int m_renderer_ID;

	// Stores all the data about the attributes.
	std::vector<VertexAttribute> m_attributes;
public:
	VertexArray();
	~VertexArray();

	// Binds this array to be the current vertex array
	void Bind() const;
	// Unbinds this vertex array.
	void Unbind() const;

	// Adds an attribute to this vertex array. VB is the buffer whose attributes
	// will be specified and layout is the layout to add.
	void AddLayout(const VertexBuffer &vb, const VertexArrayLayout &layout);
};


#endif
