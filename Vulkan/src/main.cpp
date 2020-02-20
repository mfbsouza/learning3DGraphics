#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

const char* app_name = "Vulkan Tutorial";
const int window_width = 800, window_height = 600;

void init_window();
void kill_window();
void main_loop();

SDL_Window* window = nullptr;


int main () {
    init_window();
    main_loop();
    kill_window();
    return 0;
}

void init_window () {   
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    
    window =SDL_CreateWindow(
        app_name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!window) {
        std::cout << "Failed to crete SDL Vulkan Window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void kill_window () {
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Cleaned up" << std::endl;
}

void main_loop () {
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
    }
}