#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


//#include <glm/glm/glm.hpp>
//#include <glm/glm/ext.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>


#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <time.h>
#include <cmath>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GRAVITY 0.01f

char* filetobuf(const char* file);

// ������ü ��ǥ
const GLfloat cubeVertices[8][3] = {
    {  0.5f,  0.5f,  0.5f },   // ���� 0
    { -0.5f,  0.5f,  0.5f },   // ���� 1
    { -0.5f, -0.5f,  0.5f },   // ���� 2
    {  0.5f, -0.5f,  0.5f },   // ���� 3
    {  0.5f,  0.5f, -0.5f },   // ���� 4
    { -0.5f,  0.5f, -0.5f },   // ���� 5
    { -0.5f, -0.5f, -0.5f },   // ���� 6
    {  0.5f, -0.5f, -0.5f }    // ���� 7
};
const GLfloat cubeNormal[8][3] = {
    {  0.57735f,  0.57735f,  0.57735f },  // ���� 0
    { -0.57735f,  0.57735f,  0.57735f },  // ���� 1
    { -0.57735f, -0.57735f,  0.57735f },  // ���� 2
    {  0.57735f, -0.57735f,  0.57735f },  // ���� 3
    {  0.57735f,  0.57735f, -0.57735f },  // ���� 4
    { -0.57735f,  0.57735f, -0.57735f },  // ���� 5
    { -0.57735f, -0.57735f, -0.57735f },  // ���� 6
    {  0.57735f, -0.57735f, -0.57735f }   // ���� 7
};
const GLfloat cubeColors[8][3] = {
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }
};
const GLfloat cubeTextures[8][2] = {
    { 0.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 0.0f },
    { 0.0f, 0.0f },
    { 1.0f, 1.0f },
    { 0.0f, 1.0f },
    { 0.0f, 0.0f },
    { 1.0f, 0.0f }
};

const GLfloat lightbeamVertices[8][3] = {
    {  2.5,  100.0f,  2.5 },   // ���� 0
    { -2.5,  100.0f,  2.5 },   // ���� 1
    { -2.5, -0.0f,  2.5 },   // ���� 2
    {  2.5, -0.0f,  2.5 },   // ���� 3
    {  2.5,  100.0f, -2.5 },   // ���� 4
    { -2.5,  100.0f, -2.5 },   // ���� 5
    { -2.5, -0.0f, -2.5 },   // ���� 6
    {  2.5, -0.0f, -2.5 }    // ���� 7
};
const GLfloat lightbeamNormal[8][3] = {
    {  0.707f,  0.0f,  0.707f },  // ���� 0
    { -0.707f,  0.0f,  0.707f },  // ���� 1
    { -0.707f,  0.0f,  0.707f },  // ���� 2
    {  0.707f,  0.0f,  0.707f },  // ���� 3
    {  0.707f,  0.0f, -0.707f },  // ���� 4
    { -0.707f,  0.0f, -0.707f },  // ���� 5
    { -0.707f,  0.0f, -0.707f },  // ���� 6
    {  0.707f,  0.0f, -0.707f }   // ���� 7
};

const GLfloat startlightbeamColors[8][4] = {
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f },
    { 0.0f, 1.0f, 0.0f, 0.3f }
};
const GLfloat endlightbeamColors[8][4] = {
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f },
    { 1.0f, 0.0f, 0.0f, 0.3f }
};
const GLfloat texlightbeam[8][2] = {
    { 0.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 0.0f },
    { 0.0f, 0.0f },
    { 1.0f, 1.0f },
    { 0.0f, 1.0f },
    { 0.0f, 0.0f },
    { 1.0f, 0.0f }
};

