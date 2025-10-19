#include "stdafx.h"
#include "BufferInit.h"
#include "MeshData.h"
#include "ShaderUtils.h"
#include "TextureUtils.h"
#include "CameraAndLight.h"

GLuint vaoCube, vboCube[3], eboCube;
GLuint vaofloor, vbofloor[3], ebofloor;
GLuint vaoSLB, vboSLB[3];
GLuint vaoELB, vboELB[3];

void InitBuffer() {

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgramID);
    int lightPosLoc = glGetUniformLocation(shaderProgramID, "lightPos");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

    int lightColorLoc = glGetUniformLocation(shaderProgramID, "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    int objectColorLoc = glGetUniformLocation(shaderProgramID, "objectColor");
    glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

    int ambientLightLoc = glGetUniformLocation(shaderProgramID, "ambientLight");
    glUniform1f(ambientLightLoc, 0.5f);

    unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos �� ����: ī�޶� ��ġ
    glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

    unsigned int useTexture = glGetUniformLocation(shaderProgramID, "useTexture");
    glUniform1ui(useTexture, 1);

    // --- ����ü�� VAO �� VBO ���� ---
    glGenVertexArrays(1, &vaoCube);
    glGenBuffers(3, vboCube);  // ��ǥ�� ���� VBO 2��

    // ����ü VAO ���ε�
    glBindVertexArray(vaoCube);

    // ����ü ��ǥ VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboCube[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ����ü ��� VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboCube[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormal), cubeNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    // ����ü ���� VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboCube[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    // ����ü �ؽ�ó VBO �߰� - ������
    glGenBuffers(1, &vboTexCube);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTextures), cubeTextures, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    // ����ü �ε��� EBO
    glGenBuffers(1, &eboCube); // �ε��� EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    //�ٴ�
    glGenVertexArrays(1, &vaofloor);
    glGenBuffers(3, vbofloor);

    glBindVertexArray(vaofloor);

    glBindBuffer(GL_ARRAY_BUFFER, vbofloor[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbofloor[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorNormal), floorNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbofloor[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_color), floor_color, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    // �ٴ� �ؽ�ó VBO �߰� - ������
    glGenBuffers(1, &vboTexFloor);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexFloor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texfloor), texfloor, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    //������
    glGenVertexArrays(1, &vaoSLB);
    glGenBuffers(3, vboSLB);
    glBindVertexArray(vaoSLB);

    glBindBuffer(GL_ARRAY_BUFFER, vboSLB[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightbeamVertices), lightbeamVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboSLB[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightbeamNormal), lightbeamNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vboSLB[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(startlightbeamColors), startlightbeamColors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    // ������ �ؽ�ó VBO �߰� - ������
    glGenBuffers(1, &vboTexSLB);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexSLB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texlightbeam), texlightbeam, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    //����
    glGenVertexArrays(1, &vaoELB);
    glGenBuffers(3, vboELB);
    glBindVertexArray(vaoELB);

    glBindBuffer(GL_ARRAY_BUFFER, vboELB[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightbeamVertices), lightbeamVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboELB[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightbeamNormal), lightbeamNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vboELB[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(endlightbeamColors), endlightbeamColors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    // ���� �ؽ�ó VBO �߰� - ������
    glGenBuffers(1, &vboTexELB);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexELB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texlightbeam), texlightbeam, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    //ebo
    glGenBuffers(1, &ebofloor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebofloor);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sq_index), sq_index, GL_STATIC_DRAW);
}