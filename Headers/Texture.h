//
// Created by George Allen on 16/08/2016.
//

#define STB_IMAGE_IMPLEMENTATION

#ifndef LEARNINGOPENGL_TEXTURE_H
#define LEARNINGOPENGL_TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>

#include <string>

class Texture
{
private:
    GLuint Data;
public:

    int Width;
    int Height;
    int Channels;

    Texture(std::string imagePath)
    {
        std::string path = PROJECT_SOURCE_DIR "/Textures/";
        path += imagePath;

        glGenTextures(1, &this->Data);
        glBindTexture(GL_TEXTURE_2D, this->Data); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // Set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Load image, create texture and generate mipmaps
        unsigned char * image = stbi_load(path.c_str(), &this->Width, &this->Height, &this->Channels, STBI_rgb);
        if (image == nullptr)
        {
            throw(std::string("Failed to load texture"));
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width, this->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Bind()
    {
        glBindTexture(GL_TEXTURE_2D, this->Data);
    }
};




#endif //LEARNINGOPENGL_TEXTURE_H
