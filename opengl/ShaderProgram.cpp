//
// Created by lidan on 1/3/2021.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
:ID(0),
_vs(nullptr),
_ys(nullptr)
{
    
}

ShaderProgram::~ShaderProgram() 
{

}


bool ShaderProgram::addShader(Shader* shader) 
{
    if (shader->shadertype() == ShaderType::VS)
    {
        if (_vs != nullptr)
            return false;
        _vs = shader ;
    }
    else if (shader->shadertype() == ShaderType::FG)
    {
        if ( _ys != nullptr)
            return false;
        _ys = shader;
    }

    return true ;
}

bool ShaderProgram::addShaderFromSource(ShaderType type, const std::string& source)
{
    Shader *shader = new Shader(type);

    if (shader->compileSourceCode(source))
    {
        if (shader->isCompiled())
        {
            if (addShader(shader))
                return true;
            else
            {
                shader->destroy();
                delete shader;
                return false;
            }
        }
        else
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Compile Shader Error: %s", shader->message().c_str());
            shader->destroy();
            delete shader;
            return false;
        }
    }
    else
    {
        shader->destroy();
        delete shader;
        return false;
    }

    return true;
}

bool ShaderProgram::addShaderFromFile(ShaderType type, const std::string& file) 
{
    Shader *shader = new Shader(type);

    if (shader->compileSourceFile(file))
    {
        if (shader->isCompiled())
        {
            if (addShader(shader))
                return true;
            else
            {
                shader->destroy();
                delete shader;
                return false;
            }
        }
        else
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", shader->message().c_str());
            shader->destroy();
            delete shader;
            return false;
        }
    }
    else
    {
        shader->destroy();
        delete shader;
        return false;
    }

    return true;
}


void ShaderProgram::removeAllShader() 
{
    if (ID && _vs && _ys)
    {
        glDetachShader(ID, _vs->shaderId());
        _vs->destroy();
        delete _vs ;

        glDetachShader(ID, _ys->shaderId());
        _ys->destroy();
        delete _ys;

        _link = false;
    }
}


bool ShaderProgram::link() 
{

    ID = glCreateProgram();

    if (!ID)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not create program object:");
        return false;
    }



    if (!_vs || !_ys)
        return false;

    glAttachShader(ID, _vs->shaderId());
    glAttachShader(ID, _ys->shaderId());
    glLinkProgram(ID);

    int value = 0;
    glGetProgramiv(ID, GL_LINK_STATUS, &value);
    _link = (value != 0);

    if (!_link)
    {
        int length = 0;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &value);
        if (value > 1)
        {
            _message.resize(value);
            glGetProgramInfoLog(ID, value, &length, &_message[0]);
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "ShaderProgram::link: %s", _message.c_str());
        }

        removeAllShader();
    }

    return _link;
}

bool ShaderProgram::bind() 
{
    if (!ID || !_link)
        return false;

    glUseProgram(ID);
    return true;
}

void ShaderProgram::release() 
{
    glUseProgram(0);
}




int ShaderProgram::attributeLocation(const char* name) 
{
    return glGetAttribLocation(ID, name);
}

int ShaderProgram::attributeLocation(const std::string& name) 
{
    return glGetAttribLocation(ID, name.c_str());
}

void ShaderProgram::bindAttributeLocation(const char *name, int location)
{
    glBindAttribLocation(ID, location, name);
}
void ShaderProgram::bindAttributeLocation(const std::string &name, int location){
    glBindAttribLocation(ID, location, name.c_str());
}

void ShaderProgram::disableAttributeArray(int location){
    glDisableVertexAttribArray(location);
}
void ShaderProgram::disableAttributeArray(const char *name){
    int location = glGetAttribLocation(ID, name);
    glDisableVertexAttribArray(location);
}
void ShaderProgram::disableAttributeArray(const std::string &name){
    int location = glGetAttribLocation(ID, name.c_str());
    glDisableVertexAttribArray(location);
}

void ShaderProgram::enableAttributeArray(int location){
    glEnableVertexAttribArray(location);
}
void ShaderProgram::enableAttributeArray(const char *name){
    int location = glGetAttribLocation(ID, name);
    glEnableVertexAttribArray(location);
}
void ShaderProgram::enableAttributeArray(const std::string &name){
    int location = glGetAttribLocation(ID, name.c_str());
    glEnableVertexAttribArray(location);
}

