#ifndef CAMERA_OPENGL_H
#define CAMERA_OPENGL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// DONT CHANGE, STUFF STARTS DISAPPEARING IDK WHY.
const float MAX_Z_DISTANCE = -80.0;
const float MIN_Z_DISTANCE = -5.0;

const float MAX_CAM_SPEED = 160.0f;
const float MIN_CAM_SPEED = 8.0f;

enum Keys {
	W,	// move camera up
	A,	// move camera left
	S,	// move camera down
	D,	// move camera right
	Q,	// zoom out
	E	// zoom in
};

class Camera {
private:
	// The speed the camera moves
	float m_cameraSpeed;

	// This camera will only be 2d and not have any 3d movement
	glm::vec3 m_cameraPos;

	void ZoomOut();
	void ZoomIn();

public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, float speed);

	// Gets the view matrix defined by the camera position vector.
	glm::mat4 getViewMatrix();

	void ProcessKeyboardMovement(Keys keyPressed, float deltaTime);
};

#endif
