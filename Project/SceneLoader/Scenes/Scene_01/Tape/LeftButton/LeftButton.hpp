#ifndef LeftButton_hpp
#define LeftButton_hpp

#include "../../Status/Status.hpp"

class LeftButton {
public:
    LeftButton(void);
    ~LeftButton(void);
    
    void draw(SDL_Renderer* l_Renderer);
    void touch(void);
    void active(void);
    void set(void);
    void disable(void);
    
    void clear(void);
    void deepClear(void);
public:
    const int left = 100;
    const int top = 140;
    const int bottom = 200;
    const int center = 170;
private:
    enum class Locale {
        Up,
        Down,
        Touch
    };
    Locale m_Locale = Locale::Up;
    
    Button m_Texture;
};

#endif
