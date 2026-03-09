
#version 430 core
    
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aOffset;
layout(location = 3) in vec3 aColor;
layout(location = 4) in float aScale;

out vec3 bColor;
    

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
    
void main() {
    gl_Position = proj * view * model * vec4((aPos * aScale) + aOffset, 1.0f);
    bColor = aColor;
} 