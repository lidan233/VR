//
// Created by lidan on 2021/2/28.
//

#include "FrameBuffer.h"
#include "framebuffer.h"

FrameBuffer::FrameBuffer()
        : mFrameBufferId(0),
          mOldFrameBufferId(0),
          mRenderTextureId(0),
          mDepthBuffer(0),
          mAllocated(false),
          mBinded(false),
          mRenderBufferWidth(0),
          mRenderBufferHeight(0)
{
}

FrameBuffer::~FrameBuffer()
{
    release();
    if (mAllocated)
    {
        glDeleteTextures(1, &mRenderTextureId);
        glDeleteRenderbuffers(1, &mDepthBuffer);
        glDeleteFramebuffers(1, &mFrameBufferId);
        mAllocated = false;
    }
}

void FrameBuffer::create(GLint w, GLint h, bool depth)
{
    if (!mAllocated)
    {
        glGenFramebuffers(1, &mFrameBufferId);
        glGenTextures(1, &mRenderTextureId);

        if (depth)
            glGenRenderbuffers(1, &mDepthBuffer);

    }

    mRenderBufferWidth = w;
    mRenderBufferHeight = h;

    bind();

    glBindTexture(GL_TEXTURE_2D, mRenderTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mRenderTextureId, 0);

    if (depth)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        mAllocated = true;

    release();

    glBindTexture(GL_TEXTURE_2D, 0);
    if (depth)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}

void FrameBuffer::bind()
{
    if (!mBinded)
    {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&mOldFrameBufferId);

        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_TEXTURE_2D);
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
        glViewport(0, 0, mRenderBufferWidth, mRenderBufferHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        if (mDepthBuffer != 0)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        else
            glClear(GL_COLOR_BUFFER_BIT);

        mBinded = true;
    }
}

void FrameBuffer::release()
{
    if (mBinded)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mOldFrameBufferId);
        mBinded = false;
    }
}
