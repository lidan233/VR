//
// Created by lidan on 2021/3/3.
//

#ifndef VR_VERTEXARRAYOBJECT_H
#define VR_VERTEXARRAYOBJECT_H
#include "util.h"

class VertexArrayObject {
private:
    GLuint _VertexArray;
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void create();
    void bind();
    void release();
    void destroy();

    bool isCreated() const { return _VertexArray != 0; }
    GLuint objectId() const { return _VertexArray; }

};


#endif //VR_VERTEXARRAYOBJECT_H
