#include <GL/glew.h>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
#include <fstream>


GLuint p;
const int window_width = 800;
const int window_height = 600;
int max_size = window_height;
int origin_x = window_width / 2;
int origin_y = window_height / 2;
int n_max = 200;

float scalex = 5. / max_size * window_width;
float scaley = 5. / max_size * window_height;

float ox = 0.5;
float oy = 0.5;

float cx = -0.24;
float cy = 0.14;

void special_input(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            oy -= 0.05;
            break;
        case GLUT_KEY_DOWN:
            oy += 0.05;
            break;
        case GLUT_KEY_LEFT:
            ox += 0.05;
            break;
        case GLUT_KEY_RIGHT:
            ox -= 0.05;
            break;
    }
    glutPostRedisplay();
}

void input(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            cy += 0.001;
            break;
        case 's':
            cy -= 0.001;
            break;
        case 'a':
            cx -= 0.001;
            break;
        case 'd':
            cx += 0.001;
            break;
        case '-':
            n_max -= 10;
            break;
        case '=':
            n_max += 10;
            break;
        case '_':
            n_max -= int(0.2 * n_max);
            break;
        case '+':
            n_max += int(0.2*n_max);
            break;
        case '0':
            scalex /= 1.2;
            scaley /= 1.2;
            ox = 0.5 + (ox - 0.5) * 1.2;
            oy = 0.5 + (oy - 0.5) * 1.2;
            break;
        case '9':
            scalex *= 1.2;
            scaley *= 1.2;
            ox = 0.5 + (ox - 0.5) / 1.2;
            oy = 0.5 + (oy - 0.5) / 1.2;
            break;
        case 'q':
            exit(0);
            break;
    }
    std::cout << cx << ", " << cy << std::endl;
    glutPostRedisplay();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glUseProgram(p);

    glUniform2f(glGetUniformLocation(p, "c"), cx, cy);
    glUniform2f(glGetUniformLocation(p, "scale"), scalex, scaley);
    glUniform2f(glGetUniformLocation(p, "o"), ox, oy);
    glUniform1i(glGetUniformLocation(p, "iter"), n_max);

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

void setShaders() {
    GLuint v;

    // get a shader handler
    v = glCreateShader(GL_FRAGMENT_SHADER);
    // read the shader source from a file
    std::ifstream is("src/julia.glsl", std::ios::in|std::ios::binary|std::ios::ate);
	if (!is.is_open()) {
		std::cerr << "Unable to open file " << "src/julia.glsl" << std::endl;
		exit(1);
	}
	long size = is.tellg();
	char *vs = new char[size+1];
	is.seekg(0, std::ios::beg);
	is.read (vs, size);
	is.close();
	vs[size] = 0;

    // conversions to fit the next function
    const char *vv = vs;
    // pass the source text to GL
    glShaderSource(v, 1, &vv,NULL);
    // free the memory from the source text
    delete[] vs;
    // finally compile the shader
    glCompileShader(v);

    p = glCreateProgram();
    glAttachShader(p, v);
    glLinkProgram(p);
};

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(window_width, window_height);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Julia set explorer"); // Create a window with the given title
    glutSpecialFunc(special_input);
    glutKeyboardFunc(input);
    glutDisplayFunc(display); // Register display callback handler for window re-paint

    glewInit();
	setShaders();

    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
