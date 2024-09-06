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

void VertexArrayLayout::AddAttribute(const unsigned int type, const int count, const unsigned char normalised) {
	VertexAttribute attrib;
	attrib.type = type;
	attrib.count = count;
	attrib.normalised = normalised;
	m_elements.push_back(attrib);
	m_stride += (attrib.count * VertexAttribute::GetSizeOfType(attrib.type));
}

void VertexArrayLayout::AddAttribute(const VertexAttribute &attribute) {
	m_elements.push_back(attribute);
	m_stride += (attribute.count * VertexAttribute::GetSizeOfType(attribute.type));
}
