//
//  main.cpp
//  SDL_Fonts
//
//  Created by Serge Muzyka on 7/8/23.
//

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int windowW, windowH;
int rendererW, rendererH;
float ddpi, hdpi, vdpi;

TTF_Font* myFont = 0;
TTF_Font* myFont2 = 0;
TTF_Font* myFont3 = 0;
TTF_Font* myFont4 = 0;

SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
SDL_Color black = { 0x00, 0x00, 0x00, 0 };

int main(int argc, const char * argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "!!!Error: " << SDL_GetError() << std::endl;
    }
    
    //g_pWindow = SDL_CreateWindow("Playing with fonts in SDL", SDL_WINDOWPOS_UNDEFINED,                              SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP || SDL_WINDOW_ALLOW_HIGHDPI);
    g_pWindow = SDL_CreateWindow("Playing with fonts in SDL", SDL_WINDOWPOS_UNDEFINED,                              SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!g_pWindow) {
       std::cout << "ERROR: Cannot create window\n";
       SDL_Quit();
       return -1;
    }
    
    SDL_GetWindowSize(g_pWindow, &windowW, &windowH);
    SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi);
    
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    if (!g_pRenderer) {
       std::cout << "ERROR: Cannot create renderer\n";
       SDL_DestroyWindow(g_pWindow);
       SDL_Quit();
       return -1;
    }
    
    SDL_GetRendererOutputSize(g_pRenderer, &rendererW, &rendererH);
    
    
    TTF_Init();
    //myFont = TTF_OpenFont("open24.ttf", 100);
    //myFont = TTF_OpenFont("fonts/Always In My Heart.ttf", 2880);
    myFont = TTF_OpenFont("fonts/data-latin.ttf", 72);
    //myFont2 = TTF_OpenFont("fonts/Always In My Heart.ttf", 1000);
    myFont2 = TTF_OpenFont("fonts/Semi-Coder-Regular.otf", 800);
    myFont3 = TTF_OpenFont("fonts/Mechanical Machine.ttf", 100);
    myFont4 = TTF_OpenFontDPI("fonts/Mechanical Machine.ttf", 36, static_cast<int>(hdpi), static_cast<int>(vdpi));
    if (!myFont || !myFont2 || !myFont3 || !myFont4) {
        std::cout << "Error!!! Coud not create font!\n";
        std::cout << TTF_GetError();
        TTF_CloseFont(myFont);
        TTF_CloseFont(myFont2);
        TTF_CloseFont(myFont3);
        TTF_CloseFont(myFont4);
    }

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(myFont, "Joysticks found in your system:", white);
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(myFont2, "no joysticks", black);
    SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(myFont3, "Top Secret", black);
    
    
    std::stringstream buffer;
    buffer << "Window resolution: " << windowW << " x " << windowH;
    SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(myFont3, buffer.str().c_str(), black);
    
    buffer.str(std::string());
    buffer << "Renderer resolution: " << rendererW << " x " << rendererH;
    SDL_Surface* surfaceMessage5 = TTF_RenderText_Solid(myFont3, buffer.str().c_str(), black);
    
    
    buffer.str(std::string());
    buffer << "DDPI: " << std::fixed << std::setprecision(2) << ddpi << ", HDPI: " << hdpi << ", VDPI: " << vdpi;
    SDL_Surface* surfaceMessage6 = TTF_RenderText_Solid(myFont4, buffer.str().c_str(), black);
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage);
    SDL_Texture* Message2 = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage2);
    SDL_Texture* Message3 = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage3);
    SDL_Texture* Message4 = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage4);
    SDL_Texture* Message5 = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage5);
    SDL_Texture* Message6 = SDL_CreateTextureFromSurface(g_pRenderer, surfaceMessage6);
    
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = surfaceMessage->w ; // controls the width of the rect
    Message_rect.h = surfaceMessage->h;
    
    SDL_SetRenderDrawColor(g_pRenderer, 0, 255, 50, 50);
    SDL_RenderClear(g_pRenderer);
    
    SDL_RenderCopy(g_pRenderer, Message, NULL, &Message_rect);
    
    Message_rect.x = Message_rect.w;
    Message_rect.w = 400;
    SDL_RenderCopy(g_pRenderer, Message2, NULL, &Message_rect);
    
    Message_rect.y += Message_rect.h;
    //Message_rect.w = 400;
    SDL_RenderCopy(g_pRenderer, Message3, NULL, &Message_rect);
    
    Message_rect.x = 0;
    Message_rect.y = 3 * surfaceMessage4->h;
    Message_rect.h = surfaceMessage4->h;
    Message_rect.w = surfaceMessage4->w;
    SDL_RenderCopy(g_pRenderer, Message4, NULL, &Message_rect);
    
    Message_rect.y += Message_rect.h;
    Message_rect.h = surfaceMessage5->h;
    Message_rect.w = surfaceMessage5->w;
    SDL_RenderCopy(g_pRenderer, Message5, NULL, &Message_rect);
    
    Message_rect.y += Message_rect.h;
    Message_rect.h = surfaceMessage6->h;
    Message_rect.w = surfaceMessage6->w;
    SDL_RenderCopy(g_pRenderer, Message6, NULL, &Message_rect);
    
    SDL_RenderPresent(g_pRenderer);
    
    SDL_Event e;
    bool quit = false;
    while( quit == false ) {
        while( SDL_PollEvent( &e ) ){
            if( e.type == SDL_QUIT ) quit = true;
        }
    }
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(myFont);

    TTF_Quit();
    
    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();
    return 0;
}
