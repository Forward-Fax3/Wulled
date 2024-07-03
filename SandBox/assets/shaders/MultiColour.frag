#version 450 core

layout(location = 0) out vec4 colour;

layout(push_constant) uniform PixelPushConst
{
	vec4 u_Colour;
} pixelMatrix;

// layout(location = 1) uniform vec4 u_Colour;

void main()
{
	colour = pixelMatrix.u_Colour;
}