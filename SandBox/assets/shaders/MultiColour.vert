#version 450 core


layout(location = 0) in mat4 a_Normal;
layout(location = 4) in vec3 a_Position;

layout(std140, binding = 0) uniform VertUBO
{
	mat4 u_MVP;
} vertUBO;

layout (push_constant) uniform VertPushConsts
{
	mat4 u_Transform;
} vertPushConsts;


//layout(location = 2) uniform mat4 u_MVP;
//layout(location = 3) uniform mat4 u_Transform;

void main()
{
	gl_Position = vertUBO.u_MVP * vertPushConsts.u_Transform * vec4(a_Position, 1.0);
}
