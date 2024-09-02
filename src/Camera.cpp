#include "Camera.h"

#include <iostream>

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

glm::mat4 Camera::getViewMatrix() {
	// view matrix does some stuff that should simulate a camera hopefully.
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, m_cameraPos);
	return view;
}

void Camera::ProcessKeyboardMovement(Keys keyPressed, float deltaTime) {
	float velocity = m_cameraSpeed * deltaTime;
	if (keyPressed == W) m_cameraPos -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	if (keyPressed == A) m_cameraPos += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	if (keyPressed == S) m_cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	if (keyPressed == D) m_cameraPos -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	if (keyPressed == Q) ZoomOut();
	if (keyPressed == E) ZoomIn();
}