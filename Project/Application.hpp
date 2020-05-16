#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <Logger.hpp>

#include "Entity/Window/Window.hpp"
#include "SceneLoader/SceneLoader.hpp"

struct Timer {
    double last_tick = 0;
    double delta = 0;

    void tick(void) {
        double new_tick = (double) SDL_GetTicks();
        delta = new_tick - last_tick;
        last_tick = new_tick;
    }
};

class Application {
public:
    Application(const std::string& l_Title, Uint16 l_Width, Uint16 l_Height, Uint32 l_PosX, Uint32 l_PosY, Uint32 l_Flag);
    ~Application(void);

    bool isRunning(void) const;

    void HandleEvent(void);
    void Update(void);
    void Render(void);
private:
    void init(const char* l_Title , Uint16 l_Width, Uint16 l_Height, Uint32 l_PosX, Uint32 l_PosY, Uint32 l_Flag);
    void destroy(void);
private:
    WindowEntity* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    SceneLoader* m_SceneLoader = nullptr;
    SDL_Event m_Event;

    Timer m_Timer;
    double m_Accumulator = 0;

    const double m_Limit = 1.0 / 120.0;

    bool m_isRunning = false;
    bool m_initFlag = false;
};

#endif