void ShaderProgram::setAttributeArray(int location, const GLfloat *values, int tupleSize, int stride){
    glVertexAttribPointer(location, tupleSize, GL_FLOAT, GL_FALSE, stride, values);
}

void ShaderProgram::setAttributeArray(int location, const Vec3 *values, int stride){
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, stride, values);
}

void ShaderProgram::setAttributeArray(int location, const Vec4 *values, int stride){
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, stride, values);
}

void ShaderProgram::setAttributeArray(int location, GLenum type, const void *values, int tupleSize, int stride){
    glVertexAttribPointer(location, tupleSize, type, GL_TRUE, stride, values);
}

void ShaderProgram::setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride){
    glVertexAttribPointer(location, tupleSize, type, GL_TRUE, stride,
                          reinterpret_cast<const void *>(intptr_t(offset)));
}

void ShaderProgram::setAttributeArray(const char *name, const GLfloat *values, int tupleSize, int stride){
    GLint location = glGetAttribLocation(ID, name);;
    glVertexAttribPointer(location, tupleSize, GL_FLOAT, GL_FALSE, stride, values);
}
void ShaderProgram::setAttributeArray(const char *name, const Vec3 *values, int stride){
    GLint location = glGetAttribLocation(ID, name);;
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, values);
}
void ShaderProgram::setAttributeArray(const char *name, const Vec4 *values, int stride){
    GLint location = glGetAttribLocation(ID, name);;
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, stride, values);
}
void ShaderProgram::setAttributeArray(const char *name, GLenum type, const void *values, int tupleSize, int stride){
    GLint location = glGetAttribLocation(ID, name);;
    glVertexAttribPointer(location, tupleSize, type, GL_TRUE, stride, values);
}

void ShaderProgram::setAttributeBuffer(const char *name, GLenum type, int offset, int tupleSize, int stride){
    GLint location = glGetAttribLocation(ID, name);;
    glVertexAttribPointer(location, tupleSize, type, GL_TRUE, stride,
                          reinterpret_cast<const void *>(intptr_t(offset)));
}

void ShaderProgram::setAttributeValue(int location, GLfloat value){
    glVertexAttrib1f(location, value);
}
void ShaderProgram::setAttributeValue(int location, GLfloat x, GLfloat y){
    glVertexAttrib2f(location, x, y);
}
void ShaderProgram::setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z){
    glVertexAttrib3f(location, x, y, z);
}
void ShaderProgram::setAttributeValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    glVertexAttrib4f(location, x, y, z, w) ;
}
void ShaderProgram::setAttributeValue(int location, const Vec3 &value){
    float* data = new float[3] ;
    for(int i = 0 ; i < 3; i++)  data[i] = value[i] ;
    glVertexAttrib3fv(location,data) ;
}
void ShaderProgram::setAttributeValue(int location, const Vec4 &value){
    float* data = new float[4] ;
    for(int i = 0 ; i < 4; i++)  data[i] = value[i] ;
    glVertexAttrib4fv(location,data) ;
}

void ShaderProgram::setAttributeValue(const char *name, GLfloat value){
    GLint location = glGetAttribLocation(ID, name);
    glVertexAttrib1f(location, value);
}
void ShaderProgram::setAttributeValue(const char *name, GLfloat x, GLfloat y){
    GLint location = glGetAttribLocation(ID, name);
    glVertexAttrib2f(location, x, y);
}
void ShaderProgram::setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z){
    GLint location = glGetAttribLocation(ID, name);
    glVertexAttrib3f(location, x, y, z);
}
void ShaderProgram::setAttributeValue(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    GLint location = glGetAttribLocation(ID, name);
    glVertexAttrib4f(location, x, y, z, w);
}
void ShaderProgram::setAttributeValue(const char *name, const Vec3 &value){
    GLint location = glGetAttribLocation(ID, name);
    float* data = new float[3] ;
    for(int i = 0 ; i < 3; i++)  data[i] = value[i] ;
    glVertexAttrib3fv(location,data) ;
}
void ShaderProgram::setAttributeValue(const char *name, const Vec4 &value){
    GLint location = glGetAttribLocation(ID, name);
    float* data = new float[4] ;
    for(int i = 0 ; i < 4; i++)  data[i] = value[i] ;
    glVertexAttrib3fv(location,data) ;
}

