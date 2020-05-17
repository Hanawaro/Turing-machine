#include "TableController.hpp"

TableController::TableController(SDL_Renderer* l_Renderer) {
    m_Renderer = l_Renderer;
    for (int i = 0; i < Status::maximalOfSteps; i++) {
        for (int j = 0; j < Status::maximalOfLength; j++) {
            m_Algorithm[i][j].data = new TextEntity(m_Path, 22, {0, 0, 0}, "   ", l_Renderer);
            m_Algorithm[i][j].height = m_Algorithm[i][j].data->GetDstRect()->h - 4*2;
            m_Algorithm[i][j].width = (m_Algorithm[i][j].data->GetDstRect()->w * m_Algorithm[i][j].height) / m_Algorithm[i][j].data->GetDstRect()->h;
            
            m_Algorithm[i][j].data->SetSize(m_Algorithm[i][j].width, m_Algorithm[i][j].height);
        }
    }
    
    for (int i = 0; i < Status::maximalOfLength; i++) {
        std::string data = "";
        if (i < Status::alphabet.size() && Status::alphabet[i] == ' ') {
            data += '_';
        } else if (i < Status::alphabet.size()) {
            data += Status::alphabet[i];
        }
        if (i < Status::alphabet.size()) {
            m_Vertical[i].data = new TextEntity(m_Path, 22, {0, 0, 0}, data, l_Renderer);
            m_Vertical[i].height = m_Vertical[i].data->GetDstRect()->h - 4*2;
            m_Vertical[i].width = (m_Vertical[i].data->GetDstRect()->w * m_Vertical[i].height) / m_Vertical[i].data->GetDstRect()->h;
            
            m_Vertical[i].data->SetSize(m_Vertical[i].width, m_Vertical[i].height);
        } else {
            m_Vertical[i].data = new TextEntity(m_Path, 22, {0, 0, 0}, " ", l_Renderer);
            m_Vertical[i].height = m_Vertical[i].data->GetDstRect()->h - 4*2;
            m_Vertical[i].width = (m_Vertical[i].data->GetDstRect()->w * m_Vertical[i].height) / m_Vertical[i].data->GetDstRect()->h;
            
            m_Vertical[i].data->SetSize(m_Vertical[i].width, m_Vertical[i].height);
        }
    }
    
    for (int i = 0; i < Status::maximalOfSteps; i++) {
        m_Horizontal[i].data = new TextEntity(m_Path, 22, {0, 0, 0}, std::string("Q(") + std::to_string(i+1) + ")", l_Renderer);
        m_Horizontal[i].height = m_Horizontal[i].data->GetDstRect()->h - 4*2;
        m_Horizontal[i].width = (m_Horizontal[i].data->GetDstRect()->w * m_Horizontal[i].height) / m_Horizontal[i].data->GetDstRect()->h;
            
        m_Horizontal[i].data->SetSize(m_Horizontal[i].width, m_Horizontal[i].height);
    }
    
}

TableController::~TableController(void) {
    for (int i = 0; i < Status::maximalOfSteps; i++) {
        for (int j = 0; j < Status::maximalOfLength; j++) {
            delete m_Algorithm[i][j].data;
        }
    }
    
    for (int i = 0; i < Status::maximalOfSteps; i++) {
        delete m_Horizontal[i].data;
    }
    
    for (int i = 0; i < Status::maximalOfLength; i++) {
        delete m_Vertical[i].data;
    }
}

