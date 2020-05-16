#ifndef PauseButton_hpp
#define PauseButton_hpp

#include "../../Status/Status.hpp"

class PauseButton {
public:
    PauseButton(SDL_Renderer* l_Renderer);
    ~PauseButton(void);
    
    void draw(void);
    void touch(void);
    void active(void);
    void set(void);
    void disable(void);
    
    void clear(void);
    void deepClear(void);
public:
    const int width = 50;
    const int height = 50;
    
    const int x1 = 135;
    const int y1 = 25;
    
    const int x2 = x1 + width;
    const int y2 = y1 + height;
private:
    const std::string m_Path = "Source/Sprite/Pause/";
    
    SDL_Renderer* m_Renderer = nullptr;
    
    enum class Locale {
        Up,
        Down,
        Touch
    };
    Locale m_Locale = Locale::Up;
    
    Button m_Texture;
};

#endif
