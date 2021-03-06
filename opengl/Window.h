//
// Created by lidan on 2021/2/25.
//

#ifndef VR_WINDOW_H
#define VR_WINDOW_H


#include "util.h"
#include "Rectangle.h"
#include "Cam.h"

class Window {

private:
    bool isMouseDown ;
    SDL_Window *_window ;
    SDL_DisplayMode  _mode ;
    SDL_GLContext _context ;
    RectangleF<float> *_rect, *_drawrect ;
    Camera* ca ;


public:
    Window() ;
    ~Window() ;

    int posX() const ;
    int posY() const ;

    int width() ;
    int height() ;

    const RectangleF<float>* rect() const { return _rect; }
    const RectangleF<float>* drawRect() const { return _drawrect; }

    void run() ;
    void move(int x, int y) ;
    void resize(int w, int h) ;

    void setTitle(const char* title) ;
    void setWindowIcon(const unsigned char* pixels, int w, int h, int n) ;

protected:
    virtual void initilizeGL() ;
    virtual void resizeGL(int w, int h ) ;
    virtual void renderGL() ;
    virtual void keydownEvent(SDL_KeyboardEvent *event) ;
    virtual void keyupEvent(SDL_KeyboardEvent *event);
    virtual void mouseButtonUpEvent(SDL_MouseButtonEvent *event);
    virtual void mouseButtonDownEvent(SDL_MouseButtonEvent *event);
    virtual void mouseMotionEvent(SDL_MouseMotionEvent *event);

private:
    void createWindow() ;
    void closeWindow() ;
};


#endif //VR_WINDOW_H
