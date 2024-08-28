#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 aColor;

out vec4 vertexColor;

uniform mat4 transform;

void main() {
	vertexColor = vec4(aColor, 1.0f);
	gl_Position = transform * vec4(position, 1.0f, 1.0f);
}
