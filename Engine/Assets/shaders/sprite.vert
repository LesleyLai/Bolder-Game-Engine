#version 330 core
uniform mat4 projection;
uniform mat4 model = mat4(1);

layout (location = 0) in vec3 position;

void main() {
    gl_Position = projection * model * vec4(position, 1);
}
