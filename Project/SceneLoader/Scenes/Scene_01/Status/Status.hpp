#ifndef Status_hpp
#define Status_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>

#include <Logger.hpp>

#include "../../../../Entity/Window/Window.hpp"
#include "../../../../Entity/Texture/Texture.hpp"
#include "../../../../Entity/Text/Text.hpp"
#include <vector>
#include <string>

struct Font {
    TextEntity* data = nullptr;
    int width = 0;
    int height = 0;
};

struct Button {
    TextureEntity* Disable  = nullptr;
    TextureEntity* Touch    = nullptr;
    TextureEntity* Active   = nullptr;
    TextureEntity* Enable   = nullptr;
    int width = 0;
    int height = 0;
};

struct SideBar {
    int x1, x2, y1, y2;
    int amount;
};

class Status {
public:
    // amount of cells on the tape
    static const int amountOfCells   = 15;
    // maximal length of alphabet
    static const int maximalOfLength = 14;
    // maximal steps of algorithm
    static const int maximalOfSteps  = 10;
    
    // program status
    enum class DeepStatus {
        Empty,
        Process,
        Pause,
        NextStep,
        End,
        InputBar,
        Cells
    };
    static DeepStatus status;
    
    // the tape
    static std::vector<char> tape;
    
    // the bias for the tape
    static int bias;
    
    // the algorithm
    static std::vector<std::vector<std::string>> algorithm;
    
    // the alphabet
    static std::string alphabet;
    
    // the side bar for the tape
    static SideBar sideBar;
    
    // resize for the screen
    static double resizeHorizontal;
    static double resizeVertical;
};

#endif
