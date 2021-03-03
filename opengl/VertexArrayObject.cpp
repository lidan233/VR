//
// Created by lidan on 2021/3/3.
//

#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
        : _VertexArray(0)
{
}

VertexArrayObject::~VertexArrayObject()
{
    destroy();
}

void VertexArrayObject::create()
{
    glGenVertexArrays(1, &_VertexArray);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(_VertexArray);
}

void VertexArrayObject::release()
{
    glBindVertexArray(0);
}

void VertexArrayObject::destroy()
{
    if (_VertexArray != 0) {
        glDeleteVertexArrays(1, &_VertexArray);
        _VertexArray = 0;
    }
}



