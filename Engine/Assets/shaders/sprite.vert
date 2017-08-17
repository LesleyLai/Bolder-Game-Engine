#version 330 core
uniform mat4 Projection;
uniform mat4 View = mat4(1);
uniform mat4 Model = mat4(1);

layout (location = 0) in vec3 position;


void main() {
    gl_Position = vec4(position, 1);
    //gl_Position = Projection * vec4(position, 1);
}
