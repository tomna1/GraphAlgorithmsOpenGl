#include "VertexArray.h"

#include <iostream>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_renderer_ID);
	m_attributes = {};
}

VertexArray::VertexArray(const VertexBuffer &vb, const VertexArrayLayout &layout) {
	glGenVertexArrays(1, &m_renderer_ID);

	AddLayout(vb, layout);
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

void VertexArray::AddLayout(const VertexBuffer &vb, const VertexArrayLayout &layout) {
	vb.Bind();
	Bind();

	const std::vector<VertexAttribute> &elements = layout.GetElements();
	// Specifies the amount of bytes to a certain attribute in the layout.
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const VertexAttribute &element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void *)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexAttribute::GetSizeOfType(element.type);
	}
}
