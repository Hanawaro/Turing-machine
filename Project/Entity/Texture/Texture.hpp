#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Logger.hpp>

struct MapRGB {
    Uint16 r;
    Uint16 g;
    Uint16 b;
};

class TextureEntity {
public:
    TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer);
    TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, Uint16 l_Width, Uint16 l_Height);
    TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map);
    TextureEntity(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map, Uint16 l_Width, Uint16 l_Height);
    ~TextureEntity(void);

    void draw(SDL_Renderer* l_Renderer);
    void draw(SDL_Renderer* l_Renderer, Sint16 l_PosX, Sint16 l_PosY);

    void SetSize(Uint16 l_Width, Uint16 l_Height);
    void SetPosition(Sint16 l_PosX, Sint16 l_PosY);

    void SetTexture(const std::string& l_Path, SDL_Renderer* l_Renderer);
    void SetTexture(const std::string& l_Path, SDL_Renderer* l_Renderer, MapRGB l_Map);

    const std::string& GetPath(void) const;
    const MapRGB* GetMapRGB(void) const;
    const SDL_Rect* GetDstRect(void) const;
    const SDL_Texture* GetTexture(void) const;
private:
    SDL_Texture* m_Texture = nullptr;

    std::string m_Path;
    MapRGB m_Map;
    SDL_Rect m_DstRect;
};

#endif
