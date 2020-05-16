#include "Application.hpp"

Application::Application(const std::string& l_Title, Uint16 l_Width, Uint16 l_Height, Uint32 l_PosX, Uint32 l_PosY, Uint32 l_Flag) {
    init(l_Title.c_str(), l_Width, l_Height, l_PosX, l_PosY, l_Flag);
}

Application::~Application(void) {
    destroy();
}

bool Application::isRunning(void) const { return m_isRunning; }

void Application::HandleEvent(void) {
    while (SDL_PollEvent(&m_Event)) {
        switch (m_Event.type) {
        case SDL_QUIT:
            m_isRunning = false;
            m_SceneLoader->ClearScene();
            break;
        default:
            m_SceneLoader->HandleEvent(&m_Event);
            break;
        }
    }
}

void Application::Update(void) {
    // Updating
    m_Timer.tick();
    m_Accumulator += m_Timer.delta;
    //std::cout << "Delta is " << m_Timer.delta << " and limit is " << m_Limit*1000 << std::endl;
    if (m_SceneLoader->GetStatusScene((SceneLoader::Scenes)m_SceneLoader->GetActiveScene())) {
        while (m_Accumulator > m_Limit*1000) {
            m_Accumulator -= m_Limit * 1000;
            m_SceneLoader->Update(m_Limit * 1000);
        }
    } else {
        // Manage scenes
    }
}

void Application::Render(void) {
    m_SceneLoader->draw();
}

void Application::init(const char* l_Title, Uint16 l_Width, Uint16 l_Height, Uint32 l_PosX, Uint32 l_PosY, Uint32 l_Flag) {
    // Logger init
    Logger::Init(Logger::MESSAGE);
    
    Logger::LogProcess(std::string("Creating the application class"));
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Logger::LogError(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("SDL initialized"));
    
    // Init IMG
    int tmp_imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(tmp_imgFlags) & tmp_imgFlags)) {
        Logger::LogError(std::string("SDL_image could not initialuze! SDL_image: ") + IMG_GetError());
        SDL_Quit();
        Logger::LogWarning(std::string("SDL quited"));
        Logger::LogWarning(std::string("Memory cleared"));
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("IMG initialized"));
    
    // Init TTF
    if (TTF_Init() < 0) {
        Logger::LogError(std::string("TTF could not initialize! TTF_Error: ") + TTF_GetError());
        IMG_Quit();
        Logger::LogWarning(std::string("IMG quited"));
        SDL_Quit();
        Logger::LogWarning(std::string("SDL quited"));
        Logger::LogWarning(std::string("Memory cleared"));
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("TTF initialized"));
    
    // MIX
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        Logger::LogError(std::string("Window could not be created! SDL_Error: ") + Mix_GetError());
        TTF_Quit();
        Logger::LogWarning(std::string("TTF quited"));
        IMG_Quit();
        Logger::LogWarning(std::string("IMG quited"));
        SDL_Quit();
        Logger::LogWarning(std::string("SDL quited"));
        Logger::LogWarning(std::string("Memory cleared"));
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("MIX initialized"));
    
    // Initialize window
    m_Window = new WindowEntity();
    m_Window->width = l_Width;
    m_Window->height = l_Height;
    if (!(m_Window->window = SDL_CreateWindow(l_Title, l_PosX, l_PosY, l_Width, l_Height, l_Flag))) {
        Logger::LogError(std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
        delete m_Window;
        Logger::LogWarning(std::string("Window deleted"));
        TTF_Quit();
        Logger::LogWarning(std::string("TTF quited"));
        IMG_Quit();
        Logger::LogWarning(std::string("IMG quited"));
        SDL_Quit();
        Logger::LogWarning(std::string("SDL quited"));
        Logger::LogWarning(std::string("Memory cleared"));
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("Window initialized"));
    
    // Initialize renderer
    if (!(m_Renderer = SDL_CreateRenderer(m_Window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        Logger::LogError(std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
        SDL_DestroyWindow(m_Window->window);
        delete m_Window;
        Logger::LogWarning(std::string("Window deleted"));
        TTF_Quit();
        Logger::LogWarning(std::string("TTF quited"));
        IMG_Quit();
        Logger::LogWarning(std::string("IMG quited"));
        SDL_Quit();
        Logger::LogWarning(std::string("SDL quited"));
        Logger::LogWarning(std::string("Memory cleared"));
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess(std::string("Renderer initialized"));
    
    // Initialize scene loader
    m_SceneLoader = new SceneLoader(m_Window, m_Renderer);
    Logger::LogSucsess(std::string("Scene loader initialized"));
    
    // Start game loop and load start scene
    m_isRunning = true;
    m_initFlag = true;
    m_SceneLoader->SetStartScene();
    Logger::LogSucsess(std::string("Application class created\n"));
}

void Application::destroy(void) {
    Logger::LogProcess(std::string("Deleting application class"));
    if (m_initFlag) {
        // Delete scene loader
        delete m_SceneLoader;
        Logger::LogSucsess(std::string("Scene loader deleted"));
        // Destroy renderer
        SDL_DestroyRenderer(m_Renderer);
        Logger::LogSucsess(std::string("Renderer deleted"));
        // Delete and destroy window
        SDL_DestroyWindow(m_Window->window);
        delete m_Window;
        Logger::LogSucsess(std::string("Window deleted"));
        // Mix quit
        Mix_Quit();
        Logger::LogSucsess(std::string("MIX quited"));
        // Ttf quit
        TTF_Quit();
        Logger::LogSucsess(std::string("TTF quited"));
        // Img quit
        IMG_Quit();
        Logger::LogSucsess(std::string("IMG quited"));
        // Sdl quit
        SDL_Quit();
        Logger::LogSucsess(std::string("SDL quited"));
        Logger::LogSucsess(std::string("Application class deleted"));
        // Destroy logger
        Logger::Destroy();
    }
}

