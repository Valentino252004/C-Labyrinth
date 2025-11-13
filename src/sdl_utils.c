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

void display_menu(SDL_Renderer* renderer, TTF_Font* font, Menu* menu) {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color selectedItemColor = {255, 0, 0, 255};
    SDL_Color testColor = {127, 0, 127, 255};
    int width, height;

    SDL_GetRendererOutputSize(renderer, &width, &height);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, NULL);

    SDL_Color itemColor;
    SDL_Rect textContainer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int textWidth, textHeight, offset;
    offset = (menu->nbItems-1)*50;
    for (int i = 0; i < menu->nbItems; i++) {
        if (i < menu->nbInputs) {
            //Input;
        }
        if (i == menu->selectedMenuItem) {
            if (menu->isWriting) {
                itemColor = testColor;
            } else {
                itemColor = selectedItemColor;
            }
        }
        else {
            itemColor = textColor;
        }

        surface = TTF_RenderUTF8_Blended(
            font, menu->items[i], itemColor
        );
        
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
        textContainer.x = (width - textWidth)/2; //Center of the screen minus half the width of the text container
        textContainer.y = (height)/2 - offset + 100*i; //Center of the screen minus a flat value + X*i pixels to place them one by one
        textContainer.h = textHeight;
        textContainer.w = textWidth;
        SDL_RenderCopy(renderer, texture, NULL, &textContainer);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

}