#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;

uniform vec3 view_pos;

void main()
{
    vec3 normalized_normal = normalize(normal);

    vec3 light_direction = normalize(light.position - frag_pos);
    vec3 view_direction = normalize(view_pos - frag_pos);
    vec3 reflect_direction = reflect(-light_direction, normalized_normal);

    float diff = max(dot(normalized_normal, light_direction), 0.0);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);


    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular); 

    vec3 result = ambient + diffuse + specular;

    frag_color = vec4(result, 1.0);
}
