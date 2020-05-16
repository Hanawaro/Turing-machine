#include "NextButton.hpp"

NextButton::NextButton(SDL_Renderer* l_Renderer) {
    m_Renderer = l_Renderer;
    m_Texture.Disable = new TextureEntity(m_Path + "disable.png", l_Renderer, {255, 255, 255}, height, width);
    m_Texture.Touch = new TextureEntity(m_Path + "touch.png", l_Renderer, {255, 255, 255}, height, width);
    m_Texture.Active = new TextureEntity(m_Path + "active.png", l_Renderer, {255, 255, 255}, height, width);
    m_Texture.Enable = new TextureEntity(m_Path + "enable.png", l_Renderer, {255, 255, 255}, height, width);
    m_Texture.width = width;
    m_Texture.height = height;
    
    m_Texture.Disable->SetPosition(x1, y1);
    m_Texture.Touch->SetPosition(x1, y1);
    m_Texture.Active->SetPosition(x1, y1);
    m_Texture.Enable->SetPosition(x1, y1);
}

NextButton::~NextButton(void) {
    delete m_Texture.Disable;
    delete m_Texture.Touch;
    delete m_Texture.Active;
    delete m_Texture.Enable;
}

void NextButton::draw(void) {
    switch (m_Locale) {
        case Locale::Up:
            switch (Status::status) {
                case Status::DeepStatus::End:
                case Status::DeepStatus::Process:
                case Status::DeepStatus::Pause:
                    m_Texture.Enable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                    m_Texture.Enable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                    m_Texture.Enable->draw(m_Renderer);
                    break;
                default:
                    m_Texture.Disable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                    m_Texture.Disable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                    m_Texture.Disable->draw(m_Renderer);
                    break;
            }
            break;
        case Locale::Down:
            m_Texture.Active->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
            m_Texture.Active->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
            m_Texture.Active->draw(m_Renderer);
            break;
        case Locale::Touch:
            if (Status::status != Status::DeepStatus::End &&
                Status::status != Status::DeepStatus::Process &&
                Status::status != Status::DeepStatus::Pause) {
                
                m_Texture.Touch->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Touch->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Touch->draw(m_Renderer);
            } else {
                m_Texture.Enable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Enable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Enable->draw(m_Renderer);
            }
            break;
    }
}

void NextButton::touch(void) {
    if (m_Locale != Locale::Down && (Status::status != Status::DeepStatus::Process || Status::status != Status::DeepStatus::Pause))
        m_Locale = Locale::Touch;
}

void NextButton::active(void) {
    if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause || Status::status == Status::DeepStatus::End)
        m_Locale = Locale::Up;
    else
       m_Locale = Locale::Down;
}

void NextButton::set(void) {
    if (Status::status != Status::DeepStatus::Process && Status::status != Status::DeepStatus::Pause && Status::status != Status::DeepStatus::End) {
        
        Logger::LogMessage(std::string("Press NEXT button when possible"));
        if (Status::status != Status::DeepStatus::NextStep)
            Logger::LogMessage(std::string("Next step of the algorithm"));
        else
            Logger::LogMessage(std::string("Reset step of the algorithm"));
        
        Status::status = Status::DeepStatus::NextStep;
    } else {
        Logger::LogMessage(std::string("Try to press NEXT button when impossible"));
    }
    m_Locale = Locale::Touch;
}

void NextButton::disable(void) {
    m_Locale = Locale::Up;
    Status::status = Status::DeepStatus::Empty;
}

void NextButton::clear(void) {
    if (m_Locale != Locale::Down)
        deepClear();
}

void NextButton::deepClear(void) {
    m_Locale = Locale::Up;
}

