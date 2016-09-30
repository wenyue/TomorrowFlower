#version 330 core
in vec3 TF_position;

uniform mat4 TF_projection;
uniform mat4 TF_view;
uniform mat4 TF_model;

void main()
{
	gl_Position = TF_projection * view * model * vec4(_position, 1.0f);
}
