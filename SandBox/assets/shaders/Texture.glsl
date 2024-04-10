#type pixel
#version 460 core

layout(location = 0) out vec4 colour;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	colour = texture(u_Texture, v_TexCoord);
}

#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = vec4(a_Position, 1.0);
}