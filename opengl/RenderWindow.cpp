//
// Created by lidan on 2021/3/2.
//
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


#include "RenderWindow.h"
#include "Rectangle.h"
#include "ShaderProgram.h"
#include "Sample2D.h"
#include "util.h"
#include "stb_image.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "ShaderToy.h"



int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

#define NUMBER(n) n < 10 ? 0 : int(n / 10)

GLfloat vertices[] = {
        -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  0.0f,  0.0f,  0.0f
};

GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
};


static struct tm *t;

inline static float mseconds()
{

//#ifdef WIN32
////    return 0.0f;
//#else
//    static struct timeval tv;
//    gettimeofday(&tv, nullptr);
//    t = localtime(&tv.tv_sec);
//    return tv.tv_usec * 0.000001f;
//#endif
    static struct timeval tv;
    gettimeofday(&tv, nullptr);
    t = _localtime32(&tv.tv_sec);
    return tv.tv_usec * 0.000001f;
}



RenderWindow::RenderWindow()
: mVAO(nullptr),
mVBOArray(nullptr),
mVBOIndex(nullptr),
mProgram(nullptr)
{
    createIcon(icon, 4684);
}

RenderWindow::~RenderWindow()
{
    delete mVAO;
    delete mVBOArray;
    delete mVBOIndex;
    delete mProgram;

    auto size = mTextures.size();
    for (int i = 0; i < size; i++)
        delete mTextures[i];
}

void RenderWindow::addTexture(std::vector<const char *> &texFileNames)
{
    auto size = texFileNames.size();
    for (int i = 0; i < size; i++)
    {
        Sample2D *texture = new Sample2D(GL_TEXTURE_2D,std::string(texFileNames[i]), GL_REPEAT, GL_LINEAR, true, true);
        texture->loadByFile();
        if (texture->isLoaded())
        {
            texture->bindToPipLine(i);
            mTextures.push_back(texture);
        }
    }
}

void RenderWindow::addUserFragmentMainCode(const char *fragmentMain)
{
    char buffer[0x20];
    std::string fragment = std::string(fragmentShaderPassHeader);

    auto size = mTextures.size();
    for (int i = 0; i < size; i++)
    {
        sprintf(buffer, "uniform sampler2D iChannel%d;\n", i);
        fragment.append(buffer);
    }

    fragment.append(fragmentMain);
    fragment.append(fragmentShaderPassFooter);

#ifdef DEBUG
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s\n", fragment.c_str());
#endif

    mProgram = new ShaderProgram();
    mProgram->addShaderFromSource(ShaderType::VS, vertexShader);
    mProgram->addShaderFromSource(ShaderType::FG, fragment.c_str());
    mProgram->link();

    if (!mProgram->isLinked())
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Linked Error: %s", mProgram->log().c_str());
}

void RenderWindow::initilizeGL()
{
    timer.init();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mVAO = new VertexArrayObject();
    mVAO->create();
    mVAO->bind();

    mVBOArray = new BufferObject(GL_ARRAY_BUFFER);
    mVBOArray->create();
    mVBOArray->bind();
    mVBOArray->setUsagePattern(GL_STATIC_DRAW);
    mVBOArray->allocate(vertices, sizeof(vertices));

    initilizeUniformValue();

    mProgram->enableAttributeArray(0);
    mProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 5);
    mProgram->enableAttributeArray(1);
    mProgram->setAttributeBuffer(1, GL_FLOAT, 3, 2, 5 * sizeof(GLfloat));

    mVBOIndex = new BufferObject(GL_ELEMENT_ARRAY_BUFFER);
    mVBOIndex->create();
    mVBOIndex->setUsagePattern(GL_STATIC_DRAW);
    mVBOIndex->bind();
    mVBOIndex->allocate(indices, sizeof(indices));

    mVAO->release();
    mProgram->release();
}
void RenderWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, GLsizei(w), GLsizei(h));

    mInput.iResolution[0] = (w * 1.0f);
    mInput.iResolution[1] = (h * 1.0f);
    Window::resizeGL(w, h);
}
void RenderWindow::renderGL()
{
    float ms = mseconds();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto size = mTextures.size();
    for (int i = 0; i < size; i++)
        mTextures[i]->bindToPipLine(i);

    mProgram->bind();

    mInput.iTime = timer.globalTime() / 1000.0f;
    mInput.iGlobalTime = mInput.iTime;

    mInput.iDate[0] = (t->tm_year + 1900.0f);
    mInput.iDate[1] = ((float)t->tm_mon);
    mInput.iDate[2] = ((float)t->tm_mday);
    mInput.iDate[3] = (t->tm_hour * 60.0f * 60.0f +
                      t->tm_min * 60.0f + (float)t->tm_sec + 0.0f);

    mInput.iFrame += timer.frameCount();
    mInput.iTimeDelta =  timer.frameRateDelay() / 1000.0f;
    mInput.iFrameRate = 1.0f / mInput.iTimeDelta;

    bindUniform();

    mVAO->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    mVAO->release();

    sprintf(title, "ShaderToy FPS: %-2.2f", mInput.iFrameRate);
    setTitle(title);
    Window::renderGL();
}

