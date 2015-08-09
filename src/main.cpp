#include <GL/glew.h>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <complex>
#include <iostream>
#include <fstream>


GLuint p;
const int window_width = 800;
const int window_height = 600;
int origin_x = window_width / 2;
int origin_y = window_height / 2;
const int n_max = 200;
double scale = 6. / window_width;
float cx = -0.74;
float cy = 0.14;

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
            cy += 0.01;
            break;
        case 's':
            cy -= 0.01;
            break;
        case 'a':
            cx -= 0.01;
            break;
        case 'd':
            cx += 0.01;
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
    std::cout << cx << ", " << cy << std::endl;
    glutPostRedisplay();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glUniform2f(glGetUniformLocation(p, "c"), cx, cy);
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

    glUseProgram(p);
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
