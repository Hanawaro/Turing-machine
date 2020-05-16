#include "LeftButton.hpp"

LeftButton::LeftButton(void) {}
LeftButton::~LeftButton(void) {}

void LeftButton::draw(SDL_Renderer* l_Renderer) {
    switch (m_Locale) {
    case Locale::Up:
        switch (Status::status) {
            case Status::DeepStatus::Process:
            case Status::DeepStatus::Pause:
                filledTrigonRGBA(l_Renderer,
                                 (left - 5)*Status::resizeHorizontal,
                                 top*Status::resizeVertical,
                                 (left - 5)*Status::resizeHorizontal,
                                 bottom*Status::resizeVertical,
                                 (left - 30)*Status::resizeHorizontal,
                                 center*Status::resizeVertical,
                                 0x50, 0x51, 0x52, 0xff
                                 );
                break;
            default:
                filledTrigonRGBA(l_Renderer,
                                 (left - 5)*Status::resizeHorizontal,
                                 top*Status::resizeVertical,
                                 (left - 5)*Status::resizeHorizontal,
                                 bottom*Status::resizeVertical,
                                 (left - 30)*Status::resizeHorizontal,
                                 center*Status::resizeVertical,
                                 0x00, 0x00, 0x00, 0xff
                                 );
                break;
        }
        break;
    case Locale::Down:
        filledTrigonRGBA(l_Renderer,
                         (left - 5)*Status::resizeHorizontal,
                         top*Status::resizeVertical,
                         (left - 5)*Status::resizeHorizontal,
                         bottom*Status::resizeVertical,
                         (left - 30)*Status::resizeHorizontal,
                         center*Status::resizeVertical,
                         0x18, 0x54, 0x93, 0xff
                         );
        break;
    case Locale::Touch:
        if (Status::status != Status::DeepStatus::Process && Status::status != Status::DeepStatus::Pause) {
            filledTrigonRGBA(l_Renderer,
                             (left - 5)*Status::resizeHorizontal,
                             top*Status::resizeVertical,
                             (left - 5)*Status::resizeHorizontal,
                             bottom*Status::resizeVertical,
                             (left - 30)*Status::resizeHorizontal,
                             center*Status::resizeVertical,
                             0x23, 0x79, 0xd3, 0xff
                             );
        } else {
            filledTrigonRGBA(l_Renderer,
                             (left - 5)*Status::resizeHorizontal,
                             top*Status::resizeVertical,
                             (left - 5)*Status::resizeHorizontal,
                             bottom*Status::resizeVertical,
                             (left - 30)*Status::resizeHorizontal,
                             center*Status::resizeVertical,
                             0x51, 0x52, 0x53, 0xff
                             );
        }
        break;
    }
}

void LeftButton::touch(void) {
    if (m_Locale != Locale::Down && (Status::status != Status::DeepStatus::Process || Status::status != Status::DeepStatus::Pause))
        m_Locale = Locale::Touch;
}

void LeftButton::active(void) {
    if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause)
        m_Locale = Locale::Up;
    else
       m_Locale = Locale::Down;
}

void LeftButton::set(void) {
    if (Status::status != Status::DeepStatus::Process && Status::status != Status::DeepStatus::Pause) {
        Status::status = Status::DeepStatus::Empty;
        if (Status::bias - 1 < 0) {
            Status::tape.insert(Status::tape.begin(), ' ');
            Status::bias = 0;
            Logger::LogMessage(std::string("Press LEFT button when possible with allocate"));
        } else {
            Status::bias = Status::bias - 1;
            Logger::LogMessage(std::string("Press LEFT button when possible without allocate"));
        }
    } else {
        Logger::LogMessage(std::string("Try to press LEFT button when impossible"));
    }
    m_Locale = Locale::Touch;
}

void LeftButton::disable(void) {
    m_Locale = Locale::Up;
    Status::status = Status::DeepStatus::Empty;
}

void LeftButton::clear(void) {
    if (m_Locale != Locale::Down)
        deepClear();
}

void LeftButton::deepClear(void) {
    m_Locale = Locale::Up;
}
