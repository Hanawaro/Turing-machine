#include "StopButton.hpp"

StopButton::StopButton(SDL_Renderer* l_Renderer) {
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

StopButton::~StopButton(void) {
    delete m_Texture.Disable;
    delete m_Texture.Touch;
    delete m_Texture.Active;
    delete m_Texture.Enable;
}

void StopButton::draw(void) {
    switch (m_Locale) {
        case Locale::Up:
            switch (Status::status) {
                case Status::DeepStatus::Process:
                case Status::DeepStatus::Pause:
                    m_Texture.Disable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                    m_Texture.Disable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                    m_Texture.Disable->draw(m_Renderer);
                    break;
                default:
                    m_Texture.Enable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                    m_Texture.Enable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                    m_Texture.Enable->draw(m_Renderer);
                    break;
            }
            break;
        case Locale::Down:
            m_Texture.Active->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
            m_Texture.Active->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
            m_Texture.Active->draw(m_Renderer);
            break;
        case Locale::Touch:
            if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause) {
                m_Texture.Touch->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Touch->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Touch->draw(m_Renderer);

            } else {
                m_Texture.Enable->SetSize(m_Texture.width*Status::resizeHorizontal, m_Texture.height*Status::resizeVertical);
                m_Texture.Enable->SetPosition(x1*Status::resizeHorizontal, y1*Status::resizeVertical);
                m_Texture.Enable->draw(m_Renderer);

                break;
            }
            break;
    }
}

void StopButton::touch(void) {
    if (m_Locale != Locale::Down && (Status::status == Status::DeepStatus::Pause || Status::status == Status::DeepStatus::Process))
        m_Locale = Locale::Touch;
}

void StopButton::active(void) {
    if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause)
        m_Locale = Locale::Down;
    else
        m_Locale = Locale::Up;
}

void StopButton::set(void) {
    if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause) {
        Status::status = Status::DeepStatus::Empty;
        Logger::LogMessage("Press STOP button when possible"s);
        Logger::LogMessage("Stop the algorithm"s);
    } else {
        Logger::LogMessage("Try to press STOP button when impossible"s);
    }
    m_Locale = Locale::Up;
}

void StopButton::disable(void) {
    m_Locale = Locale::Up;
    Status::status = Status::DeepStatus::Empty;
}

void StopButton::clear(void) {
    if (m_Locale != Locale::Down)
        deepClear();
}

void StopButton::deepClear(void) {
    m_Locale = Locale::Up;
}
