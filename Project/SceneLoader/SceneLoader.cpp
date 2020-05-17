#include "SceneLoader.hpp"

#include <sstream>

#include "Scenes/Scene_01/Scene_01.hpp"

#include "Scenes/Scene_01/Status/Status.hpp"

SceneLoader::SceneLoader(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
    m_Window = l_Window;
    m_Renderer = l_Renderer;
    m_ActiveScene = Scenes::EMPTY;
    Logger::LogProcess("Creating the scenes"s);

    // Init static status
    for (int i = 0; i < Status::amountOfCells; i++)
        Status::tape.push_back(' ');
    for (int i = 0; i < 2; i++)
        Status::algorithm.push_back({""});
    Status::alphabet = " ";
    Status::sideBar = { 0, 0, 0, 0, 0 };
    
    m_Scenes[0] = new Scene_01(m_Renderer);

    bool status = true;
    for (int i = 0; i < AMOUNT_OF_SCENES; i++)
        if (!m_Scenes[i]) {
            std::stringstream tmp_ss;
            tmp_ss << i;
            std::string error;
            tmp_ss >> error;
            status = false;
            Logger::LogError("Could not create scene["s + error + "]");
            exit(3);
        }
    if (status) Logger::LogSucsess("All scenes are created"s);
}

SceneLoader::~SceneLoader(void) {
    Logger::LogProcess("Deleting all scenes"s);
    for (int i = 0; i < AMOUNT_OF_SCENES; i++)
        delete m_Scenes[i];
    Logger::LogSucsess("All scenes deleted"s);
}

void SceneLoader::SetScene(Scenes l_Scene) {
    if (l_Scene != Scenes::EMPTY && l_Scene != Scenes::END) {
        if(m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END)
            ClearScene();
        m_ActiveScene = l_Scene;
        m_Scenes[(int) l_Scene]->Init(m_Window, m_Renderer);
        Logger::LogSucsess("The scene loaded"s);
    } else {
        Logger::LogError("Could not load the scene"s);
        exit(5);
    }
}

void SceneLoader::SetStartScene(void) {
    SetScene(Scenes::START);
}

void SceneLoader::ClearScene(void) {
    if (m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END) {
        m_Scenes[(Sint16) m_ActiveScene]->Clear();
        Logger::LogSucsess("The scene cleared\n");
        m_ActiveScene = Scenes::EMPTY;
    } else {
        Logger::LogWarning("Could not clear the scene\n");
    }
}

void SceneLoader::HandleEvent(SDL_Event *l_Event) {
    if (m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END) {
        m_Scenes[(Sint16) m_ActiveScene]->HandleEvent(l_Event);
    } else {
        Logger::LogWarning("Could not load the scene");
    }
}

void SceneLoader::draw(void) {
    if (m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END) {
        m_Scenes[(Sint16) m_ActiveScene]->draw();
    } else {
        Logger::LogWarning("Could not load the scene");
    }
}

void SceneLoader::Update(double l_Time) {
    if (m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END) {
        m_Scenes[(Sint16) m_ActiveScene]->Update(l_Time);
    } else {
        Logger::LogWarning("Could not load the scene");
    }
}

Sint16 SceneLoader::GetActiveScene(void) const { return (Sint16) m_ActiveScene; }

bool SceneLoader::GetStatusScene(Scenes l_Scene) const {
    if (m_ActiveScene != Scenes::EMPTY && m_ActiveScene != Scenes::END) {
        return m_Scenes[(int) l_Scene]->GetStatus();
    }
    Logger::LogWarning("Could not load the scene");
    return false;
}