const GLuint cubeIndices[36] = {
    // �ո�
    0, 1, 2,
    2, 3, 0,
    // �޸�
    4, 5, 6,
    6, 7, 4,
    // ���ʸ�
    1, 5, 6,
    6, 2, 1,
    // �����ʸ�
    0, 4, 7,
    7, 3, 0,
    // ����
    0, 1, 5,
    5, 4, 0,
    // �Ʒ���
    3, 2, 6,
    6, 7, 3
};
float vertices[] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const GLfloat floorVertices[4][3] = {
    {50.0f, -10.0f, 50.0f },
    {-0.0f, -10.0f, 50.0f },
    {-0.0f, -10.0f, -0.0f },
    {50.0f, -10.0f, -0.0f }
};
const GLfloat floorNormal[4][3] = {
    { 0.0f, 1.0f, 0.0f },  // ���� 0
    { 0.0f, 1.0f, 0.0f },  // ���� 1
    { 0.0f, 1.0f, 0.0f },  // ���� 2
    { 0.0f, 1.0f, 0.0f }   // ���� 3
};
//const GLfloat floor_color[4][3] = {
//    {0.0f, 0.0f, 0.8f },
//    {0.0f, 0.0f, 1.0f },
//    {0.0f, 0.0f, 0.5f },
//    {0.0f, 0.0f, 0.2f }
//};
const GLfloat floor_color[4][3] = {
    {0.7f, 0.7f, 1.0f },
    {0.7f, 0.7f, 1.0f },
    {0.7f, 0.7f, 1.0f },
    {0.7f, 0.7f, 1.0f }
};
const GLfloat texfloor[4][2] = {
    {1.0f, 1.0f},
    {0.0f, 1.0f},
    {0.0f, 0.0f},
    {1.0f, 0.0f}
};
const GLuint sq_index[6] = {
    0,1,2,
    2,3,0
};

GLuint vaoCube, vboCube[3], eboCube;
GLuint vaofloor, vbofloor[3], ebofloor;
GLuint vaoSLB, vboSLB[3];
GLuint vaoELB, vboELB[3];

GLuint textureIDs[3], vboTexCube, vboTexFloor, vboTexSLB, vboTexELB;

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.001f); // ī�޶� ��ġ
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f); // ī�޶� �ٶ󺸴� ����
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);           // ī�޶��� ���� ����
glm::mat4 projection;   // ���� ��� ����

int window_w = 600; // �⺻ â �ʺ�
int window_h = 600; // �⺻ â ����

void make_vertexShaders();
void make_fragmentShaders();
void InitBuffer();
void init();
void InitTexture();
GLuint make_shaderProgram();
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

float angle = 0.0f;  // ������ ������ ���� ����
int draw_type = 1;
int depht_type = 1;
int wireframeMode = 0;
int before_mouse_x = 300;
int before_mouse_y = 300;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f); // ������ �ʱ� ��ġ

float char_angle[3] = { 0.0f, 0.0f, 0.0f };
float char_pos[3] = { 0.0f, 10.0f, 0.0f };

int go_v[4] = { 0,0,0,0 };
int count_block = 1;
float blocks_pos[10000][3];

int count_moving_block = 1;
float moving_blocks_pos[10000][3];
float moving_blocks_chng_pos[10000][3];
int moving_blocks_vec[10000][3];

float y_speed = 0.0f;
bool jumpable;
bool infjump = false;
bool game_end{ false };

bool checkCollision(float ax, float ay, float az, float bx, float by, float bz);
void setting();

void main(int argc, char** argv)
{
    projection = glm::perspective(glm::radians(45.0f), (float)window_w / window_h, 0.1f, 1000.0f);
    srand(time(NULL));
    setting();
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 3; j++) {
            moving_blocks_chng_pos[i][j] = 0;
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_w, window_h);
    glutCreateWindow("TermProj");
    glewExperimental = GL_TRUE;
    glewInit();
    make_shaderProgram();
    InitTexture();
    InitBuffer();
    init();

    glutDisplayFunc(drawScene);
    glutTimerFunc(10, TimerFunction, 1);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutPassiveMotionFunc(Motion); // Ŭ�� ���� �̵�
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);   // Ű ���� ó��
    glutSpecialFunc(SpecialInput);

    glutMainLoop();
}

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
        model2 = glm::translate(model2, glm::vec3(blocks_pos[i][0], blocks_pos[i][1], blocks_pos[i][2]));
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
        model2 = glm::translate(model2, glm::vec3(moving_blocks_pos[i][0], moving_blocks_pos[i][1], moving_blocks_pos[i][2]));
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

