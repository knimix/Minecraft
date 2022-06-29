#vertex
#version 430 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;



void main() {
    gl_Position =  projection * view * model * vec4(position, 1.0f);
}


#fragment
#version 430 core


out vec4 OutColor;

void main(){
    OutColor = vec4(1);
}
