#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameObject.h"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;  // Milliseconds per frame

// Camera position
float cameraX = 0.0f, cameraY = 5.0f, cameraZ = 20.0f;
float lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = 0.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

GLfloat lightPosition[] = { 10.0f, 10.0f, 10.0f, 1.0f };

GameObject platform;
Model model;

// Initialization
void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color
    glViewport(0, 0, WIDTH, HEIGHT);  // Set viewport

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)WIDTH / (float)HEIGHT, 0.1, 100.0);

    model.load("models/platformBasic.obj");
    platform.Initialize(model);

    // Switch to model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Draw XYZ axes
void drawAxes() {
    glBegin(GL_LINES);
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
    glLoadIdentity();

    // Set up the camera
    gluLookAt(cameraX, cameraY, cameraZ,  // Camera position
        lookAtX, lookAtY, lookAtZ,  // Look at the origin
        upX, upY, upZ);             // Up vector

    glPushMatrix();  // Save the current matrix state

    // Apply a transformation to the model
    glTranslatef(5.0f, 0.0f, 0.0f);  // Move the model 5 units along the X-axis

    platform.Render();  // Render the model (all vertices are transformed by the current matrix)

    glPopMatrix();
    drawAxes();

    glutSwapBuffers();
}

// Update function
void update(int value) {
    platform.Update();

    // Redisplay the scene
    glutPostRedisplay();

    // Schedule the next update
    glutTimerFunc(FRAME_DELAY, update, 0);
}

// Keyboard input for camera movement
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': cameraZ -= 1.0f; break;  // Move forward
    case 's': cameraZ += 1.0f; break;  // Move backward
    case 'a': cameraX -= 1.0f; break;  // Move left
    case 'd': cameraX += 1.0f; break;  // Move right
    case 'q': cameraY += 1.0f; break;  // Move up
    case 'e': cameraY -= 1.0f; break;  // Move down
    case 27: exit(0); break;           // Escape key to exit
    }
    glutPostRedisplay();  // Redraw the scene
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Double buffer, RGB color, Depth buffer
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Scene with XYZ Axes");

    glewInit();

    init();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback
    glutKeyboardFunc(keyboard);  // Register keyboard callback

    // Start the update loop
    glutTimerFunc(FRAME_DELAY, update, 0);

    glutMainLoop();  // Enter GLUT event processing loop

    return 0;
}