#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal; // ���� �븻 �߰�
layout(location = 2) in vec3 color;

out vec3 fragColor;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normalMatrix; // main.cpp���� ���޵� normalMatrix

void main()
{
    // Transform positions
    FragPos = vec3(modelTransform * vec4(position, 1.0));
    Normal = normalize(normalMatrix * normal);
    fragColor = color; // ���� ���� ����
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(position, 1.0);
}