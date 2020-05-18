#include "Core.hpp"

Core::Core(SDL_Renderer* l_Renderer) :
    m_InputBar(l_Renderer), m_CellTape(l_Renderer), m_TableController(l_Renderer),
    m_StartButton(l_Renderer), m_StopButton(l_Renderer), m_PauseButton(l_Renderer), m_NextButton(l_Renderer)
{
    m_Renderer = l_Renderer;
}

Core::~Core(void) {}

void Core::disable(void) {
    if (Status::status == Status::DeepStatus::InputBar)
        m_InputBar.disable();
    if (Status::status == Status::DeepStatus::Cells)
        m_TableController.disable();
}

void Core::clear(void) {
    m_CellTape.clear();
    m_StartButton.clear();
    m_StopButton.clear();
    m_PauseButton.clear();
    m_NextButton.clear();
    m_InputBar.clear();
    m_LeftButton.clear();
    m_RightButton.clear();
    m_TableController.clear();
}

void Core::deepClear(void) {
    m_StartButton.deepClear();
    m_StopButton.deepClear();
    m_PauseButton.deepClear();
    m_NextButton.deepClear();
    m_LeftButton.deepClear();
    m_RightButton.deepClear();
}

void Core::touch(int x, int y) {
    clear();
    
    // the side bar of the tape module
    if (x > Status::sideBar.x1 && x < Status::sideBar.x2 && y > Status::sideBar.y1 && y < Status::sideBar.y2) {
        m_CellTape.ActiveSideBar(x, y);
        return;
    }
    
    // THE CONTROLLER MODULE
    // start button
    if (x >= m_StartButton.x1  && x <= m_StartButton.x2 && y >= m_StartButton.y1 && y <= m_StartButton.y2) {
        m_StartButton.touch();
        return;
    }
    
    // stop button
    if (x >= m_StopButton.x1  && x <= m_StopButton.x2 && y >= m_StopButton.y1 && y <= m_StopButton.y2) {
        m_StopButton.touch();
        return;
    }
    
    // pause button
    if (x >= m_PauseButton.x1  && x <= m_PauseButton.x2 && y >= m_PauseButton.y1 && y <= m_PauseButton.y2) {
        m_PauseButton.touch();
        return;
    }
    
    // next button
    if (x >= m_NextButton.x1  && x <= m_NextButton.x2 && y >= m_NextButton.y1 && y <= m_NextButton.y2) {
        m_NextButton.touch();
        return;
    }
    
    // THE ALPHABET MODULE
    // input bar
    if (x >= m_InputBar.x1 && x <= m_InputBar.x2 && y >= m_InputBar.y1 && y <= m_InputBar.y2) {
        m_InputBar.touch();
    }
    
    // THE TAPE MODULE
    // left button
    if (-1.2*x + 254 <= y && 1.2*x + 86 >= y && x <= 95) {
        m_LeftButton.touch();
        return;
    }
    // right button
    if (-1.25*x + 1082.5 >= y && 1.25*x - 742.5 <= y && x >= 706) {
        m_RightButton.touch();
        return;
    }
    // THE ALGORITHM MODULE
    // the algorithm's table
    if (x >= m_TableController.x + m_TableController.width &&
        x <= (m_TableController.x + (Status::algorithm.size() + 1) * m_TableController.width) &&
        y >= m_TableController.y + m_TableController.height &&
        y <= (m_TableController.y + (Status::alphabet.size() + 1) * m_TableController.height)) {
        
        m_TableController.touch(x, y);
    }
    
    deepClear();
}

void Core::upTouch(int x, int y) {
    // THE CONTROLLER MODULE
    // start button
    if (x >= m_StartButton.x1  && x <= m_StartButton.x2 && y >= m_StartButton.y1 && y <= m_StartButton.y2) {
        m_StartButton.active();
        return;
    }
    // stop button
    if (x >= m_StopButton.x1  && x <= m_StopButton.x2 && y >= m_StopButton.y1 && y <= m_StopButton.y2){
        m_StopButton.active();
        return;
    }
    // pause button
    if (x >= m_PauseButton.x1  && x <= m_PauseButton.x2 && y >= m_PauseButton.y1 && y <= m_PauseButton.y2) {
        m_PauseButton.active();
        return;
    }
    // next button
    if (x >= m_NextButton.x1  && x <= m_NextButton.x2 && y >= m_NextButton.y1 && y <= m_NextButton.y2) {
        m_NextButton.active();
        return;
    }
    
    // THE TAPE MODULE
    // left button
    if (-1.2*x + 254 <= y && 1.2*x + 86 >= y && x <= 95) {
        m_LeftButton.active();
        return;
    }
    // right button
    if (-1.25*x + 1082.5 >= y && 1.25*x - 742.5 <= y && x >= 706) {
        m_RightButton.active();
        return;
    }
}