void ShaderProgram::setUniformValue(int location, GLint value){
    glUniform1i(location, value);
}
void ShaderProgram::setUniformValue(int location, GLuint value){
    glUniform1i(location, value);
}
void ShaderProgram::setUniformValue(int location, GLfloat value){
    glUniform1f(location, value);
}
void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y){
    glUniform2f(location, x, y);
}
void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z){
    glUniform3f(location, x, y, z);
}
void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    glUniform4f(location, x, y, z, w);
}
void ShaderProgram::setUniformValue(int location, const Vec3 &value){
    float* data = new float[3] ;
    for(int i = 0 ; i < 3; i++)  data[i] = value[i] ;
    glUniform3fv(location, 1, data);
}
void ShaderProgram::setUniformValue(int location, const Vec4 &value){
    float* data = new float[4] ;
    for(int i = 0 ; i < 4; i++)  data[i] = value[i] ;
    glUniform3fv(location, 1, data);
}
void ShaderProgram::setUniformValue(int location, const Lmatrix<float> &value){
    const float* data = value.getData() ;
    int m = value.mrows() ;
    int n = value.ncols() ;

    if(m == 2 && n == 3)
    {
        glUniformMatrix2x3fv(location, 1, GL_FALSE, data);
    }else if ( m ==3 && n ==2 )
    {
        glUniformMatrix3x2fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==3 && n ==3 )
    {
        glUniformMatrix3fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==3 && n ==4 )
    {
        glUniformMatrix3x4fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==4 && n ==2 )
    {
        glUniformMatrix4x2fv(location, 1, GL_FALSE, data);
    }else if ( m ==4 && n ==3 )
    {
        glUniformMatrix4x3fv(location, 1, GL_FALSE, data);
    }else if ( m ==4 && n ==4 )
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, data);
    }

}


void ShaderProgram::setUniformValue(const char *name, const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform3f(location, x, y, z);
}

void ShaderProgram::setUniformValue(const char *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform4f(location, x, y, z, w);
}


void ShaderProgram::setUniformValue(const char *name, const Vec3 &value)
{
    GLint location = glGetUniformLocation(ID, name);
    float * fv = new float[4] ;
    for(int i = 0 ; i < 4; i++ ) fv[i] = value[i] ;
    glUniform3fv(location, 1, fv);
}

void ShaderProgram::setUniformValue(const char *name, const Vec4 &value)
{
    GLint location = glGetUniformLocation(ID, name);
    float * fv = new float[4] ;
    for(int i = 0 ; i < 4; i++ ) fv[i] = value[i] ;
    glUniform4fv(location, 1, fv);
}

void ShaderProgram::setUniformValue(const char *name, const Lmatrix<float> &value)
{
    GLint location = glGetUniformLocation(ID, name);
    const float* data = value.getData() ;
    int m = value.mrows() ;
    int n = value.ncols() ;

    if(m == 2 && n == 3)
    {
        glUniformMatrix2x3fv(location, 1, GL_FALSE, data);
    }else if ( m ==3 && n ==2 )
    {
        glUniformMatrix3x2fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==3 && n ==3 )
    {
        glUniformMatrix3fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==3 && n ==4 )
    {
        glUniformMatrix3x4fv(location, 1, GL_FALSE, data);
    }
    else if ( m ==4 && n ==2 )
    {
        glUniformMatrix4x2fv(location, 1, GL_FALSE, data);
    }else if ( m ==4 && n ==3 )
    {
        glUniformMatrix4x3fv(location, 1, GL_FALSE, data);
    }else if ( m ==4 && n ==4 )
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, data);
    }


}


void ShaderProgram::setUniformValueArray(int location, const GLint *values, int count)
{
    glUniform1iv(location, count, values);
}

void ShaderProgram::setUniformValueArray(int location, const GLuint *values, int count)
{
    const GLint *iv = reinterpret_cast<const GLint *>(values);
    glUniform1iv(location, count, iv);
}

void ShaderProgram::setUniformValueArray(int location, const GLfloat *values, int count, int tupleSize)
{
    if (tupleSize == 1)
        glUniform1fv(location, count, values);
    else if (tupleSize == 2)
        glUniform2fv(location, count, values);
    else if (tupleSize == 3)
        glUniform3fv(location, count, values);
    else if (tupleSize == 4)
        glUniform4fv(location, count, values);
}



void ShaderProgram::setUniformValueArray(int location, const Vec3 *values, int count)
{
    float * fv = new float[3] ;
    for(int i = 0 ; i < 3; i++ ) fv[i] = (*values)[i] ;
    glUniform3fv(location, count, fv);
}

