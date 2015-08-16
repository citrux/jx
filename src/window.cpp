#include "window.hpp"

Window::Window(std::string title, int width, int height) :
    width(width), height(height)
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(width, height);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title.c_str()); // Create a window with the given title
    glewInit();
}

void Window::setSpecialInput(void(*f)(int key, int x, int y)) {glutSpecialFunc(f);};
void Window::setInput(void(*f)(unsigned char key, int x, int y)) {glutKeyboardFunc(f);};
void Window::setRender(void(*f)()) {glutDisplayFunc(f);};
void Window::setReshape(void(*f)(int w, int h)) {glutReshapeFunc(f);};


