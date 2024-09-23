#ifndef SCENE_H
#define SCENE_H

// The renderer should only be allowed to render a scene.

#include "ResourceManager.h"
#include "Model.h"

#include <vector>

// Each scene contains models that are stored in the scene and a resource
// manager to manage the meshes that those models use.
class Scene {
private:
	std::vector<Model2D> m_models;
	ResourceManager m_manager;
	// The index of the selected model in m_models.
	std::vector<int> m_selectedModels;

public:
	Scene();

	void AddMesh(const std::string &name, const Mesh2D &mesh);
	void DeleteMesh(const std::string &name);

	void BindMeshVAO(const std::string &name) const;
	void BindMeshIndexBuffer(const std::string &name) const;

	size_t GetMeshIndicesCount(const std::string &name) const;
	size_t GetMeshVertexCount(const std::string &name) const;

	void Clear();
	void ClearModels();
	void ClearMeshes();

	// Adds a model to the scene.
	void AddModel(Model2D &model);
	// Remove a model from the scene.
	void RemoveModel(const Model2D &model);
	// Returns the amount of models currently stored by the scene.
	size_t GetModelCount() const;


	void SelectModelAtPoint(float x, float y);
	void DeselectModelAtPoint(float x, float y);
	void DeselectAllModels();

	size_t GetSelectedModelCount() const;

	std::vector<Model2D>::iterator Begin();
	std::vector<Model2D>::iterator End();
};


#endif