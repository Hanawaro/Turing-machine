#include "RightButton.hpp"

RightButton::RightButton(void) {}
RightButton::~RightButton(void) {}

void RightButton::draw(SDL_Renderer* l_Renderer) {
    switch (m_Locale) {
        case Locale::Up:
            switch (Status::status) {
                case Status::DeepStatus::Process:
                case Status::DeepStatus::Pause:
                    filledTrigonRGBA(l_Renderer,
                                     (right + 5)*Status::resizeHorizontal,
                                     top*Status::resizeVertical,
                                     (right + 5)*Status::resizeHorizontal,
                                     bottom*Status::resizeVertical,
                                     (right + 30)*Status::resizeHorizontal,
                                     center*Status::resizeVertical,
                                     0x50, 0x51, 0x52, 0xff
                                     );
                    break;
                default:
                    filledTrigonRGBA(l_Renderer,
                                     (right + 5)*Status::resizeHorizontal,
                                     top*Status::resizeVertical,
                                     (right + 5)*Status::resizeHorizontal,
                                     bottom*Status::resizeVertical,
                                     (right + 30)*Status::resizeHorizontal,
                                     center*Status::resizeVertical,
                                     0x00, 0x00, 0x00, 0xff
                                     );
                    break;
            }
            break;
        case Locale::Down:
            filledTrigonRGBA(l_Renderer,
                             (right + 5)*Status::resizeHorizontal,
                             top*Status::resizeVertical,
                             (right + 5)*Status::resizeHorizontal,
                             bottom*Status::resizeVertical,
                             (right + 30)*Status::resizeHorizontal,
                             center*Status::resizeVertical,
                             0x18, 0x54, 0x93, 0xff
                             );
            break;
        case Locale::Touch:
            if (Status::status != Status::DeepStatus::Process && Status::status != Status::DeepStatus::Pause) {
                filledTrigonRGBA(l_Renderer,
                                 (right + 5)*Status::resizeHorizontal,
                                 top*Status::resizeVertical,
                                 (right + 5)*Status::resizeHorizontal,
                                 bottom*Status::resizeVertical,
                                 (right + 30)*Status::resizeHorizontal,
                                 center*Status::resizeVertical,
                                 0x23, 0x79, 0xd3, 0xff
                                 );
            } else {
                filledTrigonRGBA(l_Renderer,
                                 (right + 5)*Status::resizeHorizontal,
                                 top*Status::resizeVertical,
                                 (right + 5)*Status::resizeHorizontal,
                                 bottom*Status::resizeVertical,
                                 (right + 30)*Status::resizeHorizontal,
                                 center*Status::resizeVertical,
                                 0x51, 0x52, 0x53, 0xff
                                 );
            }
            break;
    }
}

void RightButton::touch(void) {
    if (m_Locale != Locale::Down && (Status::status != Status::DeepStatus::Process || Status::status != Status::DeepStatus::Pause))
        m_Locale = Locale::Touch;
}

void RightButton::active(void) {
    if (Status::status == Status::DeepStatus::Process || Status::status == Status::DeepStatus::Pause)
        m_Locale = Locale::Up;
    else
       m_Locale = Locale::Down;
}

void RightButton::set(void) {
    if (Status::status != Status::DeepStatus::Process && Status::status != Status::DeepStatus::Pause) {
        Status::status = Status::DeepStatus::Empty;
        Status::bias++;
        if (Status::bias + 15 > Status::tape.size()) {
            Status::tape.push_back(' ');
            Logger::LogMessage(std::string("Press RIGHT button when possible with allocate"));
        } else {
            Logger::LogMessage(std::string("Press RIGHT button when possible without allocate"));
        }
    } else {
        Logger::LogMessage(std::string("Try to press RIGHT button when impossible"));
    }
    m_Locale = Locale::Touch;
}

void RightButton::disable(void) {
    m_Locale = Locale::Up;
    Status::status = Status::DeepStatus::Empty;
}

void RightButton::clear(void) {
    if (m_Locale != Locale::Down)
        deepClear();
}

void RightButton::deepClear(void) {
    m_Locale = Locale::Up;
}

