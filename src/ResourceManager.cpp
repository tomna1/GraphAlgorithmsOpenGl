#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	m_meshes = {};
}

void ResourceManager::AddMesh(const std::string &name, const Mesh2D &mesh) {
	if (m_meshes.count(name) > 0) return;
	m_meshes[name] = mesh;
}

void ResourceManager::RemoveMesh(const std::string &name) {
	if (m_meshes.count(name) == 0) return;
	m_meshes.erase(name);
}

void ResourceManager::Clear() {
	m_meshes.clear();
}

void ResourceManager::BindMeshVAO(const std::string &name) const {
	auto it = m_meshes.find(name);
	if (it == m_meshes.end()) return;
	it->second.BindVAO();
}

void ResourceManager::BindMeshIndexBuffer(const std::string &name) const {
	auto it = m_meshes.find(name);
	if (it == m_meshes.end()) return;
	it->second.BindIndexBuffer();
}

size_t ResourceManager::GetMeshIndicesCount(const std::string &name) const {
	auto it = m_meshes.find(name);
	if (it == m_meshes.end()) return 0;
	return it->second.GetIndicesCount();
}

size_t ResourceManager::GetMeshVertexCount(const std::string &name) const {
	auto it = m_meshes.find(name);
	if (it == m_meshes.end()) return 0;
	return it->second.GetVertexCount();
}

const Mesh2D *ResourceManager::GetMesh(const std::string &name) const {
	if (m_meshes.count(name) == 0) return nullptr;
	auto it = m_meshes.find(name);
	if (it == m_meshes.end()) return nullptr;
	
	const Mesh2D *mesh = &it->second;
	return mesh;
}



bool ResourceManager::Contains(const std::string &name) {
	return m_meshes.count(name) > 0;
}

size_t ResourceManager::GetMeshCount() const {
	return m_meshes.size();
}
