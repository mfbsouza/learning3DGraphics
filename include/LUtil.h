#include "LOpenGL.h"

// Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

/* Pre Condition: 
    - a Valid OpenGL context 
   Post Condition: 
    - Initializes matrices and clear color
    - Reports to console if there was an OpenGL error
    - Returns false if there was an error in initialization
   Side Effects:
    - Projection matrix is set to identity matrix
    - Modelview matrix is set to identity matrix
    - Matrix mode is set to modelview
    - Clear color is set to black
 */

int initGL() {
    // Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    // Check for error
    GLenum error = glGetError();
    if ( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL %s\n", gluErrorString( error ) );
        return 0; // FALSE FLAG
    }

    return 1; // TRUE FLAG
}

/* Pre Condition:
    - None
   Post Condition:
    - Does per frame logic
   Side Effects:
    - None
*/

void update() {

}

/* Pre Condition:
    - A valid OpenGL context
    - Active modelview matrix
   Post Condition:
    - Renders the scene
   Side Effects:
    - Clears the color buffer
    - Swaps the front/back buffer
*/

void render() {
    // Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    // Render quad
    glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
    glEnd();

    // Update screen
    glutSwapBuffers();
}