#ifndef CAMERA_OPENGL_H
#define CAMERA_OPENGL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// DONT CHANGE, STUFF STARTS DISAPPEARING IF CAMERA GOES TOO FAR OUT. DONT
// KNOW HOW TO FIX.
const float MAX_Z_DISTANCE = -80.0;
const float MIN_Z_DISTANCE = -5.0;

const float MAX_CAM_SPEED = 160.0f;
const float MIN_CAM_SPEED = 8.0f;

enum class Keys {
	W_KEY,	// move camera up
	A_KEY,	// move camera left
	S_KEY,	// move camera down
	D_KEY,	// move camera right
	Q_KEY,	// zoom out
	E_KEY	// zoom in
};

class Camera {
private:
	// The speed the camera moves.
	float m_cameraSpeed;

	// This camera will only be 2d and not have any 3d movement.
	glm::vec3 m_cameraPos;

	// Zooms the camera out, max zoom distance is defined by MAX_Z_DISTANCE.
	void ZoomOut();
	// Zooms the camera in, max zoom distance is defined by MIN_Z_DISTANCE.
	void ZoomIn();

public:
	// Creates a camera at the origin with default speed.
	Camera();
	// Creates a camera at a given position at a default speed. Will change
	// camera position if the z value is outside of the given MAX_Z_DISTANCE
	// or MIN_Z_DISTANCE.
	Camera(glm::vec3 position);
	// Creates a camera at a given position at the given speed. Will change
	// camera position if the z value is outside of the given MAX_Z_DISTANCE
	// or MIN_Z_DISTANCE.
	Camera(glm::vec3 position, float speed);

	// Gets the view matrix defined by the position of the camera.
	glm::mat4 GetViewMatrix();

	// Will move the camera or zoom it in or out depending on the key pressed
	// and the length of time between the last frame.
	void ProcessKeyboardMovement(Keys keyPressed, float deltaTime);
};

#endif
