#pragma once

#include "stdafx.h"

#include "TextureUtils.h"
#include "ShaderUtils.h"

GLuint textureIDs[3];
GLuint vboTexCube, vboTexFloor, vboTexSLB, vboTexELB;

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

    glUseProgram(shaderProgramID); // 반드시 먼저!
    GLint outTexture = glGetUniformLocation(shaderProgramID, "outTexture");
    glUniform1i(outTexture, 0);    // outTexture → texture unit 0 연결
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]); // 또는 이후 draw 시점에 bind
}