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
    
    Logger::LogProcess("Creating the application class"s);
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Logger::LogError("SDL could not initialize! SDL_Error: "s + SDL_GetError());
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("SDL initialized"s);
    
    // Init IMG
    int tmp_imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(tmp_imgFlags) & tmp_imgFlags)) {
        Logger::LogError("SDL_image could not initialuze! SDL_image: "s + IMG_GetError());
        SDL_Quit();
        Logger::LogWarning("SDL quited"s);
        Logger::LogWarning("Memory cleared"s);
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("IMG initialized"s);
    
    // Init TTF
    if (TTF_Init() < 0) {
        Logger::LogError("TTF could not initialize! TTF_Error: "s + TTF_GetError());
        IMG_Quit();
        Logger::LogWarning("IMG quited"s);
        SDL_Quit();
        Logger::LogWarning("SDL quited"s);
        Logger::LogWarning("Memory cleared"s);
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("TTF initialized"s);
    
    // MIX
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        Logger::LogError("Window could not be created! SDL_Error: "s + Mix_GetError());
        TTF_Quit();
        Logger::LogWarning("TTF quited"s);
        IMG_Quit();
        Logger::LogWarning("IMG quited"s);
        SDL_Quit();
        Logger::LogWarning("SDL quited"s);
        Logger::LogWarning("Memory cleared"s);
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("MIX initialized"s);
    
    // Initialize window
    m_Window = new WindowEntity();
    m_Window->width = l_Width;
    m_Window->height = l_Height;
    if (!(m_Window->window = SDL_CreateWindow(l_Title, l_PosX, l_PosY, l_Width, l_Height, l_Flag))) {
        Logger::LogError("Window could not be created! SDL_Error: "s + SDL_GetError());
        delete m_Window;
        Logger::LogWarning("Window deleted"s);
        TTF_Quit();
        Logger::LogWarning("TTF quited"s);
        IMG_Quit();
        Logger::LogWarning("IMG quited"s);
        SDL_Quit();
        Logger::LogWarning("SDL quited"s);
        Logger::LogWarning("Memory cleared"s);
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("Window initialized"s);
    
    // Initialize renderer
    if (!(m_Renderer = SDL_CreateRenderer(m_Window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        Logger::LogError("Renderer could not be created! SDL_Error: "s + SDL_GetError());
        SDL_DestroyWindow(m_Window->window);
        delete m_Window;
        Logger::LogWarning("Window deleted"s);
        TTF_Quit();
        Logger::LogWarning("TTF quited"s);
        IMG_Quit();
        Logger::LogWarning("IMG quited"s);
        SDL_Quit();
        Logger::LogWarning("SDL quited"s);
        Logger::LogWarning("Memory cleared"s);
        Logger::Destroy();
        return;
    }
    Logger::LogSucsess("Renderer initialized"s);
    
    // Initialize scene loader
    m_SceneLoader = new SceneLoader(m_Window, m_Renderer);
    Logger::LogSucsess("Scene loader initialized"s);
    
    // Start game loop and load start scene
    m_isRunning = true;
    m_initFlag = true;
    m_SceneLoader->SetStartScene();
    Logger::LogSucsess("Application class created\n"s);
}

void Application::destroy(void) {
    Logger::LogProcess("Deleting application class"s);
    if (m_initFlag) {
        // Delete scene loader
        delete m_SceneLoader;
        Logger::LogSucsess("Scene loader deleted"s);
        // Destroy renderer
        SDL_DestroyRenderer(m_Renderer);
        Logger::LogSucsess("Renderer deleted"s);
        // Delete and destroy window
        SDL_DestroyWindow(m_Window->window);
        delete m_Window;
        Logger::LogSucsess("Window deleted"s);
        // Mix quit
        Mix_Quit();
        Logger::LogSucsess("MIX quited"s);
        // Ttf quit
        TTF_Quit();
        Logger::LogSucsess("TTF quited"s);
        // Img quit
        IMG_Quit();
        Logger::LogSucsess("IMG quited"s);
        // Sdl quit
        SDL_Quit();
        Logger::LogSucsess("SDL quited"s);
        Logger::LogSucsess("Application class deleted"s);
        // Destroy logger
        Logger::Destroy();
    }
}

