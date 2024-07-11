#version 450 core

layout(location = 0) out vec4 colour;

layout(std140, binding = 1) uniform UBO
{
	mat4 transform;
	vec4 colour;
} data;

// layout(location = 1) uniform vec4 u_Colour;

void main()
{
	colour = data.colour;
}