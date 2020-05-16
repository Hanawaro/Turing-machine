#include "Text.hpp"

TextEntity::TextEntity(std::string l_Path, Uint16 l_Size, SDL_Renderer* l_Renderer)
    : m_Path(l_Path), m_Size(l_Size)
{
    Logger::LogProcess(std::string("Creating text"));
    Logger::LogProcess(std::string("Loading the font from ") + m_Path);
    if ( !(m_Font = TTF_OpenFont(m_Path.c_str(), m_Size)) ) {
        Logger::LogError(std::string("Could not load the font from ") + m_Path);
        exit(1);
    } else {
        Logger::LogSucsess(std::string("The font from ") + m_Path + std::string(" loaded"));
        SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
        m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
        m_DstRect = { 0, 0, 0, 0 };
        SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
        SDL_FreeSurface(tmp_Surface);
        Logger::LogSucsess(std::string("The text created "));
    }
}

TextEntity::TextEntity(std::string l_Path, Uint16 l_Size, std::string l_Content, SDL_Renderer* l_Renderer)
    : m_Path(l_Path), m_Size(l_Size), m_Content(l_Content)
{
    Logger::LogProcess(std::string("Creating text"));
    Logger::LogProcess(std::string("Loading the font from ") + m_Path);
    if (!(m_Font = TTF_OpenFont(m_Path.c_str(), m_Size))) {
        Logger::LogError(std::string("Could not load the font from ") + m_Path);
        exit(1);
    } else {
        Logger::LogSucsess(std::string("The font from ") + m_Path + std::string(" loaded"));
        SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
        m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
        m_DstRect = { 0, 0, 0, 0 };
        SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
        SDL_FreeSurface(tmp_Surface);
        Logger::LogSucsess(std::string("The text created "));
    }
}

TextEntity::TextEntity(std::string l_Path, Uint16 l_Size, SDL_Color l_Color, SDL_Renderer* l_Renderer)
    : m_Path(l_Path), m_Size(l_Size), m_Color(l_Color)
{
    Logger::LogProcess(std::string("Creating text"));
    Logger::LogProcess(std::string("Loading the font from ") + m_Path);
    if (!(m_Font = TTF_OpenFont(m_Path.c_str(), m_Size))) {
        Logger::LogError(std::string("Could not load the font from ") + m_Path);
        exit(1);
    } else {
        Logger::LogSucsess(std::string("The font from ") + m_Path + std::string(" loaded"));
        SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
        m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
        m_DstRect = { 0, 0, 0, 0 };
        SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
        SDL_FreeSurface(tmp_Surface);
        Logger::LogSucsess(std::string("The text created "));
    }
}

TextEntity::TextEntity(std::string l_Path, Uint16 l_Size, SDL_Color l_Color, std::string l_Content, SDL_Renderer* l_Renderer)
    : m_Path(l_Path), m_Size(l_Size), m_Color(l_Color), m_Content(l_Content)
{
    Logger::LogProcess(std::string("Creating text"));
    Logger::LogProcess(std::string("Loading the font from ") + m_Path);
    if (!(m_Font = TTF_OpenFont(m_Path.c_str(), m_Size))) {
        Logger::LogError(std::string("Could not load the font from ") + m_Path);
        exit(1);
    } else {
        Logger::LogSucsess(std::string("The font from ") + m_Path + std::string(" loaded"));
        SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
        m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
        m_DstRect = { 0, 0, 0, 0 };
        SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
        SDL_FreeSurface(tmp_Surface);
        Logger::LogSucsess(std::string("The text created "));
    }
}

TextEntity::~TextEntity(void) {
    Logger::LogProcess(std::string("Deleting the text"));
    TTF_CloseFont(m_Font);
    Logger::LogSucsess(std::string("The font closed"));
    SDL_DestroyTexture(m_Texture);
    Logger::LogSucsess(std::string("The texture deleted"));
    Logger::LogSucsess(std::string("Text deleted"));
}

void TextEntity::SetSize(Uint16 l_Width, Uint16 l_Height) {
    m_DstRect.w = l_Width;
    m_DstRect.h = l_Height;
}

void TextEntity::SetPosition(Sint16 l_PosX, Sint16 l_PosY) {
    m_DstRect.x = l_PosX;
    m_DstRect.y = l_PosY;
}

void TextEntity::SetContent(const std::string& l_Content, SDL_Renderer* l_Renderer)  {
    m_Content = l_Content;
    SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
    SDL_DestroyTexture(m_Texture);
    m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
    SDL_FreeSurface(tmp_Surface);
}

void TextEntity::setColor(SDL_Color l_Color, SDL_Renderer* l_Renderer) {
    m_Color = l_Color;
    SDL_Surface* tmp_Surface = TTF_RenderText_Solid(m_Font, m_Content.c_str(), m_Color);
    SDL_DestroyTexture(m_Texture);
    m_Texture = SDL_CreateTextureFromSurface(l_Renderer, tmp_Surface);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_DstRect.w, &m_DstRect.h);
    SDL_FreeSurface(tmp_Surface);
}

void TextEntity::draw(SDL_Renderer* l_Renderer) {
    SDL_RenderCopy(l_Renderer, m_Texture, NULL, &m_DstRect);
}

void TextEntity::draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY) {
    SetPosition(l_PosX, l_PosY);
    SDL_RenderCopy(l_Renderer, m_Texture, NULL, &m_DstRect);
}

void TextEntity::draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY, Uint16 l_Width, Uint16 l_Height) {
    SetSize(l_Width, l_Height);
    SetPosition(l_PosX, l_PosY);
    SDL_RenderCopy(l_Renderer, m_Texture, NULL, &m_DstRect);
}

const std::string& TextEntity::GetFont(void) const { return m_Path; }

const std::string& TextEntity::GetContent(void) const { return m_Content; }

const SDL_Rect* TextEntity::GetDstRect(void) const { return &m_DstRect; }
