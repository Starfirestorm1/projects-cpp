#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform float aShift;
out vec2 TexCoord;
out vec3 Pos;
uniform mat4 transform;
void main()
{
    TexCoord = aTexCoord;
    Pos = aPos;
    gl_Position = transform * vec4(aPos, 1.0);
}
