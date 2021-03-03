//
// Created by lidan on 2021/2/28.
//

#ifndef VR_BUFFEROBJECT_H
#define VR_BUFFEROBJECT_H

#include "util.h"

class BufferObject {

private:
    GLenum mType;
    GLenum mPattern;
    GLuint mBufferObjectId;

public:
    BufferObject();
    BufferObject(GLenum type);
    ~BufferObject();

    void allocate(const void *data, int count);

    void create();
    void bind();

    bool isCreated() const { return mBufferObjectId != 0; }

    void release();
    void destroy();

    void setUsagePattern(GLenum pattern) { mPattern = pattern; }

    GLuint bufferId() const { return mBufferObjectId; }
    GLenum type() const { return mType; }
    GLenum usagePattern() const { return mPattern; }

};


#endif //VR_BUFFEROBJECT_H
