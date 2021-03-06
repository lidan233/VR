//
// Created by lidan on 2021/2/26.
//

#include "Sample2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


Sample2D::Sample2D(uint target,
                   std::string path,
                   uint filterMode,
                   uint wrapMode,
                   bool isfilp,
                   bool isrgb )
:_Target(target),
_WrapMode(wrapMode),
_FilterMode(filterMode) ,
_isFilp(isfilp),
_isRGB(isrgb) ,
_id(0),
_isLoaded(false),
_path(path)
{
    glGenTextures(1,&_id) ;
}

Sample2D::Sample2D(uint target, std::string path)
{

}

Sample2D::Sample2D(uint target,
                   uint filterMode,
                   uint wrapMode,
                   bool isfilp, bool isrgb)
:_Target(target),
_WrapMode(wrapMode),
_FilterMode(filterMode) ,
_isFilp(isfilp),
_isRGB(isrgb) ,
_id(0),
_isLoaded(false)
{
    glGenTextures(1,&_id) ;
}


Sample2D::~Sample2D()
{
    glDeleteTextures(1,&_id) ;
}

void Sample2D::loadByFile()
{
    stbi_set_flip_vertically_on_load(_isFilp) ;
    int w,h,c ;
    GLubyte* pixel = stbi_load(_path.c_str(),&w,&h,&c, STBI_rgb) ;
    if (pixel == nullptr)
    {
        return ;
    }

    if(_Target == GL_TEXTURE_CUBE_MAP)
    {
        for(int i = 0 ; i < 6 ; i++)
        {
            loadData(&pixel[i*w*h*c], w, h, c,1, false, i) ;
        }
    }else{
        loadData(pixel, w, h, c,1, false, 0) ;
    }
    stbi_image_free(pixel) ;
    pixel = nullptr ;
}

void Sample2D::loadByPixels(GLubyte *pixels,
                            GLint w, GLint h,
                            GLint depth,
                            GLint channels,
                            bool isFloat)
{
    loadData(pixels, w, h ,channels , depth, isFloat, 0  ) ;
}

void Sample2D::loadByEmpty(GLint w, GLint h)
{
    glBindTexture(GL_TEXTURE_2D, _id) ;
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, w,h) ;
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_id,0) ;

    _width = w ;
    _height = h ;
    _channel = 1 ;
}


 bool Sample2D::savePixelsToFile(const char *filepath, GLubyte *pixels, GLint w, GLint h, int depth)
{
    stbi_uc temp;

    for (int row = 0; row < (h >> 1); row++) {
        for (int col = 0; col < w; col++) {
            for (int z = 0; z < depth; z++) {
                int idx1 = (row * w + col) * depth + z;
                int idx2 = ((h - row - 1) * w + col) * depth + z;
                temp = pixels[idx1];
                pixels[idx1] = pixels[idx2];
                pixels[idx2] = temp;
            }
        }
    }

    return stbi_write_png(filepath, w, h, depth, pixels, w * depth);
}

void Sample2D::bindToPipLine(GLint pipline)
{
    glActiveTexture(GL_TEXTURE0+pipline) ;
    glBindTexture(_Target, _id) ;

    if(_WrapMode == GL_REPEAT)
    {
        glTexParameteri(_Target,GL_TEXTURE_WRAP_S, GL_REPEAT) ;
        glTexParameteri(_Target,GL_TEXTURE_WRAP_T, GL_REPEAT) ;
        if(_Target==GL_TEXTURE_CUBE_MAP || _Target == GL_TEXTURE_3D)
        {
            glTexParameteri(_Target,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE) ;
        }
    } else {
        glTexParameteri(_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        if (_Target == GL_TEXTURE_CUBE_MAP || _Target == GL_TEXTURE_3D)
        {
            glTexParameteri(_Target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
    }


}

void Sample2D::reflush()
{
    glBindTexture(_Target, 0 ) ;
}


void Sample2D::loadData(GLubyte* pixels,
              GLint w, GLint h, GLint c,
              GLuint d,
              bool isFloat, GLint mapLayer)
{
    uint format = GL_RGBA ;
    uint sourceFormat = GL_RGBA ;

    if (c == 1)
    {
        format = isFloat ? GL_R16F : GL_R8 ;
        sourceFormat = GL_RGB ;
    }else if (c == 2)
    {
        format = isFloat? GL_RG16F : GL_RGB ;
        sourceFormat = GL_RG ;
    }else if (c == 3)
    {
        format = isFloat? GL_RGB16F : GL_RGB8 ;
        sourceFormat = GL_RGB ;
    }else if (c == 4) {
        format = isFloat ? GL_RGBA16F : GL_RGBA8;
        sourceFormat = GL_RGBA;
    }


    glBindTexture(_Target, _id) ;
    if (_Target == GL_TEXTURE_CUBE_MAP) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + mapLayer, 0, format, w, h, 0, sourceFormat,
                     isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);
    } else if (_Target == GL_TEXTURE_3D) {
        glTexImage3D(GL_TEXTURE_3D, 0, format, w, h, d, 0, sourceFormat,
                     isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, sourceFormat,
                     isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);
    }


    glGenerateMipmap(_Target) ;

    _width = w ;
    _height = h ;
    _channel = d ;
    _isLoaded = true ;
}


