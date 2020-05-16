#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <Logger.hpp>

class TextEntity {
public:
    TextEntity(std::string l_Path, Uint16 l_Size, SDL_Renderer* l_Renderer);
    TextEntity(std::string l_Path, Uint16 l_Size, std::string l_Content, SDL_Renderer* l_Renderer);
    TextEntity(std::string l_Path, Uint16 l_Size, SDL_Color l_Color, SDL_Renderer* l_Renderer);
    TextEntity(std::string l_Path, Uint16 l_Size, SDL_Color l_Color, std::string l_Content, SDL_Renderer* l_Renderer);
    ~TextEntity(void);

    void SetSize(Uint16 l_Width, Uint16 l_Height);
    void SetPosition(Sint16 l_PosX, Sint16 l_PosY);
    void SetContent(const std::string& l_Content, SDL_Renderer* l_Renderer);
    void setColor(SDL_Color l_Color, SDL_Renderer* l_Renderer);
    void draw(SDL_Renderer* l_Renderer);
    void draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY);
    void draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY, Uint16 l_Width, Uint16 l_Height);

    const std::string& GetFont(void) const;
    const std::string& GetContent(void) const;
    const SDL_Rect* GetDstRect(void) const;
private:
    std::string m_Path = "";
    TTF_Font* m_Font = nullptr;

    std::string m_Content = "";
    Uint16 m_Size = 0;
    SDL_Color m_Color = { 255, 255, 255 };
    SDL_Rect m_DstRect = { 0, 0, 0, 0 };

    SDL_Texture* m_Texture = nullptr;
};

#endif
