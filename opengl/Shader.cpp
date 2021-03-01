//
// Created by lidan on 2021/2/28.
//

//
// Created by 李源 on 2020-05-25.
//

#include "Shader.h"

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
        llog(WARNNING, "Could not create shader of type "+std::to_string((int)shadertype()))  ;
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


    checkCompileErrors(ID,shaderId()) ;
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
    compile(code.c_str()) ;
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