GLuint make_shaderProgram()
{
    make_vertexShaders();
    make_fragmentShaders();

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgramID;
}

void make_vertexShaders()
{
    GLchar* vertexSource = filetobuf("vertex.glsl");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
    }
}

void make_fragmentShaders()
{
    GLchar* fragmentSource = filetobuf("fragment.glsl");
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
    }
}

void TimerFunction(int value)
{
    angle += 1.0f;  // ������ 10���� ����
    if (angle >= 360.0f) {
        angle -= 360.0f;  // 360���� ������ �ʱ�ȭ
    }

    // A�� �̵� �� ȸ�� ��ȯ ���
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(char_pos[0], char_pos[1], char_pos[2]));
    model = glm::rotate(model, glm::radians(char_angle[1]), glm::vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(char_angle[0]), glm::vec3(1.0, 0.0, 0.0));

    // �ʱ� �� (A���� z+1 ��ġ)
    glm::vec4 initialPoint = glm::vec4(0.0f, 3.0f, -5.0f, 1.0f);

    // ��ȯ�� ��ǥ ���
    glm::vec4 transformedPoint = model * initialPoint;

    // cameraPos ������Ʈ
    cameraPos.x = transformedPoint.x;
    cameraPos.y = transformedPoint.y;
    cameraPos.z = transformedPoint.z;

    // A ���� �ݴ��� �� ��� (���������� �ݴ� �������� �̵�)
    glm::vec4 targetPoint = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // ��ȯ�� ��ǥ ���
    glm::vec4 rotatedTarget = model * targetPoint;

    // cameraTarget ������Ʈ
    cameraTarget.x = rotatedTarget.x;
    cameraTarget.y = rotatedTarget.y;
    cameraTarget.z = rotatedTarget.z;


    // char_angle[1] ���� ȸ�� ��� ���
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-char_angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));

    // ����(forward) �� ����(right) ���� ���
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f); // �⺻ ���� ����
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);    // �⺻ ���� ����
    forward = glm::normalize(glm::vec3(rotation * glm::vec4(forward, 0.0f))); // ȸ���� ���� ����
    right = glm::normalize(glm::vec3(rotation * glm::vec4(right, 0.0f)));     // ȸ���� ���� ����

    // �̵� �Ÿ�
    float moveSpeed = 0.1f;

    if (go_v[0]) { // ������ �̵�
        char_pos[0] -= forward.x * moveSpeed;
        char_pos[2] -= forward.z * moveSpeed;
    }
    if (go_v[1]) {// �ڷ� �̵�
        char_pos[0] += forward.x * moveSpeed;
        char_pos[2] += forward.z * moveSpeed;
    }
    if (go_v[2]) { // ���� �̵�
        char_pos[0] += right.x * moveSpeed;
        char_pos[2] += right.z * moveSpeed;
    }
    if (go_v[3]) { // ������ �̵�
        char_pos[0] -= right.x * moveSpeed;
        char_pos[2] -= right.z * moveSpeed;
    }

    y_speed -= GRAVITY;
    jumpable = infjump;

    for (int i = 0; i < count_block; i++) {
        if (checkCollision(char_pos[0], char_pos[1], char_pos[2], blocks_pos[i][0], blocks_pos[i][1], blocks_pos[i][2])) {
            if ((char_pos[1] + y_speed) < blocks_pos[i][1] + 1.0f && char_pos[1] >= blocks_pos[i][1]) {
                char_pos[1] = blocks_pos[i][1] + 1.0f;
                y_speed = 0;
                jumpable = 1;
            }
            else if ((char_pos[1] + y_speed) > blocks_pos[i][1] - 1.0f && char_pos[1] <= blocks_pos[i][1]) {
                char_pos[1] = blocks_pos[i][1] - 1.0f;
                y_speed = 0;
            }

            if ((!game_end) && ((blocks_pos[i][1] >= 50) && (count_block - i <= 25))) {
                std::cout << "Congratulations! You Win! \npress \"q\" to quit the game.\n";
                game_end = true;
            }

            break;
        }
    }
    for (int i = 0; i < count_moving_block; i++) {
        if (checkCollision(char_pos[0], char_pos[1], char_pos[2], moving_blocks_pos[i][0], moving_blocks_pos[i][1], moving_blocks_pos[i][2])) {
            if ((char_pos[1] + y_speed) < moving_blocks_pos[i][1] + 1.0f && char_pos[1] >= moving_blocks_pos[i][1]) {
                char_pos[1] = moving_blocks_pos[i][1] + 1.0f;
                y_speed = 0;
                jumpable = 1;
            }
            else if ((char_pos[1] + y_speed) > moving_blocks_pos[i][1] - 1.0f && char_pos[1] <= moving_blocks_pos[i][1]) {
                char_pos[1] = moving_blocks_pos[i][1] - 1.0f;
                y_speed = 0;
            }

            for (int j = 0; j < 3; j++) {
                char_pos[j] += moving_blocks_vec[i][j] * 0.03f;
            }
            break;
        }
    }

    for (int i = 0; i < count_moving_block; i++) {
        for (int j = 0; j < 3; j++) {
            if (moving_blocks_vec[i][j] != 0) {
                moving_blocks_chng_pos[i][j] += moving_blocks_vec[i][j] * 0.03f;
                moving_blocks_pos[i][j] += moving_blocks_vec[i][j] * 0.03f;

                if (moving_blocks_chng_pos[i][j] >= 5.0f) moving_blocks_vec[i][j] *= -1;
                else if (moving_blocks_chng_pos[i][j] <= -5.0f) moving_blocks_vec[i][j] *= -1;
            }
        }
    }

    char_pos[1] += y_speed;


    if (char_pos[1] <= -10.0f) {
        char_pos[0] = 0.0f;
        char_pos[1] = 10.0f;
        char_pos[2] = 0.0f;

        y_speed = 0.0f;
    }


    glutPostRedisplay();
    glutTimerFunc(10, TimerFunction, 1);
}
void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    }
}
void Motion(int x, int y)
{
    // x�� y�� ��ȭ�� ���
    float deltaX = static_cast<float>(x - before_mouse_x);
    float deltaY = static_cast<float>(y - before_mouse_y);

    // ��ȭ���� char_angle�� �ݿ�
    char_angle[1] += deltaX * 0.8f; // x �̵����� ����Ͽ� y�� ȸ�� ���� ����
    char_angle[0] += deltaY * 0.1f; // y �̵����� ����Ͽ� x�� ȸ�� ���� ����

    // ���� ���� ���� (360�� �̻�, -360�� ���Ϸ� ���� �ʵ��� ó��)
    for (int i = 0; i < 2; i++) {
        if (char_angle[i] > 360.0f) char_angle[i] -= 360.0f;
        if (char_angle[i] < -360.0f) char_angle[i] += 360.0f;
    }

    // ���� ���콺 ��ġ�� �����Ͽ� ���� ȣ�⿡�� ��
    before_mouse_x = x;
    before_mouse_y = y;
}


