#version 330 core
in vec3 _position;
in vec3 _color;
in vec2 _texCoord;

out vec3 ourColor;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(_position, 1.0f);
	ourColor = _color;
	// texCoord = _texCoord;
	texCoord = vec2(_texCoord.x, 1.0 - _texCoord.y);
}