void RenderWindow::keydownEvent(SDL_KeyboardEvent *event)
{
    if (event->keysym.sym == SDLK_x)
    {

    }
}
void RenderWindow::mouseButtonUpEvent(SDL_MouseButtonEvent *event)
{
    mInput.iMouse[2] = (-Math::abs(mInput.iMouse.b()));
    mInput.iMouse[3] = (-Math::abs(mInput.iMouse.a()));
}
void RenderWindow::mouseButtonDownEvent(SDL_MouseButtonEvent *event)
{
    const RectangleF<float> *rect = drawRect();
    mInput.iMouse[2] =(Math::floor((event->x - rect->left()) / rect->width() * width()));
    mInput.iMouse[3] =(Math::floor(height() - (event->y - rect->top()) / rect->height() * height()));
    mInput.iMouse[0] =(mInput.iMouse.b());
    mInput.iMouse[1] = (mInput.iMouse.a());
}
void RenderWindow::mouseMotionEvent(SDL_MouseMotionEvent *event)
{
    const RectangleF<float>* winrect = rect();
    const RectangleF<float>* drawrect = drawRect();

    float widthRatio = drawrect->width() / winrect->width();
    float heightRatio = drawrect->height() / winrect->height();

    mInput.iMouse[0] = (Math::floor(event->x - drawrect->left()) * widthRatio);
    mInput.iMouse[1] = (Math::floor(height() - (event->y - drawrect->top()) * heightRatio));
}

void RenderWindow::createIcon(const unsigned char *buffer, size_t size)
{
    stbi_set_flip_vertically_on_load(0);

    int w, h, n;
    stbi_uc *pixels = stbi_load_from_memory(icon, size, &w, &h, &n, STBI_rgb_alpha);
    setWindowIcon(pixels, w, h, n);
    stbi_image_free(pixels);
}

void RenderWindow::initilizeUniformValue()
{
    mInput.iResolution  = Vec3(width() * 1.0f, height() * 1.0f, 1.0f);
    mInput.iTime        = 0.0f;
    mInput.iGlobalTime  = 0.0f;
    mInput.iMouse       = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    mInput.iDate        = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    mInput.iSampleRate  = 44100 * 1.0f;

    auto size = mTextures.size();

    if (size <= 4)
    {
        for (int i = 0; i < size; i++)
        {
            mInput.iChannelResolution[i] = Vec3(mTextures[i]->width(),
                                                   mTextures[i]->height(),
                                                   1.0f);
            mInput.iChannelTime[i] = 0.0f;
        }
    }

    mInput.iFrame       = 0;
    mInput.iTimeDelta   = 0.0f;
    mInput.iFrameRate   = 0.0f;
}

void RenderWindow::bindUniform()
{
    if (mProgram != nullptr) {
        mProgram->setUniformValue("iResolution", mInput.iResolution);
        mProgram->setUniformValue("iTime", mInput.iTime);
        mProgram->setUniformValue("iGlobalTime", mInput.iGlobalTime);
        mProgram->setUniformValue("iMouse", mInput.iMouse);
        mProgram->setUniformValue("iDate", mInput.iDate);
        mProgram->setUniformValue("iSampleRate", mInput.iSampleRate);
        mProgram->setUniformValueArray("iChannelResolution", mInput.iChannelResolution, 4);
        mProgram->setUniformValueArray("iChannelTime", mInput.iChannelTime, 4, 1);
        mProgram->setUniformValue("iTimeDelta", mInput.iTimeDelta);
        mProgram->setUniformValue("iFrame", mInput.iFrame);
        mProgram->setUniformValue("iFrameRate", mInput.iFrameRate);

        mProgram->setUniformValue("iChannel0", 0);
        mProgram->setUniformValue("iChannel1", 1);
        mProgram->setUniformValue("iChannel2", 2);
        mProgram->setUniformValue("iChannel3", 3);

        mProgram->setUniformValue("iChannel[0].resolution", mInput.iChannelResolution[0]);
        mProgram->setUniformValue("iChannel[1].resolution", mInput.iChannelResolution[1]);
        mProgram->setUniformValue("iChannel[2].resolution", mInput.iChannelResolution[2]);
        mProgram->setUniformValue("iChannel[3].resolution", mInput.iChannelResolution[3]);

        mProgram->setUniformValue("iChannel[0].time", mInput.iChannelTime[0]);
        mProgram->setUniformValue("iChannel[1].time", mInput.iChannelTime[1]);
        mProgram->setUniformValue("iChannel[2].time", mInput.iChannelTime[2]);
        mProgram->setUniformValue("iChannel[3].time", mInput.iChannelTime[3]);
    }
}

