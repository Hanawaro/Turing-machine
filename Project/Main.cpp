#include <iostream>

#include "Application.hpp"

#define WIN_WIDTH    800
#define WIN_HEIGHT   600
#define WIN_X_POS    800
#define WIN_Y_POS    190

int main(int argc, char** argv) {
    {
        Application app("Application", WIN_WIDTH, WIN_HEIGHT, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
        while (app.isRunning()) {
            app.Update();
            app.Render();
            app.HandleEvent();
        }
    }

    return 0;
}
