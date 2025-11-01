#include "stdafx.h"
#include "Render.h"
#include "ShaderUtils.h"
#include "CameraAndLight.h"
#include "GameState.h"
#include "BufferInit.h"
#include "TextureUtils.h"

extern std::vector<Object> staitcObjects;
extern std::vector<MovingObject> MoveObjects;


int wireframeMode = 0;
GLvoid drawScene()
{
    glUseProgram(shaderProgramID);
    // glClearColor(0.1, 0.1, 0.1, 1.0f);
    glClearColor(0.5, 0.5, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� ���� Ŭ����
    if (wireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // ���̾������� ���
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // �ָ��� ���
    }

    // === ���� ��ȯ ===
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
    int viewLoc = glGetUniformLocation(shaderProgramID, "viewTransform");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // === ���� ��� ===
    int projLoc = glGetUniformLocation(shaderProgramID, "projectionTransform");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    // ���̴� ���α׷� ���� ��
    // ������ ������ ���α׷��� ���ε�
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

    // === ������ ��ġ ��� ��ȯ ===
    glm::mat4 lightModel = glm::mat4(1.0f); // ���� ��� ����
    lightModel = glm::translate(lightModel, lightPos); // ������ �ʱ� ��ġ�� �̵�
    lightModel = glm::translate(lightModel, glm::vec3(25.0f, 100.0f, 25.0f));

    // ��ȯ�� ������ ���� ��ǥ ���
    glm::vec4 transformedLightPos = lightModel * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // ������ ���ο� ��ġ ���

    // GLSL�� ��ȯ�� ���� ��ġ ����
    int lightPosLoc = glGetUniformLocation(shaderProgramID, "lightPos");
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(transformedLightPos));

    // === ������ ���� ������Ʈ (Ȱ��ȭ�� ����) ===
    int lightColorLoc = glGetUniformLocation(shaderProgramID, "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);  // ������ ���� (���)

    // === vaoCube ===
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(char_pos[0], char_pos[1], char_pos[2]));
    //model = glm::rotate(model, glm::radians(char_angle[0]), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(char_angle[1]), glm::vec3(0.0, -1.0, 0.0));
    //model = glm::rotate(model, glm::radians(char_angle[2]), glm::vec3(0.0, 0.0, 1.0));
    unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    // vaoCube�� normalMatrix
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    unsigned int normalMatrixLoc = glGetUniformLocation(shaderProgramID, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // �ؽ�ó ��� Ȱ��ȭ - ������
    unsigned int useTexture = glGetUniformLocation(shaderProgramID, "useTexture");
    glUniform1i(useTexture, 1);

    //����ü �׸���
    glBindVertexArray(vaoCube);  // ����ü VAO ���ε�
    glBindTexture(GL_TEXTURE_2D, textureIDs[1]); // �ؽ�ó ���ε� - ������

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //�ٴ�
    glm::mat4 modelFloor = glm::mat4(1.0f);
    unsigned int modelLocation_F = glGetUniformLocation(shaderProgramID, "modelTransform");
    glUniformMatrix4fv(modelLocation_F, 1, GL_FALSE, glm::value_ptr(modelFloor));

    glm::mat3 normalMatrix_floor = glm::transpose(glm::inverse(glm::mat3(modelFloor)));
    unsigned int normalMatrixLoc_floor = glGetUniformLocation(shaderProgramID, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc_floor, 1, GL_FALSE, glm::value_ptr(normalMatrix_floor));

    glBindVertexArray(vaofloor);
    glBindTexture(GL_TEXTURE_2D, textureIDs[2]); // �ؽ�ó ���ε� - ������

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebofloor);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (int i = 0; i < count_block; i++) {
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, staticObjects[i].GetPosVec3());
        unsigned int modelLocation2 = glGetUniformLocation(shaderProgramID, "modelTransform");
        glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(model2));

        // vaoCube�� normalMatrix
        glm::mat3 normalMatrix2 = glm::transpose(glm::inverse(glm::mat3(model2)));
        unsigned int normalMatrixLoc2 = glGetUniformLocation(shaderProgramID, "normalMatrix");
        glUniformMatrix3fv(normalMatrixLoc2, 1, GL_FALSE, glm::value_ptr(normalMatrix2));

        //����ü �׸���
        glBindVertexArray(vaoCube);  // ����ü VAO ���ε�
        glBindTexture(GL_TEXTURE_2D, textureIDs[0]); // �ؽ�ó ���ε� - ������

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    for (int i = 0; i < count_moving_block; i++) {
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, MoveObjects[i].GetPosVec3());
        unsigned int modelLocation2 = glGetUniformLocation(shaderProgramID, "modelTransform");
        glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(model2));

        // vaoCube�� normalMatrix
        glm::mat3 normalMatrix2 = glm::transpose(glm::inverse(glm::mat3(model2)));
        unsigned int normalMatrixLoc2 = glGetUniformLocation(shaderProgramID, "normalMatrix");
        glUniformMatrix3fv(normalMatrixLoc2, 1, GL_FALSE, glm::value_ptr(normalMatrix2));

        //����ü �׸���
        glBindVertexArray(vaoCube);  // ����ü VAO ���ε�
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    // �ؽ�ó ��� ��Ȱ��ȭ - ������
    glUniform1i(useTexture, 0);

    int alphaLoc = glGetUniformLocation(shaderProgramID, "alpha");
    glUniform1f(alphaLoc, 0.3f); // 0.3�� ���� ����

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //SLB
    glm::mat4 model_SLB = glm::mat4(1.0f);
    model_SLB = glm::translate(model_SLB, glm::vec3(2.0f, 0.5f, 2.0f));
    unsigned int modelLocation_SLB = glGetUniformLocation(shaderProgramID, "modelTransform");
    glUniformMatrix4fv(modelLocation_SLB, 1, GL_FALSE, glm::value_ptr(model_SLB));

    glm::mat3 normalMatrix_SLB = glm::transpose(glm::inverse(glm::mat3(model_SLB)));
    unsigned int normalMatrixLoc_SLB = glGetUniformLocation(shaderProgramID, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc_SLB, 1, GL_FALSE, glm::value_ptr(normalMatrix_SLB));

    glBindVertexArray(vaoSLB);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //ELB
    glm::mat4 model_ELB = glm::mat4(1.0f);
    model_ELB = glm::translate(model_ELB, glm::vec3(2.0f, 0.5f, 2.0f));
    model_ELB = glm::translate(model_ELB, glm::vec3(0.0f, 50.0f, 45.0f));
    unsigned int modelLocation_ELB = glGetUniformLocation(shaderProgramID, "modelTransform");
    glUniformMatrix4fv(modelLocation_ELB, 1, GL_FALSE, glm::value_ptr(model_ELB));

    glm::mat3 normalMatrix_ELB = glm::transpose(glm::inverse(glm::mat3(model_ELB)));
    unsigned int normalMatrixLoc_ELB = glGetUniformLocation(shaderProgramID, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc_ELB, 1, GL_FALSE, glm::value_ptr(normalMatrix_ELB));

    glBindVertexArray(vaoELB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisable(GL_BLEND);

    glutSwapBuffers();  // ȭ�鿡 ����ϱ�
}

void init() {
    // ���� �׽�Ʈ Ȱ��ȭ
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  // ����� ��ü�� ���̵��� ���� (�⺻��)

    /*
    // ���� ���� Ȱ��ȭ
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);  // �޸��� ���� (�⺻ ����)
    glFrontFace(GL_CCW);  // �ð� �ݴ� ������ �ո����� ���� (�⺻ ����)
    */
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}