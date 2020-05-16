#ifndef Core_hpp
#define Core_hpp

// static status
#include "../Status/Status.hpp"

// controller module
#include "../Controller/StartButton/StartButton.hpp"
#include "../Controller/StopButton/StopButton.hpp"
#include "../Controller/PauseButton/PauseButton.hpp"
#include "../Controller/NextButton/NextButton.hpp"

// alphabet module
#include "../Alphabet/InputBar/InputBar.hpp"

// tape module
#include "../Tape/CellTape/CellTape.hpp"
#include "../Tape/RightButton/RightButton.hpp"
#include "../Tape/LeftButton/LeftButton.hpp"

// algorithm module
#include "../Algorithm/TableController/TableController.hpp"

class Core {
public:
    Core(SDL_Renderer* l_Renderer);
    ~Core(void);
    
    // algorithm controller
    void doAlgorithm(double l_Time);
    
    // Change algorithm status
    void startAlgorithm(void);
    void stopAlgorithm(void);
    void pauseAlgorithm(void);
    void nextStep(void);
    
    // Events
    void touch(int x, int y);
    void upTouch(int x, int y);
    void downTouch(int x, int y);
    void handleEvent(SDL_Event *l_Event);
    
    // draw
    void drawCore(void);
private:
    // for doAlgorithm() function
    void doProcess(double l_Time);
    void doNext(void);
    
    // for downTouch() function
    void disable(void);
    void clear(void);
    void deepClear(void);
private:
    SDL_Renderer* m_Renderer = nullptr;
    // control module
    NextButton m_NextButton;
    PauseButton m_PauseButton;
    StartButton m_StartButton;
    StopButton m_StopButton;
        
    // alphabet module
    InputBar m_InputBar;
    
    // tape module
    RightButton m_RightButton;
    LeftButton m_LeftButton;
    CellTape m_CellTape;
    
    // algorithm module
    TableController m_TableController;
    
    // Algorithm data
    int m_Index = (Status::amountOfCells - 1)/2;  // index of center cell of tape
    int m_Step = 1;                               // step of the algorithm
    double m_Time = 0;                            // time to start function
    char m_ForIndex = '\0';                       // active cell's character
    std::string m_Info = "";                      // active command for cell
 
    bool flag = false;
    bool m_NextFirst = false;                     // Flag for change active cell
    bool m_NextSecond = false;                    // Flag for move active cell
};

#endif
