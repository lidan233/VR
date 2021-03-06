//
// Created by lidan on 1/3/2021.
//

#ifndef VR_SHADERPROGRAM_H
#define VR_SHADERPROGRAM_H

#include "Shader.h"
#include "EigenLidan.h"

class ShaderProgram {
private:
    int _link ;
    int ID ;
    std::string _message ;
    Shader* _vs = nullptr ;
    Shader* _ys = nullptr ;

public:
    ShaderProgram() ;
    ~ShaderProgram() ;


    bool addShader(Shader* shader) ;
    bool addShaderFromSource(ShaderType type, const std::string& source) ;
    bool addShaderFromFile(ShaderType type, const std::string& file) ;

    void removeAllShader() ;

    bool link() ;
    bool bind() ;
    void release() ;

    bool isLinked() const { return _link; }
    const std::string& log() const { return _message; }
    int programID() const { return ID; }


    int attributeLocation(const char* name) ;
    int attributeLocation(const std::string& name) ;

    void bindAttributeLocation(const char *name, int location);
    void bindAttributeLocation(const std::string &name, int location);

    void disableAttributeArray(int location);
    void disableAttributeArray(const char *name);
    void disableAttributeArray(const std::string &name);

    void enableAttributeArray(int location);
    void enableAttributeArray(const char *name);
    void enableAttributeArray(const std::string &name);

    void setAttributeArray(int location, const GLfloat *values, int tupleSize, int stride);
    void setAttributeArray(int location, const Vec3 *valus, int stride);
    void setAttributeArray(int location, const Vec4 *values, int stride);
    void setAttributeArray(int location, GLenum type, const void *values, int tupleSize, int stride);

    void setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride);

    void setAttributeArray(const char *name, const GLfloat *values, int tupleSize, int stride);
    void setAttributeArray(const char *name, const Vec3 *values, int stride);
    void setAttributeArray(const char *name, const Vec4 *values, int stride);
    void setAttributeArray(const char *name, GLenum type, const void *values, int tupleSize, int stride);

    void setAttributeBuffer(const char *name, GLenum type, int offset, int tupleSize, int stride);

    void setAttributeValue(int location, GLfloat value);
    void setAttributeValue(int location, GLfloat x, GLfloat y);
    void setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z);
    void setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setAttributeValue(int location, const Vec3 &value);
    void setAttributeValue(int location, const Vec4 &value);

    void setAttributeValue(const char *name, GLfloat value);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z);
    void setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setAttributeValue(const char *name, const Vec3 &value);
    void setAttributeValue(const char *name, const Vec4 &value);

    void setUniformValue(int location, GLint value);
    void setUniformValue(int location, GLuint value);
    void setUniformValue(int location, GLfloat value);
    void setUniformValue(int location, GLfloat x, GLfloat y);
    void setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z);
    void setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformValue(int location, const Vec3 &value);
    void setUniformValue(int location, const Vec4 &value);
    void setUniformValue(int location, const Lmatrix<float> &value);


    void setUniformValue(const char *name, GLint value);
    void setUniformValue(const char *name, GLuint value);
    void setUniformValue(const char *name, GLfloat value);
    void setUniformValue(const char *name, GLfloat x, GLfloat y);
    void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z);
    void setUniformValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniformValue(const char *name, const Vec3 &value);
    void setUniformValue(const char *name, const Vec4 &value);
    void setUniformValue(const char *name, const Lmatrix<float> &value);


    void setUniformValueArray(int location, const GLint *values, int count);
    void setUniformValueArray(int location, const GLuint *values, int count);
    void setUniformValueArray(int location, const GLfloat *values, int count, int tupleSize);
    void setUniformValueArray(int location, const Vec3 *values, int count);
    void setUniformValueArray(int location, const Vec4 *values, int count);
//    void setUniformValueArray(int location, const Lmatrix<float> *values, int count);


    void setUniformValueArray(const char *name, const GLint *values, int count);
    void setUniformValueArray(const char *name, const GLuint *values, int count);
    void setUniformValueArray(const char *name, const GLfloat *values, int count, int tupleSize);
    void setUniformValueArray(const char *name, const Vec3 *values, int count);
    void setUniformValueArray(const char *name, const Vec4 *values, int count);
    void setUniformValueArray(const char *name, const Lmatrix<float> *values, int count);


    GLint uniformLocation(const char *name);
    GLint uniformLocation(const std::string &name);
};


#endif //VR_SHADERPROGRAM_H
