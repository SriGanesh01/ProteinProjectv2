
#version 330 core
    
in vec3 bPos;
    
out vec4 color;
    
void main() {
    vec3 colorValue = bPos + vec3(0.5);
    color = vec4(colorValue, 1.0f);
}