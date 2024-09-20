#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Mesh.h"

#include <map>
#include <string>


// The resource manager is responsible for storing all meshes and handing out
// IDs that can be used to reference the meshes stored.
class ResourceManager {
private:
	// Contains all the meshes.
	std::map<std::string, Mesh2D> m_meshes;

public:
	// Empty managers with no stored meshes.
	ResourceManager();

	// Adds a mesh to the resource Manager. Will not add the mesh if a mesh
	// with that name already exists in the resource manager.
	 void AddMesh(const std::string &name, const Mesh2D &mesh);
	 // Remove a mesh from the resource manager. 
	 void RemoveMesh(const std::string &name);

	 void Clear();

	 void BindMeshVAO(const std::string &name) const;
	 void BindMeshIndexBuffer(const std::string &name) const;

	 size_t GetMeshIndicesCount(const std::string &name) const;
	 size_t GetMeshVertexCount(const std::string &name) const;

	 // Returns a pointer to the mesh associated with that string. Will
	 // return a nullptr if not found.
	 const Mesh2D *GetMesh(const std::string &name) const;

	 // Returns true if the resource manager already contains a mesh with the name.
	 bool Contains(const std::string &name);
	 // Returns the amount of meshes stored by the resource manager.
	 size_t GetMeshCount() const;
};

#endif