void Core::downTouch(int x, int y) {
    // THE TAPE MODULE
    // the side bar for the tape
    if (x >= Status::sideBar.x1 && x <= Status::sideBar.x2 && y >= Status::sideBar.y1 && y <= Status::sideBar.y2) {
        disable();
        m_CellTape.DoSideBar(x, y);
        return;
    }
    m_CellTape.disable();
    
    // left button
    if (-1.2*x + 254 <= y && 1.2*x + 86 >= y && x <= 95) {
        disable();
        m_LeftButton.set();
        m_CellTape.updateTape();
        return;
    }
    
    // right button
    if (-1.25*x + 1082.5 >= y && 1.25*x - 742.5 <= y && x >= 706) {
        disable();
        m_RightButton.set();
        m_CellTape.updateTape();
        return;
    }
    
    // cell
    if (y >= m_CellTape.top && y <= m_CellTape.bottom && x >= m_CellTape.left && x <= 706) {
        disable();
        m_CellTape.OpenCell(x, y);
        return;
    }
    
    // THE CONTROLLER MODULE
    // start button
    if (x >= m_StartButton.x1  && x <= m_StartButton.x2 && y >= m_StartButton.y1 && y <= m_StartButton.y2) {
        disable();
        startAlgorithm();
        m_StartButton.set();
        return;
    }
    
    // stop button
    if (x >= m_StopButton.x1  && x <= m_StopButton.x2 && y >= m_StopButton.y1 && y <= m_StopButton.y2) {
        disable();
        stopAlgorithm();
        m_StopButton.set();
        return;
    }
    
    // pause button
    if (x >= m_PauseButton.x1  && x <= m_PauseButton.x2 && y >= m_PauseButton.y1 && y <= m_PauseButton.y2) {
        disable();
        pauseAlgorithm();
        m_PauseButton.set();
        return;
    }
    
    // next button
    if (x >= m_NextButton.x1  && x <= m_NextButton.x2 && y >= m_NextButton.y1 && y <= m_NextButton.y2) {
        disable();
        nextStep();
        m_NextButton.set();
        return;
    }
    
    // THE ALPHABET MODULE
    // input bar
    if (x >= m_InputBar.x1 && x <= m_InputBar.x2 && y >= m_InputBar.y1 && y <= m_InputBar.y2) {
        if (Status::status != Status::DeepStatus::InputBar)
            disable();
        else
            m_TableController.disable();
        m_InputBar.set();
        return;
    }
    
    // THE CELLS MODULE
    if (x >= m_TableController.x + 70 && x <= (m_TableController.x + (Status::algorithm.size() + 1) * m_TableController.width) &&
        y >= m_TableController.y + 20 && y <= (m_TableController.y + (Status::alphabet.size() + 1) * m_TableController.height)) {
        
        disable();
        m_TableController.touch(x, y);
        m_TableController.set();
        return;
    }
    
    disable();
}

void Core::handleEvent(SDL_Event *l_Event) {
    if (Status::status == Status::DeepStatus::InputBar) {
        m_InputBar.handle(l_Event);
        m_CellTape.updateBar();
        m_CellTape.updateTape();
        m_TableController.update();
    }
    if (Status::status == Status::DeepStatus::Cells) {
        m_TableController.handle(l_Event);
    }
}

void Core::drawCore(void) {
    // draw the controller module
    
    m_StartButton.draw();
    m_StopButton.draw();
    m_PauseButton.draw();
    m_NextButton.draw();
    
    // draw the alphabet module
    m_InputBar.draw();

    // draw the tape module
    m_LeftButton.draw(m_Renderer);
    m_CellTape.draw();
    m_RightButton.draw(m_Renderer);

    // draw the cells module
    m_TableController.draw();

    // draw the side bar for the tape
    m_CellTape.drawSideBar();
}

