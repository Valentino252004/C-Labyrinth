#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"

void display_string(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, char* string, int x, int y) {
    if (!font) { 
        printf("Erreur font: %s\n", TTF_GetError()); 
        TTF_CloseFont(font); 
        return; 
    }
    SDL_Surface * surface = TTF_RenderUTF8_Blended(font, string, color);
    if (!surface) {
        printf("Erreur création surface texte: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_Rect textBox;
    textBox.x = x;
    textBox.y = y;
    textBox.w = surface->w;
    textBox.h = surface->h;


    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!surface) {
        printf("Erreur création texture: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_RenderCopy(renderer, texture, NULL, &textBox);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void display_menu(SDL_Renderer* renderer, TTF_Font*, int selected, char** items) {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color selectedColor = {255, 0, 0, 255};
    int width, height;

    SDL_GetRendererOutputSize(renderer, &width, &height);

    printf("Size: W: %d, H: %d\n", width, height);

}