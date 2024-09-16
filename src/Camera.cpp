#include "Camera.h"

#include <GL/glew.h>


#include <iostream>

#define DISPLAY_WIDTH = 1920
#define DISPLAY_HEIGHT = 1080

void Camera::ZoomOut() {
	float z = m_cameraPos.z;
	if (z < MAX_Z_DISTANCE) return;
	m_cameraPos += glm::vec3(0.0f, 0.0f, -1.0f);
	if (m_cameraSpeed >= MAX_CAM_SPEED) return;
	m_cameraSpeed += MIN_CAM_SPEED/10;
}

void Camera::ZoomIn() {
	float z = m_cameraPos.z;
	if (z > MIN_Z_DISTANCE) return;
	m_cameraPos += glm::vec3(0.0f, 0.0f, 1.0f);
	if (m_cameraSpeed <= MIN_CAM_SPEED) return;
	m_cameraSpeed -= MIN_CAM_SPEED/10;
}

Camera::Camera() {
	m_cameraPos = glm::vec3(0.0f, 0.0f, MIN_Z_DISTANCE);
	m_cameraSpeed = MIN_CAM_SPEED;
}

Camera::Camera(glm::vec3 position) {
	if (position.z < MIN_Z_DISTANCE) m_cameraPos = glm::vec3(position.x, position.y, MIN_Z_DISTANCE);
	else m_cameraPos = position;
	m_cameraSpeed = MIN_CAM_SPEED;
}

Camera::Camera(glm::vec3 position, float speed) {
	if (position.z < MIN_Z_DISTANCE) m_cameraPos = glm::vec3(position.x, position.y, MIN_Z_DISTANCE);
	else m_cameraPos = position;
	
	if (speed < MIN_CAM_SPEED) m_cameraSpeed = MIN_CAM_SPEED;
	else m_cameraSpeed = speed;
}

glm::mat4 Camera::GetViewMatrix() const {
	// view matrix does some stuff that should simulate a camera hopefully.
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, m_cameraPos);
	return view;
}

void Camera::ProcessKeyboardMovement(Keys keyPressed, float deltaTime) {
	float velocity = m_cameraSpeed * deltaTime;
	if (keyPressed == Keys::W_KEY) m_cameraPos -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	else if (keyPressed == Keys::A_KEY) m_cameraPos += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	else if (keyPressed == Keys::S_KEY) m_cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	else if (keyPressed == Keys::D_KEY) m_cameraPos -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	else if (keyPressed == Keys::Q_KEY) ZoomOut();
	else if (keyPressed == Keys::E_KEY) ZoomIn();
}


float Camera::GetX() const {
	return m_cameraPos.x;
}
float Camera::GetY() const {
	return m_cameraPos.y;
}
float Camera::GetZ() const {
	return m_cameraPos.z;
}


glm::vec2 Camera::ScreenToWorld(int x, int y, glm::mat4 projection) {
	// coordindates multiplied by the view matrix then the then the projection matrix creates normalised screen coordinates.

	// that must mean some inverse stuff is true.
	// 3rd value is screen. width, 4th value is screen height.
	int screenSize[4];
	glGetIntegerv(GL_VIEWPORT, screenSize);

	// normalised screen coordinates between -1 and 1.
	float nx = (2 * ((float)x / (float)screenSize[2])) - 1;
	float ny = -((2 * ((float)y / (float)screenSize[3])) - 1);
	// std::cout << "Normalised coords: " << nx << ", " << ny << std::endl;

	// dont know what im doing so going to copy this.
	// https://www.reddit.com/r/gamedev/comments/10izurv/screen_to_world_coordinates/
	glm::mat4 invProj = glm::inverse(projection);
	glm::mat4 invView = glm::inverse(GetViewMatrix());

	glm::mat4 idk = projection * GetViewMatrix();
	glm::mat4 idkinv = glm::inverse(idk);

	glm::vec4 coords = { (float)nx, (float)ny, 0.0f, 1.0f };

	auto pos = idkinv * coords;
	
	
	
	//glm::vec4 viewSpace = invProj * coords;
	// std::cout << "viewSpace: " << viewSpace.x << "," << viewSpace.y << "," << viewSpace.z << "," << viewSpace.w << std::endl;
	//glm::vec4 worldSpace = invView * viewSpace;
	// std::cout << "worldSpace: " << worldSpace.x << "," << worldSpace.y << "," << worldSpace.z << "," << worldSpace.w << std::endl;


	std::cout << "pos: " << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;

	

	return { pos.x, pos.y };
}
