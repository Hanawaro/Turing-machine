#include "StartButton.hpp"

StartButton::StartButton(SDL_Renderer* l_Renderer) {
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

StartButton::~StartButton(void) {
    delete m_Texture.Disable;
    delete m_Texture.Touch;
    delete m_Texture.Active;
    delete m_Texture.Enable;
}

void StartButton::draw(void) {
    switch (m_Locale) {
        case Locale::Up:
            switch (Status::status) {
                case Status::DeepStatus::Process:
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
            if (Status::status != Status::DeepStatus::Process) {
                m_Texture.Touch->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Touch->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Touch->draw(m_Renderer);
            } else {
                m_Texture.Disable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Disable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Disable->draw(m_Renderer);
            }
            break;
    }
}

void StartButton::touch(void) {
    if (m_Locale != Locale::Down && Status::status != Status::DeepStatus::Process)
        m_Locale = Locale::Touch;
}

void StartButton::active(void) {
    if (Status::status == Status::DeepStatus::Process)
        m_Locale = Locale::Up;
    else
       m_Locale = Locale::Down;
}

void StartButton::set(void) {
    if (Status::status != Status::DeepStatus::Process) {
        Logger::LogMessage("Press START button when possible"s);
        if (Status::status == Status::DeepStatus::Pause)
            Logger::LogMessage("Continue the algorithm"s);
        else
            Logger::LogMessage("Start the algorithm"s);
        Status::status = Status::DeepStatus::Process;
    } else {
        Logger::LogMessage("Try to press START button when impossible"s);
    }
    m_Locale = Locale::Up;
    
}

void StartButton::disable(void) {
    m_Locale = Locale::Up;
    Status::status = Status::DeepStatus::Empty;
}

void StartButton::clear(void) {
    if (m_Locale != Locale::Down)
        deepClear();
}

void StartButton::deepClear(void) {
    m_Locale = Locale::Up;
}