void Core::doAlgorithm(double l_Time) {
    m_Index = (Status::amountOfCells - 1)/2 + Status::bias;
    switch (Status::status) {
        case Status::DeepStatus::Process:
            doProcess(l_Time);
            break;
        case Status::DeepStatus::Pause:
            break;
        case Status::DeepStatus::NextStep:
            doNext();
            break;
        default:
            break;
    }
}

void Core::startAlgorithm(void) {
    if (Status::status == Status::DeepStatus::Pause)
        return;
    m_Step = 1;
    m_Time = 0;
    flag = false;
    m_NextFirst = false;
    m_NextSecond = false;}

void Core::stopAlgorithm(void) {
    m_Step = 1;
    m_Time = 0;
    flag = false;
    m_NextFirst = false;
    m_NextSecond = false;
}

void Core::pauseAlgorithm(void) {}

void Core::nextStep(void) {
    if (Status::status != Status::DeepStatus::NextStep) {
        m_Step = 1;
    }
    m_NextFirst = true;
}

void Core::doProcess(double l_Time) {
    if (m_Time > 500) {
        if (m_Time > 1000) {
            // Carriage shift
            switch (m_Info[1]) {
                case '>':
                    Status::bias++;
                    if (Status::bias + 15 > Status::tape.size())
                        Status::tape.push_back(' ');
                    break;
                case '<':
                    if (!Status::bias)
                        Status::tape.insert(Status::tape.begin(), ' ');
                    Status::bias = Status::bias - 1 < 0 ? 0 : Status::bias - 1;
                    break;
                case '|':
                    break;
            }
            // transition
            if (m_Info[2] == '0') {
                m_Step = 1;
                Status::status = Status::DeepStatus::Empty;
                Logger::LogMessage("Legal end of a algorithm"s);
            } else {
                m_Step = m_Info[2] - '0';
            }
            m_Time = 0;
            // update the tape
            m_CellTape.updateTape();
            flag = false;
        } else {
            if (!flag) {
                // get all information
                m_ForIndex = Status::tape[m_Index];
                if (Status::alphabet.find(m_ForIndex) == -1) {
                    m_Step = 1;
                    Status::status = Status::DeepStatus::Empty;
                    Logger::LogMessage("Fatal end of a algorithm"s);
                    return;
                }
                m_Info = Status::algorithm[m_Step - 1][Status::alphabet.find(m_ForIndex)];
                if (m_Info.size() != 3) {
                    m_Step = 1;
                    Status::status = Status::DeepStatus::Empty;
                    Logger::LogMessage("Fatal end of a algorithm"s);
                    return;
                }
                // Cell valuse replacement
                Status::tape[m_Index] = m_Info[0];
                // update the tape
                m_CellTape.updateTape();
            }
            flag = true;
            // battery increase
            m_Time += l_Time;
        }
    } else {
        // battery increase
        m_Time += l_Time;
    }
}

void Core::doNext(void) {
    if (!m_NextFirst)
        return;
    // get all information
    m_ForIndex = Status::tape[m_Index];
    if (Status::alphabet.find(m_ForIndex) != -1) {
        if (!m_NextSecond)
            m_Info = Status::algorithm[m_Step - 1][Status::alphabet.find(m_ForIndex)];
        if (m_Info.size() != 3) {
            m_Step = 1;
            Status::status = Status::DeepStatus::End;
            Logger::LogMessage("Fatal end of a next step algorithm"s);
        } else {
            // Cell valuse replacement
            Status::tape[m_Index] = m_Info[0];
            if (m_NextSecond) {
                // Carriage shift
                switch (m_Info[1]) {
                    case '>':
                        Status::bias++;
                        if (Status::bias + 15 > Status::tape.size())
                            Status::tape.push_back(' ');
                        break;
                    case '<':
                        if (!Status::bias)
                            Status::tape.insert(Status::tape.begin(), ' ');
                        Status::bias = Status::bias - 1 < 0 ? 0 : Status::bias - 1;
                        break;
                    case '|':
                        break;
                }
                // transition
                if (m_Info[2] == '0') {
                    m_Step = 1;
                    Status::status = Status::DeepStatus::End;
                    Logger::LogMessage("Legal end of a next step algorithm"s);
                } else {
                    m_Step = m_Info[2] - '0';
                }
                m_NextFirst = false;
                m_NextSecond = false;
                // update the tape
                m_CellTape.updateTape();
                return;
            }
            m_NextFirst = false;
            m_NextSecond = true;
            // update the tape
            m_CellTape.updateTape();
        }
    }
}
