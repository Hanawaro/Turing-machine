#ifndef InputBar_hpp
#define InputBar_hpp

#include "../../Status/Status.hpp"

class InputBar {
public:
    InputBar(SDL_Renderer* l_Renderer);
    ~InputBar(void);
    void draw(void);
    void touch(void);
    void set(void);
    void disable(void);
    void clear(void);
    
    void handle(SDL_Event* l_Event);
public:
    const int width  = 140;
    const int height = 26;
    
    const int x1 = 620;
    const int x2 = x1 + width;
    const int y1 = 37;
    const int y2 = y1 + height;
    
    const std::string m_Path = "Source/Font/Menlo.ttf";
private:
    enum class Locale {
        Disable,
        Touch,
        Enable
    };
    Locale m_Locale = Locale::Disable;
    
    SDL_Renderer* m_Renderer = nullptr;
    Font value;
};

#endif
