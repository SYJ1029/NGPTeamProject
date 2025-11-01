#include "stdafx.h"

#include "MeshData.h"
#include "ShaderUtils.h"
#include "BufferInit.h"
#include "TextureUtils.h"
#include "CameraAndLight.h"
#include "GameState.h"
#include "CallbackFuncs.h"
#include "Render.h"

#include "Object.h"
#include "Player.h"


int window_w = 600;
int window_h = 600;
GLint width, height;


//const int MAX_PLAYER{ 3 };

//extern std::vector<Object> staticObjects;
//extern std::vector<MovingObject> MoveObjects;

extern std::array<Player, MAX_PLAYER> players;

int main(int argc, char** argv)
{
    projection = glm::perspective(glm::radians(45.0f), (float)window_w / window_h, 0.1f, 1000.0f);
    srand(time(NULL));
    setting(staticObjects, MoveObjects, players);
   /* for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 3; j++) {
            moving_blocks_chng_pos[i][j] = 0;
        }
    }*/
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
    //glutMouseFunc(Mouse);
    //glutSpecialFunc(SpecialInput);

    glutTimerFunc(10, TimerFunction, 1);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(drawScene);

    glutMainLoop();
}
