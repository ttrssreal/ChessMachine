#pragma once
#include "chessboard.h"
#include <SDL2/SDL.h>

class Window {
  private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    int m_width, m_height;

  public:
    Window(int width, int height);
    ~Window();

    struct BoardState* boardstate;

    void clear();
    void drawboard();
    void drawpieces();
    void render();
};