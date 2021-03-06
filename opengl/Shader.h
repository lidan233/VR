//
// Created by lidan on 2021/2/28.
//


//
// Created by 李源 on 2020-05-25.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>

#include "util.h"
#include "Log.h"

extern const char *vertexShader;
extern const char *fragmentShaderPassHeader;
extern const char *fragmentShaderPassFooter;



enum ShaderType{
    VS = 1 << 1 ,
    FG = 1 << 2 ,
    GS = 1 << 3 ,
};


class Shader {
private:
    bool isComplile ;
    friend class ShaderProgram ;
    GLuint ID ;
    ShaderType _type ;

    std::string _code ;
    std::string _message ;

protected:
    bool destroy() ;
    bool compile(const char *source) ;

public :
    Shader(ShaderType shaderType) ;
    ~Shader() ;

    bool compileSourceCode(const std::string code) ;
    bool compileSourceFile(const std::string filename) ;

    bool isCompiled() const { return isComplile ; }
    int shaderId() const { return ID ; }
    ShaderType shadertype() const { return _type; }
    std::string sourceCode() const { return _code; }
    std::string message() const { return _message ; }


};


#endif //LEARNOPENGL_SHADER_H
