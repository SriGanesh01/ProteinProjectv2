
#version 430 core
    
in vec3 bColor;
    
out vec4 color;
    
void main() {
    color = vec4(bColor, 1.0f);
}