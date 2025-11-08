#include "InitGL.h"

int window_w = 600;
int window_h = 600;
GLint width, height;

void InitGL(int argc, char** argv)
{
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

    glutMotionFunc(Motion);
    glutPassiveMotionFunc(Motion); // 클릭 없이 이동
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);   // 키 떼짐 처리

    glutTimerFunc(10, TimerFunction, 1);
    glutReshapeFunc(Reshape);
    projection = glm::perspective(glm::radians(45.0f), (float)window_w / window_h, 0.1f, 1000.0f);
    glutDisplayFunc(drawScene);
}