void TableController::draw(void) {
    boxRGBA(m_Renderer,
                  x * Status::resizeHorizontal,
                  y * Status::resizeVertical,
                  (x + (Status::algorithm.size() + 1) * width) * Status::resizeHorizontal,
                  (y + (Status::alphabet.size() + 1) * height) * Status::resizeVertical,
                  0xff, 0xff, 0xff, 0xc8
                  );
    rectangleRGBA(m_Renderer,
                  x * Status::resizeHorizontal,
                  y * Status::resizeVertical,
                  (x + (Status::algorithm.size() + 1) * width) * Status::resizeHorizontal + 1,
                  (y + (Status::alphabet.size() + 1) * height) * Status::resizeVertical + 1,
                  0x00, 0x00, 0x00, 0xff
                  );
    for (int i = 0; i <= Status::alphabet.size(); i++) {
        lineRGBA(m_Renderer,
                 x * Status::resizeHorizontal,
                 (y + i*height)*Status::resizeVertical,
                 (x + (Status::algorithm.size() + 1) * width) * Status::resizeHorizontal,
                 (y + i*height)*Status::resizeVertical,
                 0x00, 0x00, 0x00, 0xff
                 );
    }
    for (int i = 0; i <= Status::algorithm.size(); i++) {
        lineRGBA(m_Renderer,
                 (x + i*width) * Status::resizeHorizontal,
                 y*Status::resizeVertical,
                 (x + i*width) * Status::resizeHorizontal,
                 (y + (Status::alphabet.size() + 1) * height) * Status::resizeVertical,
                 0x00, 0x00, 0x00, 0xff
                 );
    }
    if (m_LocaleMain == Locale::Touch || m_LocaleSecondary == Locale::Touch)
        rectangleRGBA(m_Renderer,
                      m_ActiveCell.x1*Status::resizeHorizontal + 2,
                      m_ActiveCell.y1*Status::resizeVertical + 2,
                      m_ActiveCell.x2*Status::resizeHorizontal - 1,
                      m_ActiveCell.y2*Status::resizeVertical - 1,
                      0x00, 0x00, 0x00, 0xff
                      );
    if (m_LocaleMain == Locale::Enable)
        rectangleRGBA(m_Renderer,
                      m_DrawCell.x1*Status::resizeHorizontal + 1,
                      m_DrawCell.y1*Status::resizeVertical + 1,
                      m_DrawCell.x2*Status::resizeHorizontal,
                      m_DrawCell.y2*Status::resizeVertical,
                      0x00, 0x00, 0x00, 0xff
                      );
    
    for (int i = 0; i < Status::algorithm.size(); i++) {
        for (int j = 0; j < Status::alphabet.size(); j++) {
            m_Algorithm[i][j].data->SetSize(m_Algorithm[i][j].width*Status::resizeHorizontal, m_Algorithm[i][j].height*Status::resizeVertical);
            m_Algorithm[i][j].data->SetPosition((x + (i+1)*width + (width - m_Algorithm[i][j].width)/2)*Status::resizeHorizontal + 2, (y + (j+1)*height)*Status::resizeVertical + 2);
            m_Algorithm[i][j].data->draw(m_Renderer);
        }
    }
    for (int i = 0; i < Status::alphabet.size(); i++) {
        m_Vertical[i].data->SetSize(m_Vertical[i].width*Status::resizeHorizontal, m_Vertical[i].height*Status::resizeVertical);
        m_Vertical[i].data->SetPosition((x + (width - m_Vertical[i].width)/2)*Status::resizeHorizontal + 2, (y + (i+1)*height)*Status::resizeVertical + 2);
        m_Vertical[i].data->draw(m_Renderer);
    }
    for (int i = 0; i < Status::algorithm.size(); i++) {
        m_Horizontal[i].data->SetSize(m_Horizontal[i].width*Status::resizeHorizontal, m_Horizontal[i].height*Status::resizeVertical);
        m_Horizontal[i].data->SetPosition((x + (i+1)*width + (width - m_Horizontal[i].width)/2)*Status::resizeHorizontal + 2, y*Status::resizeVertical + 2);
        m_Horizontal[i].data->draw(m_Renderer);
    }
}

void TableController::touch(int l_X, int l_Y) {
    if (Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process) {
        for (int i = 0; i < Status::algorithm.size(); i++) {
            for (int j = 0; j < Status::alphabet.size(); j++) {
                if (l_X >= x + (i + 1)*width && l_X <= x + (i + 2)*width &&
                    l_Y >= y + (j + 1)*height && l_Y <= y + (j + 2)*height) {
                    if (m_LocaleMain == Locale::Enable && (m_DrawCell.activeI != i || m_DrawCell.activeJ != j)) {
                        m_ActiveCell.x1 = x + (i + 1)*width;
                        m_ActiveCell.y1 = y + (j + 1)*height;
                        m_ActiveCell.x2 = x + (i + 2)*width;
                        m_ActiveCell.y2 = y + (j + 2)*height;
                        m_ActiveCell.activeI = i;
                        m_ActiveCell.activeJ = j;
                        m_LocaleSecondary = Locale::Touch;
                    } else if (m_LocaleMain == Locale::Enable && m_DrawCell.activeI == i && m_DrawCell.activeJ == j) {
                        m_ActiveCell.x1 = m_DrawCell.x1 = x + (i + 1)*width;
                        m_ActiveCell.y1 = m_DrawCell.y1 = y + (j + 1)*height;
                        m_ActiveCell.x2 = m_DrawCell.x2 = x + (i + 2)*width;
                        m_ActiveCell.y2 = m_DrawCell.y2 = y + (j + 2)*height;
                        m_ActiveCell.activeI = m_DrawCell.activeI = i;
                        m_ActiveCell.activeJ = m_DrawCell.activeJ = j;
                    } else {
                        m_ActiveCell.x1 = m_DrawCell.x1 = x + (i + 1)*width;
                        m_ActiveCell.y1 = m_DrawCell.y1 = y + (j + 1)*height;
                        m_ActiveCell.x2 = m_DrawCell.x2 = x + (i + 2)*width;
                        m_ActiveCell.y2 = m_DrawCell.y2 = y + (j + 2)*height;
                        m_ActiveCell.activeI = m_DrawCell.activeI = i;
                        m_ActiveCell.activeJ = m_DrawCell.activeJ = j;
                        m_LocaleMain = m_LocaleSecondary = Locale::Touch;
                    }
                    return;
                }
            }
        }
    } else {
        clear();
    }
}

