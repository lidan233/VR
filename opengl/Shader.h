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

#include "ShaderProgram.h"
#include "util.h"


const char *vertexShader =
        "#version 330 core\n"
        "precision mediump float;\n"
        "precision mediump int;\n"
        "layout (location = 0) in vec3 vPosition;\n"
        "layout (location = 1) in vec2 vUV;\n"
        "void main() {\n"
        "    gl_Position = vec4(vPosition, 1.0f);\n"
        "}";

const char *fragmentShaderPassHeader =
        "#version 330 core\n"
        "precision mediump float;\n"
        "precision mediump int;\n"
        "uniform vec3       iResolution;\n"
        "uniform float      iGlobalTime;\n"
        "uniform float      iTime;\n"
        "uniform float      iChannelTime[4];\n"
        "uniform vec4       iMouse;\n"
        "uniform vec4       iDate;\n"
        "uniform float      iSampleRate;\n"
        "uniform vec3       iChannelResolution[4];\n"
        "uniform int        iFrame;\n"
        "uniform float      iTimeDelta;\n"
        "uniform float      iFrameRate;\n"
        "struct Channel {\n"
        "   vec3    resolution;\n"
        "   float   time;\n"
        "};\n"
        "uniform Channel iChannel[4];\n";

const char *fragmentShaderPassFooter =
        "void main() {\n"
        "   mainImage(gl_FragColor.xyzw, gl_FragCoord.xy);\n"
        "}";


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
