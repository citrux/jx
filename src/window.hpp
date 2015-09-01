#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>


class Window {
    public:
        Window(std::string title, int width, int height);
        int width, height;

        void setSpecialInput(void(*)(int key, int x, int y));
        void setInput(void(*)(unsigned char key, int x, int y));
        void setMouse(void(*)(int button, int state, int x, int y));
        void setRender(void(*)());
        void setReshape(void(*)(int w, int h));
        void setMotion(void(*)(int x, int y));
};
