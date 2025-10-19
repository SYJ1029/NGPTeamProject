#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include "stdafx.h"

extern GLuint shaderProgramID;
extern GLuint vertexShader;
extern GLuint fragmentShader;

// 파일을 읽어 문자열로 반환
char* filetobuf(const char* file);

// 셰이더 관련 함수
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();

#endif