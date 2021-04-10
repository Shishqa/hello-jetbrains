#version 400 core

layout (location = 0) in vec3 position;
uniform vec2 offset;

void main()
{
    vec4 globalPosition = vec4(position.x, position.y, position.z, 1.0);
    vec4 globalOffset = vec4(offset.x, offset.y, 0.0, 0.0);
    gl_Position = globalPosition + globalOffset;
}

