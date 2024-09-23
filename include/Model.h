#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include <string>

// A model consists of a mesh and all other data required to be able to render
// the model onto the screen
class Model2D {
private:
	// Used to access the mesh which is stored in the resource manager.
	std::string m_meshName;
	// Contains all information about the position of an object in a scene.
	glm::vec2 m_position;
	// Whether the objects if selected or not.
	bool m_isSelected;

	// UNUSED FOR NOW.
	float m_scale;

public:
	Model2D();
	Model2D(std::string &meshName, float posX, float posY);

	// Selects the model.
	void Select();
	// Deselects the model.
	void DeSelect();
	// Returns true if the model is selected and false if not.
	bool isSelected() const;

	// Sets the position of the model.
	void SetPos(float x, float y);
	// Gets the X coordinate of the model.
	float GetX() const;
	// Gets the Y Coordinate of the mode.
	float GetY() const;
	// Returns a model matrix that can be used for drawing the object.
	glm::mat4 GetModelMatrix() const;

	// Sets the name of the mesh
	void SetMeshName(const std::string &name);

	std::string GetMeshName() const;

	bool operator==(const Model2D &rhs) const;
	bool operator!=(const Model2D &rhs) const;
};


#endif
