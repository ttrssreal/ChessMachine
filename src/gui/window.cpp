#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>

Window::Window(int width, int height) {
    m_width = width;
    m_height = height;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(m_width, m_height, NULL, &m_window, &m_renderer);
}

Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
}

void Window::drawboard() {
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            if ((x + y) % 100 == 8) {
                SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
                SDL_RenderDrawPoint(m_renderer, x, y);
            } else {
                SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
                SDL_RenderDrawPoint(m_renderer, x, y);
            }
        }
    }
}

void Window::render() {
    SDL_RenderPresent(m_renderer);
}