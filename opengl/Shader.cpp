//
// Created by lidan on 2021/2/28.
//

//
// Created by 李源 on 2020-05-25.
//

#include "Shader.h"


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


static const char* types[] = {
        "Vertex",
        "Fragment",
        "Geometry"
};


inline void checkCompileErrors(GLuint shader, int tp)
{
    GLint success ;
    GLchar infoLog[1024] ;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::string type = "" ;
        switch(tp){
            case ShaderType::VS:
                type = types[0] ;
                break ;
            case ShaderType::FG:
                type = types[1] ;
                break ;
            case ShaderType::GS:
                type = types[2] ;
                break ;
            default:
                break ;
        };

        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;

    }
}


bool Shader::destroy()
{
    if (!ID)
        return true;

    glDeleteShader(ID);
    ID = 0;
    return true ;
}

bool Shader::compile(const char *source)
{

    if(shadertype() == ShaderType::VS)
    {
        ID = glCreateShader(GL_VERTEX_SHADER) ;
    }else if ( shadertype() == ShaderType::FG)
    {
        ID = glCreateShader(GL_FRAGMENT_SHADER) ;
    }else if ( shadertype() == ShaderType::GS)
    {
        ID = glCreateShader(GL_GEOMETRY_SHADER) ;
    }

    if(!ID)
    {
        llog(INFO::WARNNING1, "Could not create shader of type "+std::to_string((int)shadertype()))  ;
        return false ;
    }

    glShaderSource(ID,1,&source,NULL) ;
    glCompileShader(ID) ;

    int value;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &value);
    isComplile = (value != 0);

    int sourceCodeLength = 0;
    glGetShaderiv(ID, GL_SHADER_SOURCE_LENGTH, &sourceCodeLength);
    if (sourceCodeLength > 1)
    {
        int temp = 0;
        _code.resize(sourceCodeLength);
        glGetShaderSource(ID, sourceCodeLength, &temp, &_code[0]);
    }


    checkCompileErrors(ID,shadertype()) ;
    return isComplile ;

}


Shader::Shader(ShaderType shaderType)
:ID(0),
 _type(shaderType)
{

}

Shader::~Shader()
{
}


bool Shader::compileSourceCode(const std::string code)
{
    return compile(code.c_str()) ;
}


bool Shader::compileSourceFile(const std::string filename)
{
    std::string SCode ;
    std::ifstream SFile ;


    SFile.exceptions(std::ifstream::failbit | std::ifstream::badbit) ;
    try{
        SFile.open(filename) ;
        std::stringstream SFileStream ;

        SFileStream <<SFile.rdbuf() ;
        SFile.close() ;
        SCode = SFileStream.str() ;

    }catch(std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" <<std::endl ;
    }
    const char* ShaderCode = SCode.c_str() ;

    compile(ShaderCode) ;
    return true ;

}

