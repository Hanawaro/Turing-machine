#include "Scene_01.hpp"

// init static status class
    Status::DeepStatus Status::status = Status::DeepStatus::Empty;
    std::vector<char> Status::tape;
    int Status::bias = 0;
    std::vector<std::vector<std::string>> Status::algorithm;
    std::string Status::alphabet;
    SideBar Status::sideBar;

    double Status::resizeHorizontal = 1.0;
    double Status::resizeVertical   = 1.0;

Scene_01::Scene_01(SDL_Renderer* l_Renderer) : core(l_Renderer) {
    m_Background = new TextureEntity(m_Path, l_Renderer, WIN_WIDTH, WIN_HEIGHT);
    m_BG_width = m_Background->GetDstRect()->w;
    m_BG_height = m_Background->GetDstRect()->h;

}

Scene_01::~Scene_01(void) {
    delete m_Background;
    Clear();
}

void Scene_01::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
    // Init by default
    m_Window = l_Window;
    m_Renderer = l_Renderer;

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);
    
    m_Status = true;
}

void Scene_01::Clear(void) {
    m_Status = false;
}

void Scene_01::HandleEvent(SDL_Event *l_Event) {
    // Take absolut coordinates
    int x = l_Event->motion.x/Status::resizeHorizontal;
    int y = l_Event->motion.y/Status::resizeVertical;
    
    // Handle touch event
    core.touch(x, y);
    
    // Handle events to other moduls
    core.handleEvent(l_Event);
    
    // Handle main events
    switch (l_Event->type) {
        case SDL_WINDOWEVENT:
            // Resize event
            switch (l_Event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    Status::resizeHorizontal = l_Event->window.data1/WIN_WIDTH;
                    Status::resizeVertical = l_Event->window.data2/WIN_HEIGHT;
                    m_Background->SetSize(m_BG_width*Status::resizeHorizontal, m_BG_height*Status::resizeVertical);
                break;
            }
            break;
        // Touch without up-move
        case SDL_MOUSEBUTTONDOWN:
            if (l_Event->button.button == SDL_BUTTON_LEFT)
                core.upTouch(x, y);
            break;
        // Real touch
        case SDL_MOUSEBUTTONUP:
            if (l_Event->button.button == SDL_BUTTON_LEFT) {
                core.downTouch(x, y);
            }
            break;
    }
}

void Scene_01::draw(void) {
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    m_Background->draw(m_Renderer);
    core.drawCore();

    SDL_RenderPresent(m_Renderer);
}

void Scene_01::Update(double l_Time) {
    core.doAlgorithm(l_Time);
}
