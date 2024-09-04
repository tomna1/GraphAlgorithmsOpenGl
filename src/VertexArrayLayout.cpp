#include "VertexArrayLayout.h"

VertexArrayLayout::VertexArrayLayout() {
	m_stride = 0;
	m_elements = {};
}

VertexArrayLayout::~VertexArrayLayout() {
}

std::vector<VertexAttribute> VertexArrayLayout::getElements() const {
	return m_elements;
}

unsigned int VertexArrayLayout::getStride() const {
	return m_stride;
}

void VertexArrayLayout::addAttribute(const VertexAttribute &attribute) {
	m_elements.push_back(attribute);
	m_stride += (attribute.count * VertexAttribute::getSizeOfType(attribute.type));
}
