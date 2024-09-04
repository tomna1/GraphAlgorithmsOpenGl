#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenBuffers(1, &m_renderer_ID);
	m_attributes = {};
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_renderer_ID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_renderer_ID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addLayout(const VertexBuffer &vb, const VertexArrayLayout &layout) {
	vb.Bind();

	const std::vector<VertexAttribute> &elements = layout.getElements();
	// Specifies the amount of bytes to a certain attribute in the layout.
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const VertexAttribute &element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void *)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexAttribute::getSizeOfType(element.type);
	}
}