void Keyboard(unsigned char key, int x, int y)
{
    // Ű �Է� ó��
    switch (key) {
    case 'j':
        if (infjump == 1) {
            infjump = 0;
            std::cout << "inf jump disabled.\n";
        }
        else if (infjump == 0) {
            infjump = 1;
            std::cout << "inf jump enabled.\n";
        }

        break;
    case ' ':
        if (jumpable) {
            y_speed = 0.3f;
            char_pos[1] += y_speed;
        }
        break;
    case '\n':
    case '\r':
        char_angle[0] = 0;
        char_angle[1] = 0;
        before_mouse_x = x;
        before_mouse_y = y;
        break;
    case 'q': // ����
        exit(0);
        break;
    case 'w': // ������ �̵�
        go_v[0] = 1;
        break;
    case 's': // �ڷ� �̵�
        go_v[1] = 1;
        break;
    case 'a': // ���� �̵�
        go_v[2] = 1;
        break;
    case 'd': // ������ �̵�
        go_v[3] = 1;
        break;
    }
}
void KeyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // ������ �̵�
        go_v[0] = 0;
        break;
    case 's': // �ڷ� �̵�
        go_v[1] = 0;
        break;
    case 'a': // ���� �̵�
        go_v[2] = 0;
        break;
    case 'd': // ������ �̵�
        go_v[3] = 0;
        break;
    }
}