void TableController::clear(void) {
    if (m_LocaleMain != Locale::Enable) {
        m_LocaleMain = m_LocaleSecondary = Locale::Disable;
        m_DrawCell.x1 = m_DrawCell.y1 = m_DrawCell.x2 = m_DrawCell.y2 = 0;
        m_DrawCell.activeI = m_DrawCell.activeJ = -1;
    }
    if (m_LocaleSecondary == Locale::Touch) {
        m_LocaleSecondary = Locale::Disable;
        m_ActiveCell.x1 = m_ActiveCell.y1 = m_ActiveCell.x2 = m_ActiveCell.y2 = 0;
        m_ActiveCell.activeI = m_ActiveCell.activeJ = -1;
    }
}

void TableController::set(void) {
    if (Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process) {
        disable();
        Status::status = Status::DeepStatus::Cells;
        m_LocaleMain = m_LocaleSecondary = Locale::Enable;
        m_DrawCell.activeI = m_ActiveCell.activeI;
        m_DrawCell.activeJ = m_ActiveCell.activeJ;
        m_DrawCell.x1 = m_ActiveCell.x1;
        m_DrawCell.y1 = m_ActiveCell.y1;
        m_DrawCell.x2 = m_ActiveCell.x2;
        m_DrawCell.y2 = m_ActiveCell.y2;
        SDL_StartTextInput();
        Logger::LogMessage("Enable TABLE CELL ["s + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) + "] when possible. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
    } else {
        Logger::LogMessage("Try to enable TABLE CELL ["s + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) + "] when impossible. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
    }
}

void TableController::disable(void) {
    for (int i = 0; i < Status::algorithm.size(); i++) {
        for (int j = 0; j < Status::algorithm[i].size(); j++) {
            if (Status::algorithm[i][j].size() != 3) {
                Status::algorithm[i][j].clear();
                m_Algorithm[i][j].data->SetContent("   ", m_Renderer);
            }
        }
    }
    if (Status::status == Status::DeepStatus::Cells) {
        Logger::LogMessage("Disable TABLE CELL ["s + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) + "]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
    }
    
    if (Status::status != Status::DeepStatus::Empty) {
        checkOld();
        
        Status::status = Status::DeepStatus::Empty;
        SDL_StopTextInput();
        
        // clear
        m_LocaleMain = m_LocaleSecondary = Locale::Disable;
        m_DrawCell.x1 = m_DrawCell.y1 = m_DrawCell.x2 = m_DrawCell.y2 =
        m_ActiveCell.x1 = m_ActiveCell.y1 = m_ActiveCell.x2 = m_ActiveCell.y2 = 0;
        m_DrawCell.activeI = m_DrawCell.activeJ = m_ActiveCell.activeI = m_ActiveCell.activeJ = -1;
    }
}

void TableController::update(void) {
    for (int i = 1; i < Status::alphabet.size(); i++) {
        std::string data = "";
        data += Status::alphabet[i];
        if (data != m_Vertical[i].data->GetContent()) {
            m_Vertical[i].data->SetContent(data, m_Renderer);
        }
    }
    for (int i = 0; i < Status::algorithm.size(); i++)
        for (int j = 0; j < Status::alphabet.size(); j++)
            if (Status::alphabet.find(Status::algorithm[i][j][0]) == -1) {
                Status::algorithm[i][j].clear();
                m_Algorithm[i][j].data->SetContent("   ", m_Renderer);
            }
    checkOld();
}

