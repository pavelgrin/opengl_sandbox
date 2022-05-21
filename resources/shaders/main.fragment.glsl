#version 330 core
out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;

uniform vec3 light_pos;

uniform vec3 object_color;
uniform vec3 light_color;

void main()
{
    vec3 light_direction = normalize(light_pos - frag_pos); 

    float diff = max(dot(normalize(normal), light_direction), 0.0);
    vec3 diffuse = diff * light_color;

    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    vec3 result = (ambient + diffuse) * object_color;

    frag_color = vec4(result, 1.0);
}
