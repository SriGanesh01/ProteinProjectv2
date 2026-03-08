
#version 430 core
    
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aOffset;
    

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
    
void main() {
    gl_Position = proj * view * model * vec4(aPos + aOffset, 1.0f);
} 