void ShaderProgram::setUniformValueArray(int location, const Vec4 *values, int count)
{
    float * fv = new float[4] ;
    for(int i = 0 ; i < 4; i++ ) fv[i] = (*values)[i] ;
    glUniform4fv(location, count, fv);
}

//void ShaderProgram::setUniformValueArray(int location, const Lmatrix<float> *values, int count)
//{
//    float * fv = reinterpret_cast<const GLfloat *>(values);
//
//    glUniformMatrix2fv(location, count, GL_FALSE, fv);
//}


void ShaderProgram::setUniformValueArray(const char *name, const GLint *values, int count)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform1iv(location, count, values);
}

void ShaderProgram::setUniformValueArray(const char *name, const GLuint *values, int count)
{
    GLint location = glGetUniformLocation(ID, name);
    const GLint *iv = reinterpret_cast<const GLint *>(values);
    glUniform1iv(location, count, iv);
}

void ShaderProgram::setUniformValueArray(const char *name, const GLfloat *values, int count, int tupleSize)
{
    GLint location = glGetUniformLocation(ID, name);

    if (tupleSize == 1)
        glUniform1fv(location, count, values);
    else if (tupleSize == 2)
        glUniform2fv(location, count, values);
    else if (tupleSize == 3)
        glUniform3fv(location, count, values);
    else if (tupleSize == 4)
        glUniform4fv(location, count, values);
}


void ShaderProgram::setUniformValueArray(const char *name, const Vec3 *values, int count)
{
    GLint location = glGetUniformLocation(ID, name);
    float * fv = new float[4] ;
    for(int i = 0 ; i < 4; i++ ) fv[i] = (*values)[i] ;
    glUniform3fv(location, count, fv);
}

void ShaderProgram::setUniformValueArray(const char *name, const Vec4 *values, int count)
{
    GLint location = glGetUniformLocation(ID, name);
     GLfloat *fv = new float[4] ;
    for(int i = 0 ; i < 4; i++ ) fv[i] = (*values)[i] ;
    glUniform4fv(location, count, fv);
}

void ShaderProgram::setUniformValueArray(const char *name, const Lmatrix<float> *values, int count)
{

    GLint location = glGetUniformLocation(ID, name);
    const float* data = values->getData() ;
    int m = values->mrows() ;
    int n = values->ncols() ;

    if(m == 2 && n == 3)
    {
        glUniformMatrix2x3fv(location, count, GL_FALSE, data);
    }else if ( m ==3 && n ==2 )
    {
        glUniformMatrix3x2fv(location, count, GL_FALSE, data);
    }
    else if ( m ==3 && n ==3 )
    {
        glUniformMatrix3fv(location, count, GL_FALSE, data);
    }
    else if ( m ==3 && n ==4 )
    {
        glUniformMatrix3x4fv(location, count, GL_FALSE, data);
    }
    else if ( m ==4 && n ==2 )
    {
        glUniformMatrix4x2fv(location, count, GL_FALSE, data);
    }else if ( m ==4 && n ==3 )
    {
        glUniformMatrix4x3fv(location, count, GL_FALSE, data);
    }else if ( m ==4 && n ==4 )
    {
        glUniformMatrix4fv(location, count, GL_FALSE, data);
    }

}


GLint ShaderProgram::uniformLocation(const char *name)
{
    return glGetUniformLocation(ID, name);
}

GLint ShaderProgram::uniformLocation(const std::string &name)
{
    return glGetUniformLocation(ID, name.c_str());
}


//void ShaderProgram::setUniformValue(int location, GLint value)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, GLuint value)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, GLfloat value)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, const Vec3 &value)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, const Vec4 &value)
//{
//
//}
//
//void ShaderProgram::setUniformValue(int location, const Lmatrix<float> &value)
//{
//
//}



void ShaderProgram::setUniformValue(const char *name, GLint value)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform1i(location, value);
}

void ShaderProgram::setUniformValue(const char *name, GLuint value)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform1i(location, value);
}

void ShaderProgram::setUniformValue(const char *name, GLfloat value)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform1f(location, value);
}

void ShaderProgram::setUniformValue(const char *name, GLfloat x, GLfloat y)
{
    GLint location = glGetUniformLocation(ID, name);
    glUniform2f(location, x, y);
}


