#ifndef TableController_hpp
#define TableController_hpp

#include "../../Status/Status.hpp"

struct Cell {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int activeI = -1;
    int activeJ = -1;
};

class TableController {
public:
    TableController(SDL_Renderer* l_Renderer);
    ~TableController(void);
    
    void draw(void);
    void touch(int l_X, int l_Y);
    void set(void);
    void disable(void);
    void clear(void);
    void handle(SDL_Event *l_Event);
    
    void update(void);
public:
    const int width = 70;
    const int height = 22;
    
    const int x = 50;
    const int y = 250;
    
    const std::string m_Path = "Source/Font/Menlo.ttf";
private:
    void checkNew(void);
    void checkOld(void);
private:
    enum class Locale {
        Disable,
        Touch,
        Enable
    };
    Locale m_LocaleMain      = Locale::Disable;
    Locale m_LocaleSecondary = Locale::Disable;
    
    Cell m_DrawCell;
    Cell m_ActiveCell;
    
    SDL_Renderer* m_Renderer;
    
    Font m_Algorithm[Status::maximalOfSteps][Status::maximalOfLength];
    Font m_Horizontal[Status::maximalOfSteps];
    Font m_Vertical[Status::maximalOfLength];
};

#endif
