#version 330 core

struct Material {
    // vec3 ambient;
    // vec3 diffuse;
    // vec3 specular;
    sampler2D texture_diffuse0;
    sampler2D texture_specular0;
    float shininess;
};

struct Light {
    vec3 position;
    // vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
    // vec3 light_direction = normalize(-light.direction);

    float light_distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * light_distance + 
    		            light.quadratic * (light_distance * light_distance));
    

    vec3 view_direction = normalize(view_pos - frag_pos);
    vec3 reflect_direction = reflect(-light_direction, normalized_normal);

    float diff = max(dot(normalized_normal, light_direction), 0.0);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);

    // vec3 ambient_color = material.ambient;
    // vec3 diffuse_color = material.diffuse;
    // vec3 specular_color = material.specular;

    vec3 ambient_color = vec3(texture(material.texture_diffuse0, tex_coords));
    vec3 diffuse_color = ambient_color;
    vec3 specular_color = vec3(texture(material.texture_specular0, tex_coords));

    vec3 ambient = light.ambient * ambient_color;
    vec3 diffuse = light.diffuse * (diff * diffuse_color);  
    vec3 specular = light.specular * (spec * specular_color);

    vec3 result = (ambient + diffuse + specular) * attenuation;

    frag_color = vec4(result, 1.0);
}
