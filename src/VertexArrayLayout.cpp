#include "VertexArrayLayout.h"

VertexArrayLayout::VertexArrayLayout() {
	m_stride = 0;
	m_elements = {};
}

VertexArrayLayout::~VertexArrayLayout() {
}

std::vector<VertexAttribute> VertexArrayLayout::GetElements() const {
	return m_elements;
}

unsigned int VertexArrayLayout::GetStride() const {
	return m_stride;
}

void VertexArrayLayout::AddAttribute(const VertexAttribute &attribute) {
	m_elements.push_back(attribute);
	m_stride += (attribute.count * VertexAttribute::GetSizeOfType(attribute.type));
}
