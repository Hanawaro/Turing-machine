#ifndef CellTape_hpp
#define CellTape_hpp

#include "../../Status/Status.hpp"

class CellTape {
public:
    CellTape(SDL_Renderer* l_Renderer);
    ~CellTape(void);
    
    void draw(void);
    void OpenCell(int x, int y);
    void drawSideBar(void);
    void ActiveSideBar(int x, int y);
    void DoSideBar(int x, int y);
    void clear(void);
    void disable(void);
    
    void updateTape(void);
    void updateBar(void);
public:
    const int width = 40;
    const int height = 40;
    
    const int left = 100;
    const int right = left + width;
    
    const int top = 150;
    const int bottom = top + height;
    
    const std::string m_Path = "Source/Font/Menlo.ttf";
protected:
    Font m_Tape[Status::amountOfCells];
    Font m_Alphabet[Status::maximalOfLength];
private:
    enum class Locale {
        Disable,
        Active,
        Enable
    };
    Locale locale = Locale::Disable;
    int index = 0;
    int indexTape = 0;
    
    SDL_Renderer* m_Renderer;
};

#endif
