#ifndef SCENE_01_HPP
#define SCENE_01_HPP

#include "../Scene.hpp"
#include "Status/Status.hpp"
#include "Core/Core.hpp"

#define WIN_WIDTH    800.0
#define WIN_HEIGHT   600.0

class Scene_01 : public Scene {
public:
    Scene_01(SDL_Renderer* l_Renderer);
    ~Scene_01(void);
    
    void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
    void Clear(void);

    void HandleEvent(SDL_Event* l_Event);
    void draw(void);
    void Update(double l_Time);
private:
    const std::string m_Path = "Source/Sprite/Background.png";
    
    TextureEntity* m_Background = nullptr;
    int m_BG_width = 0;
    int m_BG_height = 0;
    
    int x = 0;
    int y = 0;
    
    // Controller
    Button m_Start;
    Button m_Stop;
    Button m_Pause;
    Button m_Next;
    Button m_Left;
    Button m_Right;
    
    // Tape
    TextureEntity* LeftButton = nullptr;
    TextureEntity* RightButton = nullptr;
    
    // Core class
    Core core;
};

#endif
