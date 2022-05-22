#version 330 core

struct Material {
    // vec3 ambient;
    // vec3 diffuse;
    // vec3 specular;
    sampler2D diffuse;
    sampler2D specular;
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
in vec2 tex_coords;

uniform vec3 view_pos;

void main()
{
    vec3 normalized_normal = normalize(normal);

    vec3 light_direction = normalize(light.position - frag_pos);
    vec3 view_direction = normalize(view_pos - frag_pos);
    vec3 reflect_direction = reflect(-light_direction, normalized_normal);

    float diff = max(dot(normalized_normal, light_direction), 0.0);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    // vec3 ambient_color = material.ambient;
    // vec3 diffuse_color = material.diffuse;
    // vec3 specular_color = material.specular;

    vec3 ambient_color = vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse_color = ambient_color;
    vec3 specular_color = vec3(texture(material.specular, tex_coords));;

    vec3 ambient = light.ambient * ambient_color;
    vec3 diffuse = light.diffuse * (diff * diffuse_color);  
    vec3 specular = light.specular * (spec * specular_color); 

    vec3 result = ambient + diffuse + specular;

    frag_color = vec4(result, 1.0);
}
