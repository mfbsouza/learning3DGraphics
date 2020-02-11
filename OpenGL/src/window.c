#include "window.h"

SDL_Window *  mainWindow = NULL;
SDL_GLContext mainContext;
int grenderQuad = 1;

int init_gl( void ) {
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return EXIT_FAILURE;
    }

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return EXIT_FAILURE;
    }

    // Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void window_init( const char *window_title, const int screen_width, const int screen_height ) {
    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Failed initializing window: %s\n", SDL_GetError( ) );
        exit( EXIT_FAILURE );
    }

    // Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    // Create Window
    mainWindow = SDL_CreateWindow(
        window_title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if( mainWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError( ) );
        exit( EXIT_FAILURE );
    }

    // Create context
    mainContext = SDL_GL_CreateContext( mainWindow );
    if( mainContext == NULL ) {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError( ) );
        exit( EXIT_FAILURE );
    }

    // Use Vsync TODO: use double buffer
    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError( ) );
    }

    // Initialize OpenGL
    if( init_gl() != EXIT_SUCCESS ) {
        printf( "Unable to initialize OpenGL!\n" );
    }
}

void window_quit( void ) {
    //Destroy window
    SDL_DestroyWindow( mainWindow );
    mainWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void handle_keys( unsigned char key, int x, int y ) {
    // toggle quad
    if( key == 'q' ) {
        if(grenderQuad == 1) grenderQuad = 0;
        else grenderQuad = 1;
    }
}

void update( void ) {
    SDL_GL_SwapWindow( mainWindow );
}

void render ( void ) {
    // Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    // Render quad
    if( grenderQuad ) {
        glBegin( GL_QUADS );
            glVertex2f( -0.5f, -0.5f );
            glVertex2f(  0.5f, -0.5f );
            glVertex2f(  0.5f,  0.5f );
            glVertex2f( -0.5f,  0.5f );
        glEnd(); 
    }
}