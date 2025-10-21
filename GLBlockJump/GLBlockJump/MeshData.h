#pragma once
#include "stdafx.h"

extern const GLfloat cubeVertices[8][3];
extern const GLfloat cubeNormal[8][3];
extern const GLfloat cubeColors[8][3];
extern const GLfloat cubeTextures[8][2];

extern const GLfloat lightbeamVertices[8][3];
extern const GLfloat lightbeamNormal[8][3];

extern const GLfloat startlightbeamColors[8][4];
extern const GLfloat endlightbeamColors[8][4];
extern const GLfloat texlightbeam[8][2];

extern const GLuint cubeIndices[36];
extern float vertices[216];

extern const GLfloat floorVertices[4][3];
extern const GLfloat floorNormal[4][3];
extern const GLfloat floor_color[4][3];
extern const GLfloat texfloor[4][2];
extern const GLuint sq_index[6];

struct OBB {
    glm::vec3 center;      // 중심 좌표
    glm::vec3 halfSize;    // 각 축 방향 절반 크기 (width/2, height/2, depth/2)
    glm::vec3 axis[3];     // 로컬 축 (X, Y, Z) ? 회전 포함
};