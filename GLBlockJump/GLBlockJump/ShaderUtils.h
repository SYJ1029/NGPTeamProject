#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include "stdafx.h"

extern GLuint shaderProgramID;
extern GLuint vertexShader;
extern GLuint fragmentShader;

// ������ �о� ���ڿ��� ��ȯ
char* filetobuf(const char* file);

// ���̴� ���� �Լ�
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();

#endif