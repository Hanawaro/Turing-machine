#include "CellTape.hpp"

CellTape::CellTape(SDL_Renderer* l_Renderer) {
    m_Renderer = l_Renderer;
    
    for (int i = 0; i < Status::amountOfCells; i++) {
        std::string data = "";
        data += Status::tape[i + Status::bias];
        m_Tape[i].data = new TextEntity(m_Path, 35, {0, 0, 0}, data, l_Renderer);
        m_Tape[i].height = m_Tape[i].data->GetDstRect()->h - 4*2;
        m_Tape[i].width = (m_Tape[i].data->GetDstRect()->w * m_Tape[i].height) / m_Tape[i].data->GetDstRect()->h;
        m_Tape[i].data->SetSize(m_Tape[i].width, m_Tape[i].height);
    }
    for (int i = 0; i < Status::maximalOfLength; i++) {
        std::string data = "";
        if (i < Status::alphabet.size()) {
            data += Status::alphabet[i];
        } else {
            data += " ";
        }
        m_Alphabet[i].data = new TextEntity(m_Path, 24, {0, 0, 0}, data, l_Renderer);
        m_Alphabet[i].height = m_Alphabet[i].data->GetDstRect()->h - 4*2;
        m_Alphabet[i].width = (m_Alphabet[i].data->GetDstRect()->w * m_Alphabet[i].height) / m_Alphabet[i].data->GetDstRect()->h;
        m_Alphabet[i].data->SetSize(m_Alphabet[i].width, m_Alphabet[i].height);
    }
}

CellTape::~CellTape(void) {
    for (int i = 0; i < Status::amountOfCells; i++) {
        delete m_Tape[i].data;
    }
    for (int i = 0; i < Status::maximalOfLength; i++) {
        delete m_Alphabet[i].data;
    }

}

void CellTape::draw(void) {
    for (int i = 0; i < Status::amountOfCells; i++) {
        if (i == (Status::amountOfCells-1)/2) {
            filledTrigonRGBA(m_Renderer,
                             (left + 40*i)*Status::resizeHorizontal ,
                             (top - 20)*Status::resizeVertical,
                             (right + 40*i)*Status::resizeHorizontal,
                             (top - 20)*Status::resizeVertical,
                             (left + right + 80*i)/2*Status::resizeHorizontal,
                             (top - 1)*Status::resizeVertical,
                             0, 0, 0, 255
                             );
        }
        boxRGBA(m_Renderer,
                      (left + 40*i)*Status::resizeHorizontal,
                      top*Status::resizeVertical,
                      (right + 40*i)*Status::resizeHorizontal,
                      bottom*Status::resizeVertical - 1,
                      255, 255, 255, 100
                      );
        rectangleRGBA(m_Renderer,
                      (left + 40*i)*Status::resizeHorizontal,
                      top*Status::resizeVertical,
                      (right + 40*i)*Status::resizeHorizontal + 1,
                      bottom*Status::resizeVertical,
                      0, 0, 0, 255
                      );
        m_Tape[i].data->SetSize(m_Tape[i].width*Status::resizeHorizontal, m_Tape[i].height*Status::resizeVertical);
        m_Tape[i].data->SetPosition((left + 40*i + (width - m_Tape[i].width)/2)*Status::resizeHorizontal, (top+4)*Status::resizeVertical);
        m_Tape[i].data->draw(m_Renderer);
    }
}

void CellTape::updateTape(void) {
    for (int i = 0; i < Status::amountOfCells; i++) {
        std::string data = "";
        data += Status::tape[i + Status::bias];
        if (data != m_Tape[i].data->GetContent()) {
            m_Tape[i].data->SetContent(data, m_Renderer);
        }
    }
}

void CellTape::updateBar(void) {
    for (int i = 0; i < Status::alphabet.size(); i++) {
        std::string data = "";
        data += Status::alphabet[i];
        if (data != m_Alphabet[i].data->GetContent()) {
            m_Alphabet[i].data->SetContent(data, m_Renderer);
        }
    }
}

void CellTape::OpenCell(int x, int y) {
    for (int i = 0; i < Status::amountOfCells; i++) {
        
        if (x > left + 40*i && x < right + 40*i) {
            Status::sideBar.x1 = x;
            Status::sideBar.y1 = y;
            Status::sideBar.y2 = Status::sideBar.y1 + (int) Status::alphabet.size() * 20;
            Status::sideBar.x2 = Status::sideBar.x1 + 50;
            locale = Locale::Enable;
            indexTape = i;
            
            if (Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process)
                Logger::LogMessage(std::string("Press CELL BAR when possible"));
            else
                Logger::LogMessage(std::string("Press CELL BAR when impossible"));
            break;
        }
    }
}

