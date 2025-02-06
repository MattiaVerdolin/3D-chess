
#include "texture.h"

#include <GL/freeglut.h>

#include "iostream"
#include <FreeImage.h>


Texture::Texture(std::string name) : Object(name) {}


Texture::~Texture() {
    release();
}


void Texture::createTexture(std::string path) {
    // std::cout << "Loading texture from file: " << path << std::endl;

    if (texID)
        glDeleteTextures(1, &texID);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path.c_str());
    if (format == FIF_UNKNOWN) {
        std::cerr << "Error: FreeImage does not recognize the file format: " << path << std::endl;
        return;
    }

    // std::cout << "Format detected by FreeImage: " << FreeImage_GetFormatFromFIF(format) << std::endl;

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str());

    if (!bitmap) {
        std::cerr << "Error: Unable to load image from file: " << path << std::endl;
        return;
    }

    // std::cout << "BPP: " << FreeImage_GetBPP(bitmap) << std::endl;

    // Flip texture vertically
    FreeImage_FlipVertical(bitmap);

    if (FreeImage_GetBPP(bitmap) == 32) {
        // 32 bits -> RGBA colors
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
            FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),
            GL_BGRA_EXT, GL_UNSIGNED_BYTE,
            (void*)FreeImage_GetBits(bitmap));
    }
    else if (FreeImage_GetBPP(bitmap) == 24) {
        // 24 bits -> RGB colors
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
            FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),
            GL_BGR_EXT, GL_UNSIGNED_BYTE,
            (void*)FreeImage_GetBits(bitmap));
    }

    // Release bitmap
    FreeImage_Unload(bitmap);
}

void Texture::render(const glm::mat4& finalMatrix) {
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::release() {
    if (texID) {
        glDeleteTextures(1, &texID);
        texID = 0;
    }
}


std::string Texture::getName() const {
    return name;
}

void Texture::setName(std::string& n) {
    name = n;
}
