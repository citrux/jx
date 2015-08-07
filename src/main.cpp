#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <complex>
#include <iostream>

struct rgb{
    float r, g, b;
};

const int window_width = 800;
const int window_height = 600;
int origin_x = window_width / 2;
int origin_y = window_height / 2;
const int n_max = 200;
double scale = 6. / window_width;
auto c = std::complex<double>(-0.74, 0.14);

struct rgb pixels[841*1440], palette[n_max + 1];

void special_input(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            origin_y -= 5;
            break;
        case GLUT_KEY_DOWN:
            origin_y += 5;
            break;
        case GLUT_KEY_LEFT:
            origin_x += 5;
            break;
        case GLUT_KEY_RIGHT:
            origin_x -= 5;
            break;
    }
    glutPostRedisplay();
}

void input(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            c += std::complex<double>(0, 0.01);
            break;
        case 's':
            c -= std::complex<double>(0, 0.01);
            break;
        case 'a':
            c -= std::complex<double>(0.01, 0);
            break;
        case 'd':
            c += std::complex<double>(0.01, 0);
            break;
        case '0':
            scale /= 1.2;
            origin_x = window_width / 2 + (origin_x - window_width / 2) / 1.2;
            origin_y = window_width / 2 + (origin_y - window_width / 2) / 1.2;
            break;
        case '9':
            scale *= 1.2;
            origin_x = window_width / 2 + (origin_x - window_width / 2) * 1.2;
            origin_y = window_width / 2 + (origin_y - window_width / 2) * 1.2;
            break;
        case 'q':
            exit(0);
            break;
    }
    std::cout << c << std::endl;
    glutPostRedisplay();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    auto r = (1 + sqrt(1 + 4 * abs(c))) / 2;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < window_height; ++i)
        for (int j = 0; j < window_width; ++j) {
            double x = (j - origin_x) * scale;
            double y = (origin_y - i) * scale;
            auto z = std::complex<double>(x, y);

            int n = 0;
            for (n = 0; n < n_max; ++n)
            {
                z = z * z + c;
                if (abs(z) > r)
                    break;
            }

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
    glutSpecialFunc(special_input);
    glutKeyboardFunc(input);
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
