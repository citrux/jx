#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include "iterations.hpp"

struct rgb{
    float r, g, b;
};

const int window_width = 800;
const int window_height = 600;
const int n_max = 200;
const double scale = 6. / window_width;
auto c = std::complex<double>(-0.74, 0.14);

struct rgb pixels[841*1440], palette[n_max + 1];
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < window_height; ++i)
        for (int j = 0; j < window_width; ++j) {
            double x = (j - window_width / 2) * scale;
            double y = (window_height / 2 - i) * scale;
            int n = iterations(std::complex<double>(x, y), c, n_max);
            pixels[i * window_width + j] = palette[n];
        }

    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    glutSwapBuffers();
}

void init() {
    for (int i = 0; i < n_max+1; ++i) {
        float c = (float) i / (n_max+1);
        palette[i] = {c, c, c};
    }
}
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(window_width, window_height);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Julia set explorer"); // Create a window with the given title
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
