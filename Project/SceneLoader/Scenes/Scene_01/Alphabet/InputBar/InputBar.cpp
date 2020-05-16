#include "InputBar.hpp"


InputBar::InputBar(SDL_Renderer* l_Renderer) {
    m_Renderer = l_Renderer;
    value.data = new TextEntity(m_Path, 22, {0, 0, 0}, Status::alphabet, l_Renderer);
    value.height = value.data->GetDstRect()->h - 4*2;
    value.width = (value.data->GetDstRect()->w * value.height) / value.data->GetDstRect()->h;
    
    value.data->SetSize(value.width, value.height);
}

InputBar::~InputBar(void) {
    delete value.data;
}

void InputBar::draw(void) {
    boxRGBA(m_Renderer,
                  x1*Status::resizeHorizontal,
                  y1*Status::resizeVertical,
                  x2*Status::resizeHorizontal - 1,
                  y2*Status::resizeVertical - 1,
                  255, 255, 255, 200
    );
    switch (m_Locale) {
        case Locale::Disable:
            rectangleRGBA(m_Renderer,
                          x1*Status::resizeHorizontal,
                          y1*Status::resizeVertical,
                          x2*Status::resizeHorizontal,
                          y2*Status::resizeVertical,
                          0, 0, 0, 255
                          );
            break;
        case Locale::Touch:
            rectangleRGBA(m_Renderer,
                          x1*Status::resizeHorizontal,
                          y1*Status::resizeVertical,
                          x2*Status::resizeHorizontal,
                          y2*Status::resizeVertical,
                          0, 0, 0, 255
                          );
            rectangleRGBA(m_Renderer,
                          x1*Status::resizeHorizontal + 2,
                          y1*Status::resizeVertical + 2,
                          x2*Status::resizeHorizontal - 2,
                          y2*Status::resizeVertical - 2,
                          0, 0, 0, 255
                          );
            break;
        case Locale::Enable:
            rectangleRGBA(m_Renderer,
                          x1*Status::resizeHorizontal,
                          y1*Status::resizeVertical,
                          x2*Status::resizeHorizontal,
                          y2*Status::resizeVertical,
                          0, 0, 0, 255
                          );
            rectangleRGBA(m_Renderer,
                          x1*Status::resizeHorizontal + 1,
                          y1*Status::resizeVertical + 1,
                          x2*Status::resizeHorizontal - 1,
                          y2*Status::resizeVertical - 1,
                          0, 0, 0, 255
                          );
            break;
    }
    value.data->SetSize(Status::alphabet.size()*value.width*Status::resizeHorizontal, value.height*Status::resizeVertical);
    value.data->SetPosition((x1+4)*Status::resizeHorizontal, (y1+4)*Status::resizeVertical);
    value.data->draw(m_Renderer);
}

void InputBar::touch(void) {
    if (m_Locale != Locale::Enable && Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process)
        m_Locale = Locale::Touch;
}

void InputBar::set(void) {
    if (Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::Process) {
        Status::status = Status::DeepStatus::InputBar;
        m_Locale = Locale::Enable;
        SDL_StartTextInput();
        Logger::LogMessage(std::string("Enable INPUT BAR when possible"));
    } else {
        Logger::LogMessage(std::string("Try to enable INPUT BAR when impossible"));
    }
}

void InputBar::disable(void) {
    if (Status::status == Status::DeepStatus::InputBar)
        Logger::LogMessage(std::string("Disable INPUT BAR"));
    m_Locale = Locale::Disable;
    Status::status = Status::DeepStatus::Empty;
    SDL_StopTextInput();
}

void InputBar::clear(void) {
    if (m_Locale != Locale::Enable)
        m_Locale = Locale::Disable;
}

void InputBar::handle(SDL_Event *l_Event) {
    if (l_Event->type == SDL_KEYDOWN) {
        if (l_Event->key.keysym.sym == SDLK_BACKSPACE) {
            if (Status::alphabet.size() - 1) {
                for (auto& i : Status::tape)
                    if (i == Status::alphabet[Status::alphabet.size() - 1])
                        i = Status::alphabet[0];
                
                Logger::LogMessage(std::string("Delete \"") + Status::alphabet[Status::alphabet.size() - 1] + "\" from INPUT BAR when possible. Bar was \"" + Status::alphabet + "\"");
                
                Status::alphabet = Status::alphabet.substr(0, Status::alphabet.size() - 1);
                for (int i = 0; i < Status::algorithm.size(); i++)
                    Status::algorithm[i].erase(Status::algorithm[i].end() - 1);
            } else {
                Logger::LogMessage(std::string("Try to delete from INPUT BAR when impossible. Bar is \"" + Status::alphabet + "\""));
            }
            value.data->SetContent(Status::alphabet, m_Renderer);
        }
    } else if (l_Event->type == SDL_TEXTINPUT) {
        if (Status::alphabet.size() < Status::maximalOfLength) {
            bool fake = false;
            for (int j = 0; j < Status::alphabet.size(); j++) {
                if (Status::alphabet[j] == l_Event->text.text[0] || l_Event->text.text[0] < 0)
                    fake = true;
            }
            if (!fake && l_Event->text.text[0] != '_') {
                Status::alphabet += l_Event->text.text[0];
                for (int i = 0; i < Status::algorithm.size(); i++)
                    Status::algorithm[i].push_back("");
                value.data->SetContent(Status::alphabet, m_Renderer);
                Logger::LogMessage(std::string("Add \"") + l_Event->text.text[0] + "\" to INPUT BAR when possible. Bar is \"" + Status::alphabet + "\"");
            }  else if (l_Event->text.text[0] == '_') {
                Logger::LogMessage(std::string("Try to add \"_\" to INPUT BAR when possible. Bar is \"" + Status::alphabet + "\""));
            } else {
                Logger::LogMessage(std::string("Try to add repeat symbol \"") + l_Event->text.text[0] + "\" to INPUT BAR when possible. Bar is \"" + Status::alphabet + "\"");
            }
        } else {
            Logger::LogMessage(std::string("Try to add to INPUT BAR when impossible. Bar is \"" + Status::alphabet + "\""));
        }
    }
    
    if (l_Event->type == SDL_KEYDOWN) {
        if (l_Event->key.keysym.sym == SDLK_RETURN) {
            disable();
        }
    }
    
}
