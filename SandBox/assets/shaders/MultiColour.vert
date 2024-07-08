#version 450 core


layout(location = 0) in vec3 a_Position;

layout(std140, binding = 0) uniform MVP
{
	mat4 MVP;
} mvp;

layout(std140, binding = 1) uniform UBO
{
	mat4 transform;
	vec4 colour;
} data;

void main()
{
	gl_Position = mvp.MVP * data.transform * vec4(a_Position, 1.0);
}