void SpecialInput(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  // �� Ű

        break;
    case GLUT_KEY_RIGHT: // �� Ű

        break;
    case GLUT_KEY_UP:    // �� Ű

        break;
    case GLUT_KEY_DOWN:  // �� Ű

        break;
    }
    glutPostRedisplay();  // �Է� �� �ٽ� �׸���
}

bool checkCollision(float ax, float ay, float az, float bx, float by, float bz) {
    // ������ü�� ����� ��谪
    float min_x = -0.5f, max_x = 0.5f;
    float min_y = -0.5f, max_y = 0.5f;
    float min_z = -0.5f, max_z = 0.5f;

    // A�� �̵� �� ���
    float a_min_x = ax + min_x;
    float a_max_x = ax + max_x;
    float a_min_y = ay + min_y;
    float a_max_y = ay + max_y;
    float a_min_z = az + min_z;
    float a_max_z = az + max_z;

    // B�� �̵� �� ���
    float b_min_x = bx + min_x;
    float b_max_x = bx + max_x;
    float b_min_y = by + min_y;
    float b_max_y = by + max_y;
    float b_min_z = bz + min_z;
    float b_max_z = bz + max_z;

    // �浹 ���� (AABB �浹 �˻�)
    bool x_overlap = (a_min_x <= b_max_x) && (a_max_x >= b_min_x);
    bool y_overlap = (a_min_y <= b_max_y) && (a_max_y >= b_min_y);
    bool z_overlap = (a_min_z <= b_max_z) && (a_max_z >= b_min_z);

    return x_overlap && y_overlap && z_overlap;
}


char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;
    fptr = fopen(file, "rb"); // Open file for reading
    if (!fptr) // Return NULL on failure
        return NULL;
    fseek(fptr, 0, SEEK_END); // Seek to the end of the file
    length = ftell(fptr); // Find out how many bytes into the file we are
    buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
    fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
    fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
    fclose(fptr); // Close the file
    buf[length] = 0; // Null terminator
    return buf; // Return the buffer
}

void input_block_pos(int i, float x, float y, float z) {
    blocks_pos[i][0] = x;
    blocks_pos[i][1] = y;
    blocks_pos[i][2] = z;
}
void input_moving_block_pos(int i, float x, float y, float z, int vx, int vy, int vz) {
    moving_blocks_pos[i][0] = x;
    moving_blocks_pos[i][1] = y;
    moving_blocks_pos[i][2] = z;

    moving_blocks_vec[i][0] = vx;
    moving_blocks_vec[i][1] = vy;
    moving_blocks_vec[i][2] = vz;
}

void place_platform(int& curr, const glm::vec3& v, int dx, int dy, int dz) {
    for (int y = 0; y < dy; ++y) {
        for (int x = 0; x < dx; ++x) {
            for (int z = 0; z < dz; ++z) {
                input_block_pos(curr++, v.x + (float)x, v.y + (float)y, v.z + (float)z);
                //std::cout << "block #" << curr << " (" << v.x + (float)x << ", " << v.y + (float)y << ", " << v.z + (float)z << ")\n";
            }
        }
    }
}

