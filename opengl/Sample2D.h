//
// Created by lidan on 2021/2/26.
//

#ifndef VR_SAMPLE2D_H
#define VR_SAMPLE2D_H

#include "util.h"


#include <string>

typedef unsigned int uint ;

class Sample2D {
private:
    uint _Target ;
    uint _FilterMode ;
    uint _WrapMode ;
    uint _id ;
    uint _height, _width, _channel ;
    bool _isFilp ;
    bool _isRGB ; // false is hsv
    bool _isLoaded ; // is loaded in opengl context ;
    std::string _path = "" ;

public:
    Sample2D(uint target, std::string path, uint filterMode, uint wrapMode, bool isfilp, bool isrgb ) ;
    Sample2D(uint target, std::string path) ;
    Sample2D(uint target, uint filterMode, uint wrapMode, bool isfilp, bool isrgb) ;
    ~Sample2D() ;

    void loadByFile() ;
    void loadByPixels(GLubyte *pixels, GLint w, GLint h, GLint depth, GLint channels, bool isFloat)  ;
    void loadByEmpty(GLint w, GLint h) ;
    void bindToPipLine(GLint pipline) ;
    void reflush() ;
    GLint height()  const { return _height; }
    GLint width() const { return _width; }
    GLint depth() const { return _channel; }
    bool isLoaded() const { return _isLoaded; }
    GLuint id() const { return _id ; }

    static bool savePixelsToFile(const char *filepath, GLubyte *pixels, GLint w, GLint h, int depth);

protected:
    void loadData(GLubyte* pixels, GLint w, GLint h, GLint c, GLuint d, bool isFloat, GLint mapLayer) ;
};


#endif //VR_SAMPLE2D_H