void CellTape::drawSideBar(void) {
    int y1 = Status::sideBar.y1,
        y2 = Status::sideBar.y1 + 19;
    
    if (Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process) {
        switch (locale) {
            case Locale::Enable:
                boxRGBA(m_Renderer,
                        Status::sideBar.x1*Status::resizeHorizontal,
                        Status::sideBar.y1*Status::resizeVertical,
                        Status::sideBar.x2*Status::resizeHorizontal - 1,
                        Status::sideBar.y2*Status::resizeVertical - 1,
                        255, 255, 255, 240
                        );
                rectangleRGBA(m_Renderer,
                        Status::sideBar.x1*Status::resizeHorizontal,
                        Status::sideBar.y1*Status::resizeVertical,
                        Status::sideBar.x2*Status::resizeHorizontal,
                        Status::sideBar.y2*Status::resizeVertical,
                        0, 0, 0, 255
                );
                for (int i = 0; i < Status::alphabet.size(); i++) {
                    m_Alphabet[i].data->SetSize(m_Alphabet[i].width*Status::resizeHorizontal, m_Alphabet[i].height*Status::resizeVertical);
                    m_Alphabet[i].data->SetPosition((Status::sideBar.x1 + (width - m_Alphabet[i].width)/1.7)*Status::resizeHorizontal + 2, y1*Status::resizeVertical);
                    m_Alphabet[i].data->draw(m_Renderer);
                    y1 += 20;
                }
                break;
            case Locale::Active:
                boxRGBA(m_Renderer,
                        Status::sideBar.x1*Status::resizeHorizontal,
                        Status::sideBar.y1*Status::resizeVertical,
                        Status::sideBar.x2*Status::resizeHorizontal - 1,
                        Status::sideBar.y2*Status::resizeVertical - 1,
                        255, 255, 255, 240
                );
                for (int i = 0; i < index; i++) {
                    y1 += 20;
                    y2 += 20;
                }
                boxRGBA(m_Renderer,
                        Status::sideBar.x1*Status::resizeHorizontal + 1,
                        y1*Status::resizeVertical,
                        Status::sideBar.x2*Status::resizeHorizontal - 1,
                        y2*Status::resizeVertical,
                        200, 200, 200, 240
                );
                rectangleRGBA(m_Renderer,
                        Status::sideBar.x1*Status::resizeHorizontal,
                        Status::sideBar.y1*Status::resizeVertical,
                        Status::sideBar.x2*Status::resizeHorizontal,
                        Status::sideBar.y2*Status::resizeVertical,
                        0, 0, 0, 255
                );
                y1 = Status::sideBar.y1;
                for (int i = 0; i < Status::alphabet.size(); i++) {
                    m_Alphabet[i].data->SetSize(m_Alphabet[i].width*Status::resizeHorizontal, m_Alphabet[i].height*Status::resizeVertical);
                    m_Alphabet[i].data->SetPosition((Status::sideBar.x1 + (width - m_Alphabet[i].width)/1.7)*Status::resizeHorizontal + 2, y1*Status::resizeVertical);
                    m_Alphabet[i].data->draw(m_Renderer);
                    y1 += 20;
                }
                break;
            case Locale::Disable:
                break;
        }
    } else {
        locale = Locale::Disable;
        Status::sideBar = { 0, 0, 0, 0, 0 };
    }
}

void CellTape::ActiveSideBar(int x, int y) {
    if (locale != Locale::Disable && Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process) {
        for (int i = 0; i < Status::alphabet.size(); i++) {
            if (y >= Status::sideBar.y1 + 20*i && y <= Status::sideBar.y1 + 20*(i+1) ) {
                index = i;
                break;
            }
        }
        locale = Locale::Active;
    } else {
        locale = Locale::Disable;
        Status::sideBar = { 0, 0, 0, 0, 0 };
    }
}

void CellTape::DoSideBar(int x, int y) {
    Status::tape[Status::bias + indexTape] = Status::alphabet[index];
    std::string data = "";
    data += Status::alphabet[index];
    m_Tape[indexTape].data->SetContent(data, m_Renderer);
    
    Status::status = Status::DeepStatus::Empty;
    Logger::LogMessage(std::string("Put on tape's cell[") + std::to_string(indexTape) + "] \"" + data + "\" ");
    disable();
}

void CellTape::clear(void) {
    if (locale != Locale::Disable && Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process)
        locale = Locale::Enable;
}

void CellTape::disable(void) {
    if (locale != Locale::Disable)
        Logger::LogMessage(std::string("Disable CELL BAR"));
    locale = Locale::Disable;
    Status::sideBar = { 0, 0, 0, 0, 0 };
        
}

