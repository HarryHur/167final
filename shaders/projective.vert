# version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 viewLS;
uniform mat4 projectionLS;

out vec4 position;
out vec4 positionLS;
out vec3 normal;

void main(){
    position = vec4(vertex_position, 1.0f );
    gl_Position = projection * view * model * position;
    // forward the raw position and normal in the model coord to frag shader
    normal = vertex_normal;
    positionLS = projectionLS * viewLS * model * position;
}
