#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal; // 정점 노말 추가
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 vTexCoord;

out vec3 fragColor;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalMatrix; // main.cpp에서 전달된 normalMatrix

void main()
{
    // Transform positions
    FragPos = vec3(modelTransform * vec4(position, 1.0));
    Normal = normalize(normalMatrix * normal);
    fragColor = color; // 정점 색상 전달
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(position, 1.0);

    TexCoord = vTexCoord;
}