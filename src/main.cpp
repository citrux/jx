#include "glm/vec2.hpp"
#include <iostream>
#include "window.hpp"
#include "shader.hpp"

struct Fractal {
    float scale;
    glm::vec2 origin;

    int iterations;

    GLuint program;
};

Window* w;
Fractal julia = {3.0, {0.5, 0.5}, 100, 0};
Fractal mbrot = {3.0, {0.5, 0.5}, 100, 0};
bool show_julia = false;
float scale_factor = 1.2;
glm::vec2 center(0.5, 0.5);
glm::vec2 c(-0.74, 0.14);
Fractal* current = &julia;

void special_input(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            current->origin.y -= 0.05;
            break;
        case GLUT_KEY_DOWN:
            current->origin.y += 0.05;
            break;
        case GLUT_KEY_LEFT:
            current->origin.x += 0.05;
            break;
        case GLUT_KEY_RIGHT:
            current->origin.x -= 0.05;
            break;
    }
    glutPostRedisplay();
}

void input(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            c.y += 0.001;
            break;
        case 's':
            c.y -= 0.001;
            break;
        case 'a':
            c.x -= 0.001;
            break;
        case 'd':
            c.x += 0.001;
            break;
        case '-':
            current->iterations -= 10;
            break;
        case '=':
            current->iterations += 10;
            break;
        case '_':
            current->iterations -= int(0.2 * current->iterations);
            break;
        case '+':
            current->iterations += int(0.2*current->iterations);
            break;
        case '0':
            current->scale /= scale_factor;
            current->origin = center + (current->origin - center) * scale_factor;
            break;
        case '9':
            current->scale *= scale_factor;
            current->origin = center + (current->origin - center) / scale_factor;
            break;
        case 'm':
            show_julia = !show_julia;
            break;
        case 'q':
            exit(0);
            break;
    }
    std::cout << c.x << ", " << c.y << std::endl;
    glutPostRedisplay();
}

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    if (show_julia)
        current = &julia;
    else
        current = &mbrot;

    glUseProgram(current->program);

    auto max_size = std::max(w->height, w->width);
    auto scale = glm::vec2(current->scale / max_size * w->width, current->scale / max_size * w->height);
    glUniform2f(glGetUniformLocation(current->program, "c"), c.x, c.y);
    glUniform2f(glGetUniformLocation(current->program, "scale"), scale.x, scale.y);
    glUniform2f(glGetUniformLocation(current->program, "o"), current->origin.x, current->origin.y);
    glUniform1i(glGetUniformLocation(current->program, "iter"), current->iterations);

    glBegin(GL_POLYGON);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glEnd();

    glUseProgram(0);
    glutSwapBuffers();
}



void reshape(int width, int height) {
    w->width=width;
    w->height=height;

    glViewport(0, 0, w->width, w->height);
};

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    w = new Window("Julia set", 800, 600);
    w->setInput(input);
    w->setSpecialInput(special_input);
    w->setRender(render);
    w->setReshape(reshape);

    auto shader = compileShader("./src/julia.glsl", GL_FRAGMENT_SHADER);
    auto p = glCreateProgram();
    addShader(p, shader);
    julia.program = p;

    shader = compileShader("./src/mbrot.glsl", GL_FRAGMENT_SHADER);
    p = glCreateProgram();
    addShader(p, shader);
    mbrot.program = p;

    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
