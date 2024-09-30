#include "Scene.h"

#include <iostream>

Scene::Scene() {
	m_models = {};
	m_manager = ResourceManager();
	m_selectedModels = {};
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

void Scene::SelectModelAtPoint(float x, float y) {
	// Checks all models in m_models for the one at the point.
	for (int i = 0; i < m_models.size(); i++) {
		if (m_models[i].GetX() == x && m_models[i].GetY() == y) {
			m_models[i].Select();
			m_selectedModels.push_back(m_models[i]);
			return;
		}
	}
	
}

void Scene::DeselectModelAtPoint(float x, float y) {
	for (int i = 0; i < m_models.size(); i++) {
		if (m_models[i].GetX() == x && m_models[i].GetY() == y) {
			m_models[i].DeSelect();
			
			// removes model from selected models.
			auto it = m_selectedModels.begin();
			while (*it != m_models[i]) {
				it++;
			}
			m_selectedModels.erase(it);
			return;
		}
	}
}

void Scene::DeselectAllModels() {
	for (int i = 0; i < m_models.size(); i++) {
		m_models[i].DeSelect();
	}
	while (m_selectedModels.size() > 0) {
		m_selectedModels.erase(m_selectedModels.begin());
	}
}

void Scene::DeselectLastModelSelected(unsigned int index) {
	if (index + 1 > m_selectedModels.size()) return;


	Model2D &model = m_selectedModels[m_selectedModels.size() - 1 - index];
	DeselectModelAtPoint(model.GetX(), model.GetY());
}

size_t Scene::GetSelectedModelCount() const {
	return m_selectedModels.size();
}


std::vector<Model2D>::iterator Scene::Begin() {
	return m_models.begin();
}

std::vector<Model2D>::iterator Scene::End() {
	return m_models.end();
}