void TableController::checkNew(void) {
    if (Status::algorithm.size() + 1 >= Status::maximalOfSteps)
        return;
    bool haveNew = true;
    for (int i = 0; i < Status::algorithm[m_DrawCell.activeI].size(); i++) {
        if (Status::algorithm[m_DrawCell.activeI][i].size() == 3) {
            haveNew = false;
            break;
        }
    }
    if (haveNew) {
        int size = (int) Status::algorithm.size();
        if (m_DrawCell.activeI + 1 - size >= 0) {
            std::vector<std::string> tmp(Status::alphabet.size(), "");
            Status::algorithm.push_back(tmp);
        }
    }
}

void TableController::checkOld(void) {
    bool haveLast = false;
    bool haveBeforeLast = true;
    
    int size = (int) Status::algorithm.size() - 1;
    
    for (int i = 0; i < Status::algorithm[size].size(); i++) {
        if (Status::algorithm[size][i].size() == 3) {
            haveLast = true;
            break;
        }
    }
    for (int i = 0; i < Status::algorithm[size - 1].size() && size - 1 > 0; i++) {
        haveBeforeLast = false;
        if (Status::algorithm[size - 1][i].size() == 3) {
            haveBeforeLast = true;
            break;
        }
    }
    if (!haveLast && !haveBeforeLast) {
        if (size > 1) {
            Status::algorithm.erase(Status::algorithm.begin() + size);
            if (size == m_DrawCell.activeI) {
                disable();
            }
            checkOld();
        }
    }
}

void TableController::handle(SDL_Event *l_Event) {
    if (l_Event->type == SDL_KEYDOWN) {
        if (l_Event->key.keysym.sym == SDLK_BACKSPACE) {
            if (Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size() > 0) {
                Logger::LogMessage("Delete  \""s + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ][Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size() - 1] + "\" from TABLE CELL [" + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) + "] when possible. Cell was \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                
                    Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] = Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].substr(0, Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size() - 1);
                std::string add = "";
                for (int i = 3; i > Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size(); i--)
                    add += " ";
                if (Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ][0] == ' ') {
                    m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(std::string("_") + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].substr(1, Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size() - 1) + add, m_Renderer);
                } else {
                    m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + add, m_Renderer);
                }
                if(Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size() == 0)
                    checkOld();
            } else {
                Logger::LogMessage("Try to delete from TABLE CELL ["s + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) + "] when impossible. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
            }
        }
    } else if (l_Event->type == SDL_TEXTINPUT) {
        bool fake = false;
        switch (Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].size()) {
            case 0:
                fake = false;
                for (int j = 0; j < Status::alphabet.size(); j++) {
                    if (Status::alphabet[j] == l_Event->text.text[0])
                        fake = true;
                }
                if (fake) {
                    Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] += l_Event->text.text[0];
                    checkNew();
                    if (l_Event->text.text[0] == ' ') {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent("_  ", m_Renderer);
                    } else {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "  ", m_Renderer);
                    }
                    
                    Logger::LogMessage("Add alphabet symbol \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                } else {
                    Logger::LogMessage("Try to add NOT alphabet symbol \""s + l_Event->text.text[0] + "\" to TABLE CELL [" + std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                }
                break;
            case 1:
                if (l_Event->text.text[0] == '>' || l_Event->text.text[0] == '<' || l_Event->text.text[0] == '|') {
                    Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] += l_Event->text.text[0];
                    if (Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ][0] == ' ') {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(std::string("_") + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ][1] + " ", m_Renderer);
                    } else {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + " ", m_Renderer);
                    }
                    Logger::LogMessage("Add carriage command \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                } else {
                    Logger::LogMessage("Try to add NOT carriage command \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                }
                break;
            case 2:
                if (l_Event->text.text[0] >= '0' && l_Event->text.text[0] <= '0' + Status::algorithm.size()) {
                    Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] += l_Event->text.text[0];
                    if (Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ][0] == ' ') {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(std::string("_") + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].substr(1, 2), m_Renderer);
                    } else {
                        m_Algorithm[m_DrawCell.activeI][m_DrawCell.activeJ].data->SetContent(Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ], m_Renderer);
                    }
                    Logger::LogMessage("Add condition \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                } else {
                    Logger::LogMessage("Try add NOT condition \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                }
                break;
            default:
                Logger::LogMessage("Try add more symbol \""s + l_Event->text.text[0] + "\" to TABLE CELL ["+ std::to_string(m_DrawCell.activeI) + "][" + std::to_string(m_DrawCell.activeJ) +"]. Cell is \"" + Status::algorithm[m_DrawCell.activeI][m_DrawCell.activeJ] + "\"");
                break;
        }
    }
    if (l_Event->type == SDL_KEYDOWN) {
        if (l_Event->key.keysym.sym == SDLK_RETURN) {
            disable();
        }
    }
}

