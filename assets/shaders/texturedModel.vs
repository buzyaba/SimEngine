#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoord;

uniform mat4 vp;

void main(){
    gl_Position = vp * instanceMatrix *vec4(position, 1.0);
    TexCoord = texCoord;
}