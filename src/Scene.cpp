#include "Scene.h"

Scene::Scene() {
	m_models = {};
	m_manager = ResourceManager();
}

void Scene::AddMesh(const std::string &name, const Mesh2D &mesh) {
	if (m_manager.Contains(name)) return;
	m_manager.AddMesh(name, mesh);
}

void Scene::DeleteMesh(const std::string &name) {
	m_manager.RemoveMesh(name);
}

void Scene::BindMeshVAO(const std::string &name) const {
	m_manager.BindMeshVAO(name);
}
void Scene::BindMeshIndexBuffer(const std::string &name) const {
	m_manager.BindMeshIndexBuffer(name);
}


size_t Scene::GetMeshIndicesCount(const std::string &name) const {
	return m_manager.GetMeshIndicesCount(name);
}
size_t Scene::GetMeshVertexCount(const std::string &name) const {
	return m_manager.GetMeshVertexCount(name);
}

void Scene::Clear() {
	ClearModels();
	ClearMeshes();
}
void Scene::ClearModels() {
	m_models.resize(0);
}
void Scene::ClearMeshes() {
	m_manager.Clear();
}

void Scene::AddModel(Model2D &model) {
	m_models.push_back(model);
}
void Scene::RemoveModel(const Model2D &model) { 
	for (int i = 0; i < m_models.size(); i++) {
		if (model == m_models[i]) {
			m_models.erase(m_models.begin() + i);
			return;
		}
	}
}
size_t Scene::GetModelCount() const {
	return m_models.size();
}


std::vector<Model2D>::iterator Scene::Begin() {
	return m_models.begin();
}

std::vector<Model2D>::iterator Scene::End() {
	return m_models.end();
}


