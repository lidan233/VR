//
// Created by lidan on 2021/2/28.
//

#ifndef VR_FRAMEBUFFER_H
#define VR_FRAMEBUFFER_H
#include "util.h"

class FrameBuffer {
private:
    GLuint mFrameBufferId, mOldFrameBufferId;
    GLuint mRenderTextureId;
    GLuint mDepthBuffer;

    bool mAllocated, mBinded;
    GLint mRenderBufferWidth, mRenderBufferHeight;
public:
    FrameBuffer();
    ~FrameBuffer();

    void create(GLint w, GLint h, bool depth = true);
    void bind();
    void release();

    GLuint frameBufferId() const { return mFrameBufferId; }
    GLuint textureId() const { return mRenderTextureId; }

    GLint width() const { return mRenderBufferWidth; }
    GLint height() const { return mRenderBufferHeight; }

};


#endif //VR_FRAMEBUFFER_H
