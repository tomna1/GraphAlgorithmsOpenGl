#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 aColor;

out vec4 vertexColor;

void main() {
	vertexColor = vec4(aColor, 1.0f);
	gl_Position = vec4(position, 1.0f, 1.0f);
}
