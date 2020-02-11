#include "window.h"

int main( void ) {
    
    window_init( "SDL2 + OpenGL", 640, 480 );
    
    // main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;

    //enable text input
    SDL_StartTextInput();

    //while application is running
    while( !quit ) {

        while ( SDL_PollEvent( &e ) != 0 ) {

            // User requests quit
            if( e.type == SDL_QUIT ) {
                quit = 1;
            }

            // handle keypress with current mouse position
            else if( e.type == SDL_TEXTINPUT ) {
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                handle_keys( e.text.text[0], x, y );
            }
        }

        // Render quad
        render();

        // Update screen
        update();
    }

    // disable text input
    SDL_StopTextInput();
    window_quit();

    return 0;
}