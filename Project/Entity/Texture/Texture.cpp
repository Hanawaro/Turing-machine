#include "Texture.hpp"

TextureEntity::TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer)
    : m_Path(l_Path), m_Map({256, 256, 256})
{
    Logger::LogProcess(std::string("Creating texture from"));
    Logger::LogWarning(std::string("Texture size not specified. Set by default"));
    m_DstRect.x = 0;
    m_DstRect.y = 0;
    m_DstRect.w = 0;
    m_DstRect.h = 0;
    SetTexture(l_Path, l_Renderer);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
    Logger::LogSucsess(std::string("Texture created"));
}

TextureEntity::TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, Uint16 l_Width, Uint16 l_Height)
    : m_Path(l_Path), m_Map({ 256, 256, 256})
{
    Logger::LogProcess(std::string("Creating texture from"));
    m_DstRect.x = 0;
    m_DstRect.y = 0;
    m_DstRect.w = l_Width;
    m_DstRect.h = l_Height;
    SetTexture(l_Path, l_Renderer);
    Logger::LogSucsess(std::string("Texture created"));
}

TextureEntity::TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map)
    : m_Path(l_Path), m_Map(l_Map)
{
    Logger::LogProcess(std::string("Creating texture from"));
    Logger::LogWarning(std::string("Texture size not specified. Set by default"));
    m_DstRect.x = 0;
    m_DstRect.y = 0;
    m_DstRect.w = 0;
    m_DstRect.h = 0;
    SetTexture(l_Path, l_Renderer, l_Map);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
    Logger::LogSucsess(std::string("Texture created"));
}

TextureEntity::TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map, Uint16 l_Width, Uint16 l_Height)
    : m_Path(l_Path), m_Map(l_Map)
{
    Logger::LogProcess(std::string("Creating texture"));
    m_DstRect.x = 0;
    m_DstRect.y = 0;
    m_DstRect.w = l_Width;
    m_DstRect.h = l_Height;
    SetTexture(l_Path, l_Renderer, l_Map);
    Logger::LogSucsess(std::string("Texture created"));
}

TextureEntity::~TextureEntity(void) {
    Logger::LogProcess(std::string("Deleting texture from ") + m_Path);
    SDL_DestroyTexture(m_Texture);
    Logger::LogSucsess(std::string("Texture from ") + m_Path + std::string(" deleted"));
}

void TextureEntity::draw(SDL_Renderer* l_Renderer) {
    SDL_RenderCopy(l_Renderer, m_Texture, NULL, &m_DstRect);
}

void TextureEntity::draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY) {
    m_DstRect.x = l_PosX;
    m_DstRect.y = l_PosY;
    draw(l_Renderer);
}

void TextureEntity::SetSize(Uint16 l_Width, Uint16 l_Height) {
    m_DstRect.w = l_Width;
    m_DstRect.h = l_Height;
}

void TextureEntity::SetPosition(Sint16 l_PosX, Sint16 l_PosY) {
    m_DstRect.x = l_PosX;
    m_DstRect.y = l_PosY;
}

void TextureEntity::SetTexture(const std::string& l_Path, SDL_Renderer* l_Renderer) {
    Logger::LogProcess(std::string("Loading image to texture from ") + l_Path);
    SDL_Surface* tmp_Surface = nullptr;

    if (!(tmp_Surface = IMG_Load(m_Path.c_str()))) {
        Logger::LogError(std::string("Unable to load image ") + l_Path + std::string("! Sdl_image Error: ") + IMG_GetError());
        exit(2);
    }

    if (!(m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface))) {
        Logger::LogError(std::string("Unable to create texture from ") + l_Path + std::string("! Sdl_image Error: ") + IMG_GetError());
        SDL_FreeSurface(tmp_Surface);
        exit(2);
    }

    m_Path = l_Path;

    SDL_FreeSurface(tmp_Surface);

    Logger::LogSucsess(std::string("Texture loaded from ") + l_Path);
}

void TextureEntity::SetTexture(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map) {
    Logger::LogProcess(std::string("Loading image to texture from ") + l_Path);
    SDL_Surface* tmp_Surface = nullptr;

    if (!(tmp_Surface = IMG_Load(l_Path.c_str()))) {
        Logger::LogError(std::string("Unable to load image ") + l_Path + std::string("! Sdl_image Error: ") + IMG_GetError());
        exit(2);
    }

    SDL_SetColorKey(tmp_Surface, true, SDL_MapRGB(tmp_Surface->format, Uint8(l_Map.r), Uint8(l_Map.g), Uint8(l_Map.b)));

    if (!(m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface))) {
        Logger::LogError(std::string("Unable to create texture from ") + l_Path + std::string("! Sdl_image Error: ") + IMG_GetError());
        SDL_FreeSurface(tmp_Surface);
        exit(2);
    }

    m_Path = l_Path;

    SDL_FreeSurface(tmp_Surface);

    Logger::LogSucsess(std::string("Texture loaded from ") + l_Path);
}

const std::string& TextureEntity::GetPath(void) const {    return m_Path; }

const MapRGB* TextureEntity::GetMapRGB(void) const { return &m_Map; }

const SDL_Rect* TextureEntity::GetDstRect(void) const { return &m_DstRect; }

const SDL_Texture* TextureEntity::GetTexture(void) const { return m_Texture; }
