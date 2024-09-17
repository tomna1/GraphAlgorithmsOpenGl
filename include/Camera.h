#ifndef CAMERA_OPENGL_H
#define CAMERA_OPENGL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Display.h"

// DONT CHANGE, STUFF STARTS DISAPPEARING IF CAMERA GOES TOO FAR OUT. DONT
// KNOW HOW TO FIX.
const float MAX_FOV = 140.0f;
const float MIN_FOV = 15.0f;

const float MAX_CAM_SPEED = 160.0f;
const float MIN_CAM_SPEED = 16.0f;

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

	// field of view used for the projection matrix. The larger the fov,
	// the more of the world can be seen.
	float m_fov;

	// This camera will only be 2d and not have any 3d movement.
	glm::vec3 m_cameraPos;

	// Zooms the camera out, max zoom distance is defined by MAX_Z_DISTANCE.
	void ZoomOut();
	// Zooms the camera in, max zoom distance is defined by MIN_Z_DISTANCE.
	void ZoomIn();

public:
	// Creates a camera at the origin with default speed.
	Camera();
	// Creates a camera at a the origin at the given speed.
	Camera(float speed);

	// Gets the view matrix defined by the position of the camera.
	glm::mat4 GetViewMatrix() const;

	// A projection matrix does some stuff with perspective honestly im not sure. 
	// Returns the matrix.
	glm::mat4 GetProjectionMatrix(const float width, const float height) const;

	// Will move the camera or zoom it in or out depending on the key pressed
	// and the length of time between the last frame.
	void ProcessKeyboardMovement(Keys keyPressed, float deltaTime);

	// Returns the x coordinate the camera is centred around.
	float GetX() const;
	// Returns the Y coordinate the camera is centred around.
	float GetY() const;
	// Returns the Z coordinate (zoom distance) the camera is centred around. 
	float GetZ() const;

	// Returns the coordinates of where the mouse is hovering over based on the
	// camera being used and its coordinates.
	glm::vec2 ScreenToWorld(int x, int y, const Display &display);
};

#endif
