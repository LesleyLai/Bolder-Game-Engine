#version 330 core
uniform mat4 projection;
uniform mat4 model = mat4(1);

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord;

out vec3 frag_color;
out vec2 frag_texture_coord;

void main() {
    gl_Position = projection * model * vec4(position, 1);
    frag_texture_coord = texture_coord;
}
