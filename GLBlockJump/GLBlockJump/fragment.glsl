#version 330 core

in vec3 fragColor; // Vertex Shader���� ���޹��� ����
in vec3 Normal;
in vec3 FragPos; // Vertex Shader���� ���޹���

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float ambientLight; // ȯ�汤 ����
uniform float alpha;        // ������ ���� ������ ����

void main()
{
    // Normalize vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Ambient lighting
    vec3 ambient = ambientLight * lightColor;

    // Diffuse lighting (���� ���� ����)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    int shininess = 128;
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float specularLight = max (dot (viewDir, reflectDir), 0.0);
    specularLight = pow(specularLight, shininess);
    vec3 specular = specularLight * lightColor;

    // Combine results with the object's original color
    vec3 result = (ambient + diffuse + specular) * fragColor; // ����� ���� ���� ����
    color = vec4(result, alpha);
    //color = vec4(norm * 0.5 + 0.5, 1.0);
}