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

Camera::Camera(float speed) {
	m_cameraPos = glm::vec3(0.0f, 0.0f, -10.0f);
	if (speed < MIN_CAM_SPEED) m_cameraSpeed = MIN_CAM_SPEED;
	if (speed > MAX_CAM_SPEED) m_cameraSpeed = MAX_CAM_SPEED;
	else m_cameraSpeed = speed;
	m_fov = 45.0f;
}


glm::mat4 Camera::GetViewMatrix() const {
	// view matrix does some stuff that should simulate a camera hopefully.
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, m_cameraPos);
	return view;
}
glm::mat4 Camera::GetProjectionMatrix(Display &display) const {
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(m_fov), (float)(display.GetWidth() / display.GetHeight()), 0.1f, 100.0f);
	return projection;
}

void Camera::ProcessKeyboardMovement(Keys keyPressed, float deltaTime) {
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


glm::vec2 Camera::ScreenToWorld(int x, int y, glm::mat4 projection) {
	// coordindates multiplied by the view matrix then the then the projection matrix creates normalised screen coordinates.

	// that must mean some inverse stuff is true.
	// 3rd value is screen. width, 4th value is screen height.
	int screenSize[4] = { 1, 2, 3, 4 };
	

	// normalised screen coordinates between -1 and 1.
	float nx = (2 * ((float)x / (float)screenSize[2])) - 1;
	float ny = -((2 * ((float)y / (float)screenSize[3])) - 1);
	glm::vec4 coords = { nx, ny, 0.0f, 1.0f };
	// std::cout << "Normalised coords: " << nx << ", " << ny << std::endl;

	// dont know what im doing so going to copy this.
	// https://www.reddit.com/r/gamedev/comments/10izurv/screen_to_world_coordinates/
	glm::mat4 invProj = glm::inverse(projection);
	glm::mat4 invView = glm::inverse(GetViewMatrix());
	glm::mat4 idkinv2 = invProj * invView;

	glm::mat4 idk = projection * GetViewMatrix();
	glm::mat4 idkinv = glm::inverse(idk);

	// auto pos = idk * coords;
	// pos /= pos.w;
	// std::cout << "pos: " << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;
	
	
	glm::vec4 viewSpace = invProj * coords;
	// std::cout << "viewSpace: " << viewSpace.x << "," << viewSpace.y << "," << viewSpace.z << "," << viewSpace.w << std::endl;
	glm::vec4 worldSpace = invView * viewSpace;
	worldSpace /= worldSpace.w;
	// std::cout << "worldSpace: " << worldSpace.x << "," << worldSpace.y << "," << worldSpace.z << "," << worldSpace.w << std::endl;

	// THIS NEARLY WORKS BUT ONLY WHEN I MOVE AROUND USING THE WASD KEYS, IF I MOVE THE MOUSE
	// IT DOES NOT SHOW THE CORRECT COORDINATES.


	// std::cout << "pos: " << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;

	

	return { 0, 0 };
}
