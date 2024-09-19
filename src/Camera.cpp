#include "Camera.h"

#include <iostream>

void Camera::ZoomOut() {
	m_fov += 1.0f;
	if (m_fov >= MAX_FOV) m_fov = MAX_FOV;
	m_cameraSpeed = (m_fov / 45.0f) * MIN_CAM_SPEED;
}
void Camera::ZoomIn() {
	m_fov -= 1.0f;
	if (m_fov <= MIN_FOV) m_fov = MIN_FOV;
	m_cameraSpeed = (m_fov / 45.0f) * MIN_CAM_SPEED;
}

Camera::Camera() {
	m_cameraPos = glm::vec3(0.0f, 0.0f, -10.0f);
	m_cameraSpeed = MIN_CAM_SPEED;
	m_fov = 45.0f;
}

void Camera::Update(const ShaderProgram &shader, const Window &window) {
	shader.SetMatrix4("view", GetViewMatrix());
	shader.SetMatrix4("projection", GetProjectionMatrix(window.GetWidth(), window.GetHeight()));
}


glm::mat4 Camera::GetViewMatrix() const {
	// view matrix does some stuff that should simulate a camera hopefully.
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, m_cameraPos);
	return view;
}
glm::mat4 Camera::GetProjectionMatrix(const float width, const float height) const {
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(m_fov), width / height, 0.1f, 100.0f);
	return projection;
}

void Camera::ProcessKeyboardMovement(Keys keyPressed, const float deltaTime) {
	// WASD move in that direction, Q zooms out and E zooms in.
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


glm::vec2 Camera::ScreenToWorld(const int x, const int y, const Window &window) const {
	// normalised screen coordinates between -1 and 1.
	float nx = (2 * ((float)x / (float)window.GetWidth())) - 1;
	float ny = -((2 * ((float)y / (float)window.GetHeight())) - 1);
	// I GENUINELY HAVE NO IDEA WHY MULTIPLYING THE NORMALISED COORDS BY 50 WORKS 
	// BUT IT WORKS SO I WONT CHANGE IT.
	glm::vec4 coords = { nx*50, ny*50, 0.0f, 1.0f };
	// std::cout << "Normalised coords: " << nx << ", " << ny << std::endl;

	// dont know what im doing so going to copy this.
	// https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords
	glm::mat4 invMat = glm::inverse(GetProjectionMatrix(window.GetWidth(), window.GetHeight()) * GetViewMatrix());

	glm::vec4 pos = invMat * coords;
	pos /= pos.w;
	// std::cout << "pos: " << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;
	
	return { pos.x, pos.y };
}
