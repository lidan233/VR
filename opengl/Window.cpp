//
// Created by lidan on 2021/2/28.
//

#include "Window.h"

Window::Window()
:_window(nullptr) ,
_context(nullptr) ,
_rect(nullptr),
_drawrect(nullptr)
{
    createWindow() ;
    ca = new Camera(Vec3(650,0,650)) ;
}

Window::~Window() 
{
    
}

void Window::createWindow()

{
    _mode.w = 800 ;
    _mode.h = 600 ;

    if (SDL_WasInit(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initilize SDL: %s",
                     SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    _window = SDL_CreateWindow("ShaderToy",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _mode.w, _mode.h,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

    if (!_window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s",
                     SDL_GetError());
        return;
    }

    SDL_GetWindowDisplayMode(_window, &_mode);

    _context = SDL_GL_CreateContext(_window);
    if (!_context)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create OpenGL Context: %s",
                     SDL_GetError());
        SDL_DestroyWindow(_window);
        return;
    }

    int x, y, w, h;
    SDL_GetWindowPosition(_window, &x, &y);
    SDL_GL_GetDrawableSize(_window, &w, &h);

    _rect = new RectangleF<float>(y, y + _mode.h, x, x + _mode.w);
    _drawrect = new RectangleF<float>(0, h, 0, w);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Glad initalize failed" << std::endl;
        exit(EXIT_FAILURE);
    }



    SDL_GL_SetSwapInterval(1);
}

void Window::closeWindow() 
{
    if (_context)
        SDL_GL_DeleteContext(_context);

    if (_window)
        SDL_DestroyWindow(_window);

    if (_rect)
        delete _rect;

    _context = nullptr;
    _window = nullptr;
    _rect = nullptr;
}


int Window::posX() const 
{
    return _window != nullptr ? _rect->x() : SDL_WINDOWPOS_CENTERED ;

}

int Window::posY() const 
{
    return _window != nullptr ? _rect->y() : SDL_WINDOWPOS_CENTERED ;
}

int Window::width()
{
    return _window != nullptr ? _rect->width() : SDL_WINDOWPOS_CENTERED ;
}

int Window::height()
{
    return _window != nullptr ? _rect->height() : SDL_WINDOWPOS_CENTERED ;
}

void Window::run()
{
    if (!_window && !_context)
        return ;

    bool done = true;
    SDL_Event event;

    initilizeGL();

    while (done)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    keydownEvent(&event.key);
                    break;

                case SDL_KEYUP:
                    keyupEvent(&event.key);
                    break;

                case SDL_MOUSEBUTTONUP:
                    isMouseDown = false;
                    mouseButtonUpEvent(&event.button);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    isMouseDown = true;
                    mouseButtonDownEvent(&event.button);
                    break;

                case SDL_MOUSEMOTION:
                    if (isMouseDown == true)
                        mouseMotionEvent(&event.motion);
                    break;

                case SDL_WINDOWEVENT:
                {
                    Uint8 windowEvent = event.window.event;
                    if (windowEvent == SDL_WINDOWEVENT_RESIZED ||
                        windowEvent == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        int w, h;
                        SDL_GetWindowSize(_window, &w, &h);
                        _rect->setWidth(w);
                        _rect->setHeight(h);

                        SDL_GL_GetDrawableSize(_window, &w, &h);
                        _drawrect->setWidth(w);
                        _drawrect->setHeight(h);
                        resizeGL(w, h);
                    }
                    else if (windowEvent == SDL_WINDOWEVENT_MOVED)
                    {
                        int x, y;
                        SDL_GetWindowPosition(_window, &x, &y);
                        _rect->setX(x);
                        _rect->setY(y);
                    }
                }
                    break;

                case SDL_QUIT:
                    done = false;
                    break;

                default:
                    break;
            }
        }

        renderGL();
    }

    return;
}

void Window::move(int x, int y)
{
    if (_window)
    {
        SDL_SetWindowPosition(_window, x, y);
    }
}

void Window::resize(int w, int h)
{
    if (_window)
    {
        SDL_SetWindowSize(_window, w, h);
    }
}

void Window::setTitle(const char* title)
{
    if (_window)
    {
        SDL_SetWindowTitle(_window, title);
    }
}

void Window::setWindowIcon(const unsigned char* pixels, int w, int h, int n)
{
    SDL_Surface *icon = SDL_CreateRGBSurfaceWithFormatFrom((void *)pixels, w, h, n, w * n, SDL_PIXELFORMAT_RGBA32);
    if (icon == nullptr)
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());

    SDL_SetWindowIcon(_window, icon);
    SDL_FreeSurface(icon);
}


void Window::initilizeGL() 
{
    
}

void Window::resizeGL(int w, int h )
{

}

void Window::renderGL()
{
    SDL_GL_SwapWindow(_window);
}

void Window::keydownEvent(SDL_KeyboardEvent *event)
{

}

void Window::keyupEvent(SDL_KeyboardEvent *event)
{
    switch (event->keysym.sym) {
        case SDLK_ESCAPE: return  ; break ;
        case SDLK_w: ca->ProcessKeyboard(FORWARD,0.1) ;break ;
        case SDLK_a: ca->ProcessKeyboard(LEFT,0.1); break ;
        case SDLK_s: ca->ProcessKeyboard(BACKWARD,0.1); break ;
        case SDLK_d: ca->ProcessKeyboard(RIGHT,0.1);break ;
    }
}

void Window::mouseButtonUpEvent(SDL_MouseButtonEvent *event)
{

}

void Window::mouseButtonDownEvent(SDL_MouseButtonEvent *event)
{

}

void Window::mouseMotionEvent(SDL_MouseMotionEvent *event)
{

}