void setting()
{
    int curr_block_count{};
    int curr_moving_count{};

    place_platform(curr_block_count, glm::vec3{ 0.0f, 0.0f, 0.0f }, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(curr_block_count, glm::vec3{ 7.0f + float(i * 6), float(i), 1.0f }, 3, 1, 3);
    }

    place_platform(curr_block_count, glm::vec3{ 45.0f, 5.0f, 0.0f }, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(curr_block_count, glm::vec3{ 46.0f, 5.0f + (float)i, 10.0f + (float)i * 6 }, 3, 1, 1);
    }

    place_platform(curr_block_count, glm::vec3{ 45.0f, 10.0f, 45.0f }, 5, 1, 5);

    input_moving_block_pos(curr_moving_count++, 43.0f, 14.0f, 47.0f, 0.0f, 1.0f, 0.0f);

    input_block_pos(curr_block_count++, 40.0f, 18.0f, 47.0f);
    input_block_pos(curr_block_count++, 34.0f, 18.0f, 50.0f);
    input_block_pos(curr_block_count++, 28.0f, 19.0f, 47.0f);

    input_moving_block_pos(curr_moving_count++, 25.0f, 19.0f, 42.0f, 0.0f, 0.0f, 1.0f);

    place_platform(curr_block_count, glm::vec3{ 25.0f, 19.0f, 32.0f }, 1, 1, 3);

    input_block_pos(curr_block_count++, 18.0f, 19.0f, 33.0f);
    input_block_pos(curr_block_count++, 18.0f, 20.0f, 27.0f);
    input_block_pos(curr_block_count++, 18.0f, 20.0f, 27.0f);
    input_block_pos(curr_block_count++, 14.0f, 21.0f, 23.0f);
    input_block_pos(curr_block_count++, 9.5f, 22.5f, 18.5f);
    input_block_pos(curr_block_count++, 5.0f, 24.0f, 18.0f);
    input_block_pos(curr_block_count++, 7.0f, 25.0f, 12.0f);
    input_block_pos(curr_block_count++, 12.0f, 26.5f, 16.0f);
    input_block_pos(curr_block_count++, 16.0f, 28.0f, 22.0f);
    input_block_pos(curr_block_count++, 15.0f, 30.0f, 27.0f);
    input_block_pos(curr_block_count++, 12.0f, 32.0f, 33.0f);
    input_block_pos(curr_block_count++, 10.0f, 34.5f, 36.0f);
    input_block_pos(curr_block_count++, 7.5f, 36.0f, 38.0f);
    input_block_pos(curr_block_count++, 5.0f, 38.0f, 41.0f);
    input_block_pos(curr_block_count++, 4.0f, 40.0f, 45.0f);
    input_block_pos(curr_block_count++, 3.5f, 42.0f, 48.5f);
    input_block_pos(curr_block_count++, 7.0f, 44.0f, 46.0f);
    input_block_pos(curr_block_count++, 8.0f, 46.0f, 41.0f);
    input_block_pos(curr_block_count++, 3.0f, 48.0f, 42.0f);

    place_platform(curr_block_count, glm::vec3{ 0.0f, 50.0f, 45.0f }, 5, 1, 5);

    count_block = curr_block_count;
    count_moving_block = curr_moving_count;
}

void InitTexture()
{
    std::string texFileNames[3] = {
        "texture.bmp",
        "texture1.png",
        "sea.jpg"
    };

    for (int i = 0; i < 3; ++i) {
        glGenTextures(1, &textureIDs[i]);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int w, h, channels;
        unsigned char* data = stbi_load(texFileNames[i].c_str(), &w, &h, &channels, 0);

        if (data)
        {
            GLenum format = GL_RGB;
            if (channels == 1) format = GL_RED;
            else if (channels == 3) format = GL_RGB;
            else if (channels == 4) format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            std::cout << "image " << '\"' << texFileNames[i] << "\" load complete: " << w << ", " << h << ", " << channels << '\n';
        }
        else {
            std::cerr << "Failed to load texture: " << texFileNames[i] << std::endl;
        }
        stbi_image_free(data);
    }

    glUseProgram(shaderProgramID); // �ݵ�� ����!
    GLint outTexture = glGetUniformLocation(shaderProgramID, "outTexture");
    glUniform1i(outTexture, 0);    // outTexture �� texture unit 0 ����
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]); // �Ǵ� ���� draw ������ bind
}