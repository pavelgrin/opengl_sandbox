#version 330 core
out vec4 frag_color;

// in vec2 tex_coord;

// uniform sampler2D texture0;
// uniform sampler2D texture1;

uniform vec3 object_color;
uniform vec3 light_color;

void main()
{
    // frag_color = mix(texture(texture0, tex_coord), texture(texture1, tex_coord), 0.2);
    frag_color = vec4(light_color * object_color, 1.0);